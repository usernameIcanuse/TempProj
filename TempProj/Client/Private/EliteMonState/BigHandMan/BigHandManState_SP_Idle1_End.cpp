#include "stdafx.h"
#include "Model.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "Player.h"
//#include "BehaviorBase.h"
#include "Animation.h"
#include "Character.h"
#include "EliteMonState/BigHandMan/BigHandManStates.h"



GAMECLASS_C(CBigHandManState_SP_Idle1_End);
CLONE_C(CBigHandManState_SP_Idle1_End, CComponent)

HRESULT CBigHandManState_SP_Idle1_End::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CBigHandManState_SP_Idle1_End::Initialize(void* pArg)
{
	__super::Initialize(pArg);


	return S_OK;
}

void CBigHandManState_SP_Idle1_End::Start()
{
	__super::Start();

	//���̳� �Ͼ��ÿ��� ���̵�� ������ ��ũ�� ������ 

	m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LV2Villager_M.ao|LV2Villager01_M_SP_Idle1_End");


	m_pModelCom.lock()->CallBack_AnimationEnd += bind(&CBigHandManState_SP_Idle1_End::Call_AnimationEnd, this, placeholders::_1);
}

void CBigHandManState_SP_Idle1_End::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_pModelCom.lock()->Play_Animation(fTimeDelta);
}


void CBigHandManState_SP_Idle1_End::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	Check_AndChangeNextState();
}



void CBigHandManState_SP_Idle1_End::OnStateStart(const _float& In_fAnimationBlendTime)
{
	__super::OnStateStart(In_fAnimationBlendTime);

	
	

	m_pModelCom.lock()->Set_CurrentAnimation(m_iAnimIndex);

#ifdef _DEBUG
#ifdef _DEBUG_COUT_
	cout << "BigHandManState: Idle -> OnStateStart" << endl;
#endif
#endif


}

void CBigHandManState_SP_Idle1_End::OnStateEnd()
{
	__super::OnStateEnd();


}

void CBigHandManState_SP_Idle1_End::Call_AnimationEnd(_uint iEndAnimIndex)
{
	if (!Get_Enable())
		return;

	
}

void CBigHandManState_SP_Idle1_End::OnDestroy()
{
	m_pModelCom.lock()->CallBack_AnimationEnd -= bind(&CBigHandManState_SP_Idle1_End::Call_AnimationEnd, this, placeholders::_1);
}

void CBigHandManState_SP_Idle1_End::Free()
{

}

_bool CBigHandManState_SP_Idle1_End::Check_AndChangeNextState()
{

	if (!Check_Requirement())
		return false;


	return false;
}

