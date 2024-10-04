#pragma once

#include "Status.h"

BEGIN(Client)

class CStatus_Monster : public CStatus
{
public:
	GAMECLASS_H(CStatus_Monster)
		CLONE_H(CStatus_Monster, CComponent)
public:
	typedef struct tagMonsterDesc
	{
		_float m_fCurrentHP_white; //�������ü��
		_float m_fMaxHP_white; //��������ִ�ü��
		_float m_fCurrentHP_Green; // �����ʷϻ�ü��
		_float m_fMaxHP_Green; //�����ʷϻ��ִ�ü��
		_float m_fAtk; //���� ���ݷ�
		_float m_fHitedTime; //���ظ� ���� �ķκ��� ���� �ð�(�����븶���ʱ�ȭ)
		_float m_fParryGaugeRecoveryTime; //���ظ� ���� �ķκ��� ���� �ð�(�����븶���ʱ�ȭ)

		_float m_fRecoveryAlramTime; //���ü��ȸ������ð�
		_float m_fRecoveryTime; //ȸ�������ǽð�
		_float m_fRecoveryAmountPercentageFromSecond;//�ʴ� ���ۼ�Ʈ���� ȸ���Ҳ���(0~1��)
		_float m_fRecoveryMag;//����(���࿡, ���� ������ ȸ�� �ݱ�)
		_float m_fHpBarDisableTime; //ui�𽺿��̺�Ǳ�����ǽð�
		_float m_fCurrentParryingGauge; //�и������������ġ
		_float m_fMaxParryingGauge; //�и��������ִ��ġ
		_uint	m_iDropMemory;//������ ��

		_uint  m_iCueentParryCount; // �и��ϴ¸����� �и�ī��Ʈ
		_uint  m_iMaxParryCount; //  �и������ִ�ī��Ʈ�Ǹ��и�

		_uint  m_iLifeCount; // 1������ 2������ ���

		string	m_szModelKey;
		
	}MONSTERDESC;
	
	//Delegate
public:
	FDelegate<MONSTERDESC>		Callback_UpdateHP;
	FDelegate<_float>			CallBack_Damged_White;
	FDelegate<_float>			CallBack_Damged_Green;
	FDelegate<>					CallBack_UI_Disable;
	FDelegate<>					CallBack_RecoeoryStart;
	FDelegate<>					CallBack_RecoeoryAlram;
	FDelegate<>					CallBack_ReStart;
	FDelegate<_float, _bool>	CallBack_UpdateParryGauge;
	FDelegate<>					Callback_Full_Recovery;
	
	FDelegate<>					Callback_NextPhase;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Start();
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render(ID3D11DeviceContext* pDeviceContext) { return S_OK; }


public:
	void			Restart();

public:
	virtual _bool   Is_Dead();
	virtual void    Init_Status(const void* pArg);
	virtual void    Add_Damage(const _float In_fDamage, ATTACK_OPTION eAttackOption) override;
	virtual void    Full_Recovery() override;
	virtual _float	Get_WhiteRatio() {
		return m_tMonsterDesc.m_fCurrentHP_white / m_tMonsterDesc.m_fMaxHP_white
			;
	}
	
	virtual _float	Get_GreenRatio() {
		return m_tMonsterDesc.m_fCurrentHP_Green/ m_tMonsterDesc.m_fMaxHP_Green
			;
	}
	const tagMonsterDesc& Get_Desc() { return m_tMonsterDesc; }
	_float			Get_Atk() { return m_tMonsterDesc.m_fAtk; }
	virtual void    Get_Desc(void* Out_pDesc);

	void			Add_ParryGauge(const _float In_fDamage);
	_bool			Is_Groggy() const;

	void			Heal(_float fHealAmount);

protected:
	void			Decrease_White_HP(const _float In_fDamage);
	void			Decrease_Green_HP(const _float In_fDamage);

	void			Set_ParryRecoveryTime(const _float fRatio);

	virtual void	Update_HitedTime(_float fTimeDelta);
	void			Update_ParryRecoveryTime(_float fTimeDelta);

	void			Init_StatusFromMonsterType(MONSTERTYPE eMonsterType);


protected:
	MONSTERTYPE		m_eMonsterType;
	MONSTERDESC     m_tMonsterDesc;




private:
	void			Free();
};

END
