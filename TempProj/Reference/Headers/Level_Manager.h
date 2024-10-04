#pragma once

#include "Base.h"

/* ���� ���ӳ��� ��������� ������ �����Ѵ�. */
/* ������ü�ÿ� ���� ������ �����Ѵ�. */
/* ������������ ����ߴ� ��ü�� �ڿ�(���ҽ���)�� �����Ѵ�. */

BEGIN(Engine)

class CLevel_Manager final : public CBase
{
	DECLARE_SINGLETON(CLevel_Manager)

public:
	HRESULT Open_Level(_uint iLevelID, shared_ptr<class CLevel> pLevel);
	weak_ptr<CLevel> Get_CurrentLevel() { return m_pCurrentLevel; }
	void Tick(_float fTimeDelta);
	HRESULT Render(ID3D11DeviceContext* pDeviceContext);

	GETSET(_uint, iLastCreatedLevelID)

private:
	shared_ptr<class CLevel>			m_pCurrentLevel;
	_uint					m_iCurrentLevelIDBeforeLevelInitalize = 0;

public:
	virtual void OnDestroy() override;
	void Free();
};

END