#include "VIBuffer_DynamicCube.h"

#include "GameInstance.h"

GAMECLASS_C(CVIBuffer_DynamicCube)
CLONE_C(CVIBuffer_DynamicCube, CComponent)

HRESULT CVIBuffer_DynamicCube::Initialize_Prototype()
{
    _uint ind = 0;

    /* ���ؽ� ���� ���� */
    m_iStride           = sizeof(VTXCUBETEX);
    m_iNumVertices      = 8;
    m_iNumVertexBuffers = 1;

    VTXCUBETEX* pVertices = new VTXCUBETEX[m_iNumVertices];
    ZeroMemory(pVertices, sizeof(VTXCUBETEX) * m_iNumVertices);
    
    pVertices[0].vPosition = pVertices[0].vTexUV = { -0.5f,  0.5f, -0.5f };
    pVertices[1].vPosition = pVertices[1].vTexUV = {  0.5f,  0.5f, -0.5f };
    pVertices[2].vPosition = pVertices[2].vTexUV = {  0.5f, -0.5f, -0.5f };
    pVertices[3].vPosition = pVertices[3].vTexUV = { -0.5f, -0.5f, -0.5f };

    pVertices[4].vPosition = pVertices[4].vTexUV = { -0.5f,  0.5f,  0.5f };
    pVertices[5].vPosition = pVertices[5].vTexUV = {  0.5f,  0.5f,  0.5f };
    pVertices[6].vPosition = pVertices[6].vTexUV = {  0.5f, -0.5f,  0.5f };
    pVertices[7].vPosition = pVertices[7].vTexUV = { -0.5f, -0.5f,  0.5f };

    /* ------------------------------------------------------------------ */

    /* �ε��� ���� ���� */
    m_iIndicesStride    = sizeof(FACEINDICES16);
    m_iNumPrimitive     = 12;
    m_iNumIndices       = 3 * m_iNumPrimitive;
    m_eIndexFormat      = DXGI_FORMAT_R16_UINT;
    m_eToplogy          = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    ind = 0;
    FACEINDICES16* pIndices = new FACEINDICES16[m_iNumIndices];
    ZeroMemory(pIndices, sizeof(FACEINDICES16) * m_iNumIndices);

    pIndices[ind++] = { 1, 5, 6 }; pIndices[ind++] = { 1, 6, 2 }; // +x
    pIndices[ind++] = { 4, 0, 3 }; pIndices[ind++] = { 4, 3, 7 }; // -x
    pIndices[ind++] = { 4, 5, 1 }; pIndices[ind++] = { 4, 1, 0 }; // +y
    pIndices[ind++] = { 3, 2, 6 }; pIndices[ind++] = { 3, 6, 7 }; // -y
    pIndices[ind++] = { 5, 4, 7 }; pIndices[ind++] = { 5, 7, 6 }; // +z
    pIndices[ind++] = { 0, 1, 2 }; pIndices[ind++] = { 0, 2, 3 }; // -z

    /* ------------------------------------------------------------------ */

    ZeroMemory(&m_BufferDesc, sizeof(D3D11_BUFFER_DESC));
    m_BufferDesc.ByteWidth             = m_iStride * m_iNumVertices;
    m_BufferDesc.Usage                 = D3D11_USAGE_DYNAMIC;
    m_BufferDesc.BindFlags             = D3D11_BIND_VERTEX_BUFFER;
    m_BufferDesc.StructureByteStride   = m_iStride;
    m_BufferDesc.CPUAccessFlags        = D3D11_CPU_ACCESS_WRITE;
    m_BufferDesc.MiscFlags             = 0;

    ZeroMemory(&m_SubResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
    m_SubResourceData.pSysMem = pVertices;

    if (FAILED(__super::Create_VertexBuffer()))
        return E_FAIL;

    /* ------------------------------------------------------------------ */

    ZeroMemory(&m_BufferDesc, sizeof(D3D11_BUFFER_DESC));
    m_BufferDesc.ByteWidth             = m_iIndicesStride * m_iNumIndices;
    m_BufferDesc.Usage                 = D3D11_USAGE_DEFAULT;
    m_BufferDesc.BindFlags             = D3D11_BIND_INDEX_BUFFER;
    m_BufferDesc.StructureByteStride   = 0;
    m_BufferDesc.CPUAccessFlags        = 0;
    m_BufferDesc.MiscFlags             = 0;

    ZeroMemory(&m_SubResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
    m_SubResourceData.pSysMem = pIndices;

    if (FAILED(__super::Create_IndexBuffer()))
        return E_FAIL;

    /* ------------------------------------------------------------------ */

    Safe_Delete_Array(pVertices);
    Safe_Delete_Array(pIndices);

    return S_OK;
}

HRESULT CVIBuffer_DynamicCube::Initialize(void* _pArg)
{
    return S_OK;
}

void CVIBuffer_DynamicCube::Start()
{
}

void CVIBuffer_DynamicCube::Update(MESH_VTX_INFO _VtxInfo, _fmatrix _WorldMatrix)
{
    _float3				vPosition[8];
	_uint3				vIndex[12];

	vPosition[0] = { _VtxInfo.vMin.x, _VtxInfo.vMax.y, _VtxInfo.vMin.z };
	vPosition[1] = { _VtxInfo.vMax.x, _VtxInfo.vMax.y, _VtxInfo.vMin.z };
	vPosition[2] = { _VtxInfo.vMax.x, _VtxInfo.vMin.y, _VtxInfo.vMin.z };
	vPosition[3] = { _VtxInfo.vMin.x, _VtxInfo.vMin.y, _VtxInfo.vMin.z };
	vPosition[4] = { _VtxInfo.vMin.x, _VtxInfo.vMax.y, _VtxInfo.vMax.z };
	vPosition[5] = { _VtxInfo.vMax.x, _VtxInfo.vMax.y, _VtxInfo.vMax.z };
	vPosition[6] = { _VtxInfo.vMax.x, _VtxInfo.vMin.y, _VtxInfo.vMax.z };
	vPosition[7] = { _VtxInfo.vMin.x, _VtxInfo.vMin.y, _VtxInfo.vMax.z };

    D3D11_MAPPED_SUBRESOURCE		SubResource;

    DEVICECONTEXT->Map(m_pVB.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);

    for (_uint i = 0; i < 8; ++i)
    {
        XMStoreFloat3(&vPosition[i], XMVector3TransformCoord(XMVectorSetW(XMLoadFloat3(&vPosition[i]), 1.f), _WorldMatrix));

        ((VTXCUBETEX*)SubResource.pData)[i].vPosition = vPosition[i];


    }

    DEVICECONTEXT->Unmap(m_pVB.Get(), 0);
}

void CVIBuffer_DynamicCube::Free()
{
    __super::Free();
}
