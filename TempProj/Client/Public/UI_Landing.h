#pragma once
#include "UI.h"



BEGIN(Client)
class CCustomUI;
class CHUD_Hover;
class CFadeMask;


class CEasingComponent_Alpha;
class CEasingComponent_Float;

class CUI_Landing : public CUI
{
public:
	//������� ȭ��� ã���� ��, �÷��̾� �׾�����, ���� �׿�����, �������� ������ ��, ���� �÷��̾� �װ� ȸ��������
	enum LANDING_TYPE {
		LANDING_BECONFOUND,
		LANDING_DEAD,
		LANDING_KILL_BOSS,
		LANDING_ENTER_STAGE, 
		LANDING_END
	};

	GAMECLASS_H(CUI_Landing);
	CLONE_H(CUI_Landing, CGameObject);

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Start();
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render(ID3D11DeviceContext* pDeviceContext);


public:
	void					Call_Landing(LANDING_TYPE eLandingType);
	void					Call_Landing(LANDING_TYPE eLandingType, _float fCallTime);


private:
	LANDING_TYPE			m_ePreCalledLanding;
	weak_ptr<CHUD_Hover>	m_pLanding;
	weak_ptr<CHUD_Hover>	m_pLandingBG;

	UI_DESC					m_tLandingUIDesc[LANDING_END];

	FaderDesc				m_tLandingFaderDesc;
	string					m_LandingTextures[LANDING_END];

public:
	void			Call_FadeEnd(FADER_TYPE eFaderType);
	void			Call_TimerEnd();


private://For Blur
	weak_ptr<CEasingComponent_Alpha>		m_pEasingBlurAmount;
	weak_ptr<CEasingComponent_Float>		m_pEasingFloat;

	weak_ptr<CFadeMask>						m_pFadeMask;
};

END
