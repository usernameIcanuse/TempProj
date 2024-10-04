#pragma once
#include "NorMonsterStateBase.h"

BEGIN(Engine)
class CModel;
END

BEGIN(Client)

class CNorMonState_Suprise_Attack :
	public CNorMonsterStateBase
{
	GAMECLASS_H(CNorMonState_Suprise_Attack);
	CLONE_H(CNorMonState_Suprise_Attack, CComponent)
		SHALLOW_COPY(CNorMonState_Suprise_Attack)

public:
	_float      Cul_DotResult();
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


private:

	//virtual void OnEventMessage(_uint iArg) override;

private:
//	void Call_AnimationEnd(_uint iEndAnimIndex);
protected:
	//virtual void OnDestroy() override;
	void Free();

};

END

