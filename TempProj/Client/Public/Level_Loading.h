#pragma once

/* �δ��� �ڿ���� �ε��ϴ� ���� ȭ�鿡 ������ �����ٲ���. */
/* �δ����� ��� ������� ������?? */
/* �� ����ϸ� ���������� ����.�� */

#include "Client_Defines.h"
#include "ClientLevel.h"

BEGIN(Client)


class CUI_Loading;

class CLevel_Loading final : public CClientLevel
{
public:
	CLevel_Loading();
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT Initialize(LEVEL eNextLevel);
	virtual void Tick(_float TimeDelta);
	virtual HRESULT Render(ID3D11DeviceContext* pDeviceContext);


private:
	void		Create_Level();

private:
	LEVEL			m_eNextLevel = LEVEL_END;
	shared_ptr<class CLoader>	m_pLoader;

	weak_ptr<CUI_Loading> m_pUILoading;

public:
	static shared_ptr<CLevel_Loading> Create(LEVEL eNextLevel);
	void Free();
};

END