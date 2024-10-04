#pragma once
#include "CustomUI.h"
#include "PlayerSkill_System.h"
BEGIN(Client)

class CCustomUI;
class CProgressBar;
class CHUD_Hover;
class CSkill_Base;


class CHUD_PlagueWeaponBase :
    public CCustomUI
{
	GAMECLASS_H(CHUD_PlagueWeaponBase);
	CLONE_H(CHUD_PlagueWeaponBase, CGameObject);
public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Start();
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	/*Delegate  From SkillSystem*/
	virtual void		Call_OnChangeSkill(weak_ptr<CSkill_Base> pSkillBase);

	/*Delegate From SkillBase*/
	virtual void		Call_UseStartSkill();
	virtual void		Call_UpdateCoolDown(_float fCoolDownRatio);
	virtual void		Call_EndCoolDown();

public:
	//HoverEvent
	virtual void			Call_HoverFadeEnd(FADER_TYPE eFaderType);
	
protected:
	virtual void			Bind_Player();//�÷��̾� ��ų �ý����� ���ε��ϴ� �Լ�


protected:
	virtual void			Init_UI();//���ھ�������, ���� �����Ҷ� �ʱ�ȭ �Կ��ֱ�
	void					Init_Icon(SKILL_NAME eSkillName);

	
	


private:
	virtual void			OnEnable(void* pArg) override;

	virtual void			OnDisable() override;

protected:
	CPlayerSkill_System::SOCKET_TYPE m_eSkillSocketType = CPlayerSkill_System::SOCKET_TYPE::SOCKET_END;
	weak_ptr<CCustomUI>		m_pPlagueWeapon_Main;//������
	weak_ptr<CProgressBar>	m_pPlagueWeapon_Ready;//��Ÿ�ӽÿ��� ������ ȸ�� ��
	weak_ptr<CProgressBar>	m_pPlagueWeapon_Border;//��Ÿ�� �˷��ִ� ������ ������
	weak_ptr<CCustomUI>		m_pIcon;
	weak_ptr<CHUD_Hover>	m_pHover;//��ų �� �� �������� ������ ����Ʈ.

protected:
	Engine::FaderDesc m_tFaderDesc; //For HUD_Hover;

public:
	void Free();

};

END