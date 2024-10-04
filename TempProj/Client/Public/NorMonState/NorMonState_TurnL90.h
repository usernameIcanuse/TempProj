#pragma once
#include "NorMonsterStateBase.h"

BEGIN(Engine)
class CModel;
END

BEGIN(Client)

class CNorMonState_TurnL90 :
	public CNorMonsterStateBase
{
	GAMECLASS_H(CNorMonState_TurnL90);
	CLONE_H(CNorMonState_TurnL90, CComponent)
		SHALLOW_COPY(CNorMonState_TurnL90)

protected:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Start() override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;

private:
	void   DirCheckTurnSpeed();



protected:
	virtual void OnStateStart(const _float& In_fAnimationBlendTime) override;
	virtual void OnStateEnd() override;
	virtual _bool Check_AndChangeNextState() override;

private:
	_float m_fTurnSpeed = 1.f;
	_float m_fTimeAcc = 0.f; // 1.3333�� �ִ̾ϸ��̼ǳ��� ���缭 �������ߵ� ����
	_bool  m_bStartAnimation = false; // �ִϸ��̼ǽ����Ҷ��̰����༭ �ִϸ��̼��̶����̳����ߵ�

private:
	void Call_AnimationEnd(_uint iEndAnimIndex);
protected:
	virtual void OnDestroy() override;
	void Free();

};

END
