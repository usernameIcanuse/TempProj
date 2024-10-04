#pragma once
#include "Base.h"
#include "BoneData.h"

BEGIN(Engine)

struct ENGINE_DLL MESH_DATA
{
    vector<shared_ptr<BONE_DATA>>       Bone_Datas;
    shared_ptr<VTXMODEL[]>              pVertices;
    shared_ptr<VTXANIM[]>               pAnimVertices;
    shared_ptr<VTXPOS[]>                pPosVertices;
    shared_ptr<VTXGROUND[]>             pGroundVertices;
    shared_ptr<FACEINDICES32[]>         pIndices;

    string                              szName;

    _uint                               iNumVertices;
    _uint                               iNumFaces;
    _uint                               iNumBones;
    _uint                               iMaterialIndex;

    MODEL_TYPE                          eModelType;

    HRESULT Make_MeshData(const MODEL_TYPE& In_eModelType, aiMesh* In_pAiMesh, const _fmatrix& In_TransformMatrix, MESH_VTX_INFO* In_pVertexInfo);

public:
    void Bake_Binary(ofstream& os);
    void Load_FromBinary(ifstream& is);

private:
    void Check_Position(_float3& _vRecodePosion, _float3 _vValue, _bool(*_pFncPtr)(_float, _float));
};

END