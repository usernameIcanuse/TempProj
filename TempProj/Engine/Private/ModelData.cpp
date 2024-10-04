#include "ModelData.h"


const static _bool g_bUseAssimp = false;

HRESULT MODEL_DATA::Make_ModelData(const char* szFilePath, const MODEL_TYPE& In_eModelType, _fmatrix In_TransformMatrix, _bool bAnimZero)
{
    eModelType = In_eModelType;

    XMStoreFloat4x4(&TransformMatrix, In_TransformMatrix);

    //if (In_eModelType == MODEL_TYPE::ANIM)
    //{
    //    int i = 0;
    //}

    szModelFilePath = szFilePath;

    /*if (true == g_bUseAssimp)
    {
        if (FAILED(Load_FromAssimp(bAnimZero)))
            return E_FAIL;

        return S_OK;
    }*/

    string          szBinFilePath;

    char			szDir[MAX_PATH] = "";
    char			szFileName[MAX_PATH] = "";

    _splitpath_s(szModelFilePath.c_str(), nullptr, 0, szDir, MAX_PATH, szFileName, MAX_PATH, nullptr, 0);

    szBinFilePath = szDir;
    szBinFilePath += szFileName;
    szBinFilePath += ".bin";
    szModelFileName = szFileName;

    ifstream is(szBinFilePath, std::ios::binary);

    if (!is.is_open() || g_bUseAssimp)
    {
        is.close();
        if (FAILED(Load_FromAssimp(bAnimZero)))
            return E_FAIL;
    }

    else
    {
        is.close();
        Load_FromBinary();
    }

#ifdef _DEBUG

    if (MODEL_TYPE::ANIM == eModelType)
    {
        string szDebugFileName;

        szDebugFileName = "../bin/Debugs/";

        szDebugFileName += szModelFileName;
        szDebugFileName += ".txt";

        ofstream fout(szDebugFileName);

        Debug_AnimationLog(fout);
        RootNode->Debug_NodeLog(fout);
        Debug_MeshLog(fout);

        fout.close();
    }

   /* else if(MODEL_TYPE::NONANIM == eModelType)
    {
        string szDebugFileName;

        szDebugFileName = "../bin/Debugs/NONANIMs.txt";

        ofstream fout(szDebugFileName,std::ios_base::out | std::ios_base::app);

        Debug_NonAnimLog(fout);

        fout.close();
    }*/

#endif // _DEBUG


	return S_OK;
}

MODEL_DATA::~MODEL_DATA()
{

}

void MODEL_DATA::Bake_Binary()
{
    string          szBinFilePath;

    char			szDir[MAX_PATH] = "";
    char			szFileName[MAX_PATH] = "";

    _splitpath_s(szModelFilePath.c_str(), nullptr, 0, szDir, MAX_PATH, szFileName, MAX_PATH, nullptr, 0);

    szBinFilePath = szDir;
    szBinFilePath += szFileName;
    szBinFilePath += ".bin";

    ofstream os(szBinFilePath, ios::binary);

#ifdef _DEBUG
    //���� ���� ����.
    assert(os.is_open());
#endif // _DEBUG

    write_typed_data(os, TransformMatrix);
    write_typed_data(os, iNumMeshs);
    write_typed_data(os, iNumMaterials);
    write_typed_data(os, iNumAnimations);
    write_typed_data(os, eModelType);
    write_typed_data(os, VertexInfo);

    RootNode->Bake_Binary(os);

    for (_uint i = 0; i < iNumMaterials; i++)
    {
        Material_Datas[i]->Bake_Binary(os);
    }

    for (_uint i = 0; i < iNumMeshs; i++)
    {
        Mesh_Datas[i]->Bake_Binary(os);
    }

    for (_uint i = 0; i < iNumAnimations; i++)
    {
        Animation_Datas[i]->Bake_Binary(os);
    }

    os.close();
}

void MODEL_DATA::Load_FromBinary()
{
    string          szBinFilePath;

    char			szDir[MAX_PATH] = "";
    char			szFileName[MAX_PATH] = "";

    _splitpath_s(szModelFilePath.c_str(), nullptr, 0, szDir, MAX_PATH, szFileName, MAX_PATH, nullptr, 0);

    szBinFilePath = szDir;
    szBinFilePath += szFileName;
    szBinFilePath += ".bin";

    ifstream is(szBinFilePath, ios::binary);

#ifdef _DEBUG
    //���� ���� ����.
    assert(is.is_open());
#endif // _DEBUG

    read_typed_data(is, TransformMatrix);
    read_typed_data(is, iNumMeshs);
    read_typed_data(is, iNumMaterials);
    read_typed_data(is, iNumAnimations);
    read_typed_data(is, eModelType);
    read_typed_data(is, VertexInfo);

    RootNode = make_shared<NODE_DATA>();
    RootNode->Load_FromBinary(is);

    Material_Datas.reserve(iNumMaterials);

    for (_uint i = 0; i < iNumMaterials; i++)
    {
        shared_ptr<MATERIAL_DATA> MaterialData = make_shared<MATERIAL_DATA>();
        MaterialData->Load_FromBinary(is);
        Material_Datas.push_back(MaterialData);
    }


    /* For Mesh */

    // �޽��� ����.
    if (iNumMeshs < 1)
        assert(false);

    Mesh_Datas.reserve((size_t)iNumMeshs);

    for (_uint i = 0; i < iNumMeshs; i++)
    {
        shared_ptr<MESH_DATA> MeshData = make_shared<MESH_DATA>();
        MeshData->Load_FromBinary(is);
        Mesh_Datas.push_back(MeshData);
    }

    /* For Animation */
    Animation_Datas.reserve((size_t)iNumAnimations);

    for (_uint i = 0; i < iNumAnimations; i++)
    {
        shared_ptr<ANIMATION_DATA> AnimationData = make_shared<ANIMATION_DATA>();
        AnimationData->Load_FromBinary(is);
        Animation_Datas.push_back(AnimationData);
    }

    is.close();
}

void MODEL_DATA::Debug_AnimationLog(ofstream& os)
{
    for (size_t i = 0; i < Animation_Datas.size(); i++)
    {
        os << i << ". " << Animation_Datas[i]->szName << endl;
    }
}

void MODEL_DATA::Debug_NonAnimLog(ofstream& os)
{
    _float fMax = XMVectorGetX(XMVector3Length(XMLoadFloat3(&VertexInfo.vMax)));
    _float fMin = XMVectorGetX(XMVector3Length(XMLoadFloat3(&VertexInfo.vMin)));

    os << szModelFileName << ", Min Length:  " << fMin << endl;
    os << szModelFileName << ", Max Length:  " << fMax << endl;
}

void MODEL_DATA::Debug_MeshLog(ofstream& os)
{
    for (size_t i = 0; i < Mesh_Datas.size(); i++)
    {
        os << i << "[" << Mesh_Datas[i]->szName << "]. " << Mesh_Datas[i]->iNumVertices << endl;
    }
}

void MODEL_DATA::Compute_Center(MESH_VTX_INFO& _tVertexInfo)
{
    _vector vDist      = (XMLoadFloat3(&_tVertexInfo.vMax) + XMLoadFloat3(&_tVertexInfo.vMin)) * 0.5f;

    XMStoreFloat3(&_tVertexInfo.vCenter, vDist);
}

_float MODEL_DATA::Get_MaxOffsetRange() const
{
    _vector vOffsetRange = XMLoadFloat3(&VertexInfo.vMax) - XMLoadFloat3(&VertexInfo.vMin);

    return XMVectorGetX(XMVector3Length(vOffsetRange));
}

HRESULT MODEL_DATA::Load_FromAssimp(const _bool In_bAnimZero)
{
    const aiScene* pAiSceneModel = nullptr;

    if (MODEL_TYPE::NONANIM == eModelType)
    {
        pAiSceneModel = AiImporter.ReadFile(szModelFilePath, aiProcess_PreTransformVertices | aiProcess_ConvertToLeftHanded | aiProcess_GenNormals | aiProcess_CalcTangentSpace);
    }

    else if(MODEL_TYPE::ANIM == eModelType)
    {
        pAiSceneModel = AiImporter.ReadFile(szModelFilePath, aiProcess_ConvertToLeftHanded | aiProcess_GenNormals | aiProcess_CalcTangentSpace);
    }

    else if (MODEL_TYPE::NAVI == eModelType)
    {
        pAiSceneModel = AiImporter.ReadFile(szModelFilePath, aiProcess_PreTransformVertices | aiProcess_ConvertToLeftHanded);
    }

    if (!pAiSceneModel)
        return E_FAIL;

    RootNode = make_shared<NODE_DATA>();
    RootNode->Make_NodeData(pAiSceneModel->mRootNode);

    iNumMaterials = pAiSceneModel->mNumMaterials;

    Material_Datas.reserve(iNumMaterials);

    for (_uint i = 0; i < iNumMaterials; i++)
    {
        shared_ptr<MATERIAL_DATA> MaterialData = make_shared<MATERIAL_DATA>();
        MaterialData->Make_NodeData(pAiSceneModel->mMaterials[i]);
        Material_Datas.push_back(MaterialData);
    }


    /* For Mesh */
    iNumMeshs = pAiSceneModel->mNumMeshes;

    // �޽��� ����.
    if (iNumMeshs < 1)
        return S_OK;

    Mesh_Datas.reserve((size_t)iNumMeshs);

    for (_uint i = 0; i < iNumMeshs; i++)
    {
        shared_ptr<MESH_DATA> MeshData = make_shared<MESH_DATA>();
        Mesh_Datas.push_back(MeshData);
        Mesh_Datas.back()->Make_MeshData(eModelType, pAiSceneModel->mMeshes[i], XMLoadFloat4x4(&TransformMatrix), &VertexInfo);
    }

    Compute_Center(VertexInfo);

    iNumAnimations = pAiSceneModel->mNumAnimations;

    /* For Animation */
    Animation_Datas.reserve((size_t)iNumAnimations);
    _uint i = 0;
    if (In_bAnimZero)
    {
        i = 1;
    }
    for (i; i < iNumAnimations; i++)
    {
        shared_ptr<ANIMATION_DATA> AnimationData = make_shared<ANIMATION_DATA>();
        Animation_Datas.push_back(AnimationData);


        Animation_Datas.back()->Make_AnimationData(pAiSceneModel->mAnimations[i]);
    }

    if (In_bAnimZero)
    {
        iNumAnimations -= 1;
    }

    Bake_Binary();

    return S_OK;
}

void MODEL_DATA::OnDestroy()
{
    AiImporter.FreeScene();
}



