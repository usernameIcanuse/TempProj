#include "stdafx.h"
#include "VargBossStateBase.h"
#include "EliteMonState/Joker/JokerState_TurnR90.h"
#include "Model.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "Player.h"
//#include "BehaviorBase.h"
#include "Animation.h"
#include "Character.h"
#include "JokerStates.h"



GAMECLASS_C(CJokerState_TurnR90);
CLONE_C(CJokerState_TurnR90, CComponent)

HRESULT CJokerState_TurnR90::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CJokerState_TurnR90::Initialize(void* pArg)
{
	__super::Initialize(pArg);


	return S_OK;
}

void CJokerState_TurnR90::Start()
{
	__super::Start();

	//���̳� �Ͼ��ÿ��� ���̵�� ������ ��ũ�� ������ 

	m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Joker_TurnR90");


	m_pModelCom.lock()->CallBack_AnimationEnd += bind(&CJokerState_TurnR90::Call_AnimationEnd, this, placeholders::_1);
}

void CJokerState_TurnR90::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_pModelCom.lock()->Play_Animation(fTimeDelta);
}


void CJokerState_TurnR90::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	_float fTurnValue = 1.57f / 1.333f;

	m_pTransformCom.lock()->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), fTimeDelta * fTurnValue * 1.5f);

	Check_AndChangeNextState();
}



void CJokerState_TurnR90::OnStateStart(const _float& In_fAnimationBlendTime)
{
	__super::OnStateStart(In_fAnimationBlendTime);

	m_pModelCom.lock()->Set_CurrentAnimation(m_iAnimIndex);

#ifdef _DEBUG
#ifdef _DEBUG_COUT_
	cout << "VargState: Idle -> OnStateStart" << endl;
#endif
#endif

	m_pModelCom.lock()->Set_AnimationSpeed(1.5f);
}

void CJokerState_TurnR90::OnStateEnd()
{
	__super::OnStateEnd();

	m_pModelCom.lock()->Set_AnimationSpeed(1.f);
}

void CJokerState_TurnR90::Call_AnimationEnd(_uint iEndAnimIndex)
{
	if (!Get_Enable())
		return;

	Get_OwnerCharacter().lock()->Change_State<CJokerState_Idle>(0.05f);
}

void CJokerState_TurnR90::OnDestroy()
{
	m_pModelCom.lock()->CallBack_AnimationEnd -= bind(&CJokerState_TurnR90::Call_AnimationEnd, this, placeholders::_1);
}

void CJokerState_TurnR90::Free()
{

}

_bool CJokerState_TurnR90::Check_AndChangeNextState()
{

	if (!Check_Requirement())
		return false;

	if (ComputeAngleWithPlayer() > 0.94f)
	{
		Rotation_TargetToLookDir();
		Get_Owner().lock()->Get_Component<CJokerState_Idle>().lock()->Set_TurnCheck(false);
		Get_OwnerCharacter().lock()->Change_State<CJokerState_Idle>(0.05f);
		return true;
	}

	return false;
}

