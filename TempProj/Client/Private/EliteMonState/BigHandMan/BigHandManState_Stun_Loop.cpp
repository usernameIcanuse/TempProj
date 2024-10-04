#include "stdafx.h"
#include "VargBossStateBase.h"
#include "Model.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "Player.h"
//#include "BehaviorBase.h"
#include "Animation.h"
#include "Character.h"
#include "EliteMonState/BigHandMan/BigHandManStates.h"



GAMECLASS_C(CBigHandManState_Stun_Loop);
CLONE_C(CBigHandManState_Stun_Loop, CComponent)

HRESULT CBigHandManState_Stun_Loop::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CBigHandManState_Stun_Loop::Initialize(void* pArg)
{
	__super::Initialize(pArg);


	return S_OK;
}

void CBigHandManState_Stun_Loop::Start()
{
	__super::Start();

	//���̳� �Ͼ��ÿ��� ���̵�� ������ ��ũ�� ������ 

	m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LV2Villager_M.ao|LV2Villager01_M_Stun_Loop");


	
}

void CBigHandManState_Stun_Loop::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_pModelCom.lock()->Play_Animation(fTimeDelta);
}


void CBigHandManState_Stun_Loop::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	Check_AndChangeNextState();
}



void CBigHandManState_Stun_Loop::OnStateStart(const _float& In_fAnimationBlendTime)
{
	__super::OnStateStart(In_fAnimationBlendTime);



	m_pModelCom.lock()->Set_CurrentAnimation(m_iAnimIndex);

#ifdef _DEBUG
#ifdef _DEBUG_COUT_
	cout << "BigHandManState: Idle -> OnStateStart" << endl;
#endif
#endif


}

void CBigHandManState_Stun_Loop::OnStateEnd()
{
	__super::OnStateEnd();


}



void CBigHandManState_Stun_Loop::Free()
{

}

_bool CBigHandManState_Stun_Loop::Check_AndChangeNextState()
{

	if (!Check_Requirement())
		return false;


	if (Get_OwnerMonster()->Get_EliteExecutionStartOnOff())
	{
		Get_OwnerCharacter().lock()->Change_State<CBigHandManState_VS_TakeExecution_01>(0.05f);
		return true;
	}


	return false;
}


