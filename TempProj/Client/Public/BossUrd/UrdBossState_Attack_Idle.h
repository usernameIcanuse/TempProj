#pragma once
#include "BossUrd/UrdBossState_IdleStates.h"

BEGIN(Engine)
class CModel;
END

BEGIN(Client)

class CUrdBossState_Attack_Idle :
	public CUrdBossState_IdleStates
{
	GAMECLASS_H(CUrdBossState_Attack_Idle);
	CLONE_H(CUrdBossState_Attack_Idle, CComponent)
		SHALLOW_COPY(CUrdBossState_Attack_Idle)



protected:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Start() override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;

protected:
	virtual void OnStateStart(const _float& In_fAnimationBlendTime) override;
	virtual void OnStateEnd() override;
	virtual _bool Check_AndChangeNextState() override;
	virtual void OnEventMessage(_uint iArg) override;
private:
	_uint       m_iPreCount = 5;

private:
//	void Call_AnimationEnd(_uint iEndAnimIndex);
protected:
	//virtual void OnDestroy() override;
	void Free();

};

END






