#include "Navigation.h"
#include "Cell.h"
#include "Shader.h"
#include "PipeLine.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "ModelData.h"

GAMECLASS_C(CNavigation);
CLONE_C(CNavigation, CComponent);

CNavigation::CNavigation(const CNavigation& rhs)
{
	*this = rhs;
}

HRESULT CNavigation::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CNavigation::Initialize(void* pArg)
{
	return S_OK;
}

void CNavigation::Start()
{
}

void CNavigation::Init_Navi(const string& szModelKey, const NAVIDESC& tNaviDesc)
{
	m_pModelData = GET_SINGLE(CResource_Manager)->Get_ModelFromKey(szModelKey.c_str());

	_uint VerticeCount = m_pModelData->iNumMeshs;

	for (_uint i(0); i < m_pModelData->iNumMeshs; i++)
	{
		shared_ptr<CCell> Cell = CCell::Create(m_pOwner, &m_pModelData->Mesh_Datas[i]->pPosVertices[0].vPosition, i);
		m_pCells.push_back(Cell);
	}

	memcpy(&m_NaviDesc, &tNaviDesc, sizeof(NAVIDESC));
	m_NaviDesc.m_iCurrentIndex = (_int)m_pCells.size() >> 1;

	m_IsVisitedTable.reserve(m_pCells.size());
	for (size_t i(0); i < m_pCells.size(); i++)
		m_IsVisitedTable.push_back(false);

	if (FAILED(Make_Neighbor()))
		DEBUG_ASSERT;
	
}

/* ��ü�� �����̴µ� �־� �׺���̼� �󿡼� ������ �� �ִ°�? �ƴѰ�? : return  */
/* vPosition : ��ü�� ������ġ?!(x), ��ü�� �����̰� �� ������ ��ġ. */
_bool CNavigation::IsMove(_fvector vPosition, _float3* Out_LineDir)
{
	/* m_NaviDesc.m_iCurrentIndex : ���� ��ü�� �����ϴ� ���� �ε���. */
	_int		iNeighborIndex = -1;
	_int		iPreNeighborIndex = iNeighborIndex;

	if (m_pCells.empty())
	{
#ifdef _DEBUG
		//cout << typeid(this).name() << ": ���� �����. �ϴ� �̵� ���� ó��" << endl;
#endif // _DEBUG

		return true;
	}

	Reset_VisitedTable();
	
	

	/*1. ���� �����ϴ� �� �ȿ����� ����������  */
	if (true == m_pCells[m_NaviDesc.m_iCurrentIndex]->isIn(vPosition, &iNeighborIndex, Out_LineDir))
		return true;

	/* ���� �����ϰ� �ִ� �� �ٱ����� ������. */
	else
	{
		/*2. ������ �쿡 �̿��� �����Ҷ� */
		if (0 <= iNeighborIndex)
		{
			while (1)
			{
				iPreNeighborIndex = iNeighborIndex;

				if (true == m_pCells[iNeighborIndex]->isIn(vPosition, &iNeighborIndex, Out_LineDir))
					break;

				if (0 > iNeighborIndex)
					return false;
				
				//// �湮�� ���� �ִٸ� ������.
				//if (!m_IsVisitedTable[iNeighborIndex])
				//{
				//	m_NaviDesc.m_iCurrentIndex = iPreNeighborIndex;
				//	return false;
				//}
				////�湮�� ���� ���ٸ� üũ�Ѵ�.
				//else
				//{
				//	m_IsVisitedTable[iNeighborIndex] = true;
				//}
			}

			m_NaviDesc.m_iCurrentIndex = iNeighborIndex;

			return true;
		}

		/*1. �����ʿ� �̿��� ���ٸ�.  */
		else
		{
			return false;
		}
	}
}

_int CNavigation::Get_CurrentIndex()
{
	return m_NaviDesc.m_iCurrentIndex;
}

void CNavigation::Set_CurrentIndex(const _int& In_iIndex)
{
	m_NaviDesc.m_iCurrentIndex = In_iIndex;
}

void CNavigation::Reset_VisitedTable()
{
	for (size_t i = 0; i < m_IsVisitedTable.size(); i++)
	{
		m_IsVisitedTable[i] = false;
	}
}

#ifdef _DEBUG

HRESULT CNavigation::Render(ID3D11DeviceContext* pDeviceContext)
{
	if (!GAMEINSTANCE->Is_Debug())
		return E_FAIL;

	//���̴� ������Ʈ�� ����.
	if (nullptr == m_pShader.lock().get())
		DEBUG_ASSERT;

	_float4x4		WorldMatrix;



	m_pShader.lock()->Set_RawValue("g_ViewMatrix", (void*)GET_SINGLE(CPipeLine)->Get_Transform_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4));
	m_pShader.lock()->Set_RawValue("g_ProjMatrix", (void*)GET_SINGLE(CPipeLine)->Get_Transform_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4));

	_float4 vColor(1.f, 0.f, 0.f, 1.f);

	if (0 <= m_NaviDesc.m_iCurrentIndex)
	{

		XMStoreFloat4x4(&WorldMatrix, XMMatrixTranspose(XMMatrixTranslation(0.f, 0.1f, 0.f)));
		m_pShader.lock()->Set_RawValue("g_WorldMatrix", &WorldMatrix, sizeof(_float4x4));
		vColor = { 1.f, 0.f, 0.f, 1.f };
		m_pShader.lock()->Set_RawValue("g_vColor", &vColor, sizeof(_float4));
		m_pShader.lock()->Begin(0, pDeviceContext);

		m_pCells[m_NaviDesc.m_iCurrentIndex]->Render(pDeviceContext);
	}
	else
	{

		XMStoreFloat4x4(&WorldMatrix, XMMatrixIdentity());

		m_pShader.lock()->Set_RawValue("g_WorldMatrix", &WorldMatrix, sizeof(_float4x4));
		vColor = { 0.f, 1.f, 0.f, 1.f };
		m_pShader.lock()->Set_RawValue("g_vColor", &vColor, sizeof(_float4));
		m_pShader.lock()->Begin(0, pDeviceContext);

		for (auto& pCell : m_pCells)
		{
			if (nullptr != pCell)
				pCell->Render(pDeviceContext);
		}

	}



	return S_OK;
}
#endif // _DEBUG

HRESULT CNavigation::Make_Neighbor()
{
	for (auto& pSourCell : m_pCells)
	{
		for (auto& pDestCell : m_pCells)
		{
			if (pSourCell == pDestCell)
				continue;

			if (true == pDestCell->Compare_Points(
				pSourCell->Get_Point(CCell::POINT_A),
				pSourCell->Get_Point(CCell::POINT_B)))
			{
				pSourCell->Set_Neighbor(CCell::LINE_AB, pDestCell->Get_Index());
				continue;
			}

			if (true == pDestCell->Compare_Points(
				pSourCell->Get_Point(CCell::POINT_B),
				pSourCell->Get_Point(CCell::POINT_C)))
			{
				pSourCell->Set_Neighbor(CCell::LINE_BC, pDestCell->Get_Index());
				continue;
			}

			if (true == pDestCell->Compare_Points(
				pSourCell->Get_Point(CCell::POINT_C),
				pSourCell->Get_Point(CCell::POINT_A)))
			{
				pSourCell->Set_Neighbor(CCell::LINE_CA, pDestCell->Get_Index());
				continue;
			}
		}
	}


	return S_OK;
}

void CNavigation::Free()
{

	m_pCells.clear();

}
