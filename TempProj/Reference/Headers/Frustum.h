#pragma once
#include "Base.h"

BEGIN(Engine)

class CFrustum :
    public CBase
{
    DECLARE_SINGLETON(CFrustum)

public:
	/* ������������ ����ü�� �����ϴ� ������ ���� ��� ���Ѵ�. */
	HRESULT Initialize();

	/*���� �������� ������ ����� ���Ѵ�. */
	void Update();

public:
	_bool isIn_Frustum_InWorldSpace(_fvector vWorldPoint, _float fRange = 0.f);
	_bool isIn_Frustum_InLocalSpace(_fvector vLocalPoint, _float fRange = 0.f);
	void Transform_ToLocalSpace(_fmatrix WorldMatrixInv);

private:
	_float4				m_vOriginalPoints[8];
	_vector				m_vWorldPoints[8];
	_float4				m_vWorldPlane[2][6];
	_float4				m_vLocalPlane[6];

	_int				iCurrentIndex = -1;

private:
	void Free();

};

END