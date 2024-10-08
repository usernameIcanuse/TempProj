#include "stdafx.h"
#include "CorvusStates/CorvusState_SprintAttack.h"
#include "Model.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "BehaviorBase.h"
#include "Animation.h"
#include "Player.h"
#include "CorvusStates/CorvusStates.h"
#include "PhysXCharacterController.h"

GAMECLASS_C(CCorvusState_SprintAttack);
CLONE_C(CCorvusState_SprintAttack, CComponent)

HRESULT CCorvusState_SprintAttack::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}

HRESULT CCorvusState_SprintAttack::Initialize(void* pArg)
{
	__super::Initialize(pArg);


	return S_OK;
}

void CCorvusState_SprintAttack::Start()
{
	__super::Start();
	m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Corvus_SD_SprintAttack_1");
	m_pModelCom.lock()->CallBack_AnimationEnd += bind(&CCorvusState_SprintAttack::Call_AnimationEnd, this, placeholders::_1);
}

void CCorvusState_SprintAttack::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_pModelCom.lock()->Play_Animation(fTimeDelta);

	Attack();
}

void CCorvusState_SprintAttack::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	Check_InputNextAttack();

	if (Check_AndChangeNextState())
	{

	}
}

void CCorvusState_SprintAttack::Call_AnimationEnd(_uint iEndAnimIndex)
{
	if (!Get_Enable())
		return;

	Get_OwnerPlayer()->Change_State<CCorvusState_Idle>();

}


void CCorvusState_SprintAttack::Attack()
{

}

void CCorvusState_SprintAttack::Check_InputNextAttack()
{
	if (!KEY_INPUT(KEY::LBUTTON, KEY_STATE::TAP))
	{
		return;
	}

	m_IsNextAttack = true;


}



void CCorvusState_SprintAttack::OnStateStart(const _float& In_fAnimationBlendTime)
{
	__super::OnStateStart(In_fAnimationBlendTime);

	m_pModelCom.lock()->Set_CurrentAnimation(m_iAnimIndex);

	if (!m_pModelCom.lock().get())
	{
		m_pModelCom = m_pOwner.lock()->Get_Component<CModel>();
	}

	m_pPhysXControllerCom.lock()->Callback_ControllerHit +=
		bind(&CCorvusState_SprintAttack::Call_OtherControllerHit, this, placeholders::_1);


#ifdef _DEBUG
	#ifdef _DEBUG_COUT_
		cout << "NorMonState: Attack -> OnStateStart" << endl;
#endif

#endif
}

void CCorvusState_SprintAttack::OnStateEnd()
{
	__super::OnStateEnd();

	//Disable_Weapons();
	m_IsNextAttack = false;

	m_pPhysXControllerCom.lock()->Callback_ControllerHit +=
		bind(&CCorvusState_SprintAttack::Call_OtherControllerHit, this, placeholders::_1);
}

void CCorvusState_SprintAttack::OnEventMessage(_uint iArg)
{
	//__super::OnEventMessage(iArg);
	//
	//if ((_uint)EVENT_TYPE::ON_FIRSTHIT == iArg)
	//{
	//	switch (m_pModelCom.lock()->Get_CurrentAnimationIndex())
	//	{
	//	case 0:
	//		GAMEINSTANCE->PlaySoundW(TEXT("c_luciaRK3_atk_attack01.wav"), 1.f);
	//		break;
	//
	//	case 1:
	//		GAMEINSTANCE->PlaySoundW(TEXT("c_luciaRK3_atk_attack02.wav"), 1.f);
	//		break;
	//
	//	case 2:
	//		GAMEINSTANCE->PlaySoundW(TEXT("c_luciaRK3_atk_attack03.wav"), 1.f);
	//		break;
	//
	//	case 3:
	//		GAMEINSTANCE->PlaySoundW(TEXT("c_luciaRK3_atk_attack04.wav"), 1.f);
	//		break;
	//
	//	case 4:
	//		GAMEINSTANCE->PlaySoundW(TEXT("c_luciaRK3_atk_attack05.wav"), 1.f);
	//		break;
	//
	//	case 5:
	//		GAMEINSTANCE->PlaySoundW(TEXT("c_luciaRK3_atk_attack06.wav"), 1.f);
	//		break;
	//	}
	//}

}

void CCorvusState_SprintAttack::OnDestroy()
{
	m_pModelCom.lock()->CallBack_AnimationEnd -= bind(&CCorvusState_SprintAttack::Call_AnimationEnd, this, placeholders::_1);
}

void CCorvusState_SprintAttack::Free()
{

}

_bool CCorvusState_SprintAttack::Check_AndChangeNextState()
{
	if (!Check_Requirement())
		return false;



	if (m_bLockOn)
	{
		if (Check_RequirementNextAttackState())
		{
			if (Check_RequirementAttackState())
			{

				weak_ptr<CGameObject> pTargetObject;

				if (Check_RequirementExcuteState(pTargetObject))
				{
					_vector vTargetPos = pTargetObject.lock()->Get_Transform()->Get_Position();
					m_pTransformCom.lock()->LookAt2D(vTargetPos);
					Get_OwnerPlayer()->Change_State<CCorvusState_NorMob_Execution>();
					Get_OwnerPlayer()->Get_CurState().lock()->OnEventMessage(Weak_Cast<CBase>(pTargetObject));
				}
				else
				{
					if (!Rotation_InputToLookDir())
						Rotation_TargetToLookDir();

					Get_OwnerPlayer()->Change_State<CCorvusState_LAttack2>();

				}
				return true;
			}
		}

	}
	else
	{
		if (Check_RequirementNextAttackState())
		{
			if (Check_RequirementAttackState())
			{

				Rotation_InputToLookDir();
				Get_OwnerPlayer()->Change_State<CCorvusState_LAttack2>();

				return true;
			}
		}

	}




	return false;
}

_bool CCorvusState_SprintAttack::Check_RequirementNextAttackState()
{
	_uint iTargetKeyFrameFirst = 17;
	_uint iTargetKeyFrameSecond = 50;



	if (m_pModelCom.lock()->Is_CurrentAnimationKeyInRange(iTargetKeyFrameFirst, iTargetKeyFrameSecond)
&& m_IsNextAttack)
	{
		return true;
	}



	return false;
}

_bool CCorvusState_SprintAttack::Check_RuquireMnetFirstAttackState()
{
	_uint iTargetKeyFrameMin = 51;
	_uint iTargetKeyFrameMax = 80;







	if (m_pModelCom.lock()->Is_CurrentAnimationKeyInRange(iTargetKeyFrameMin, iTargetKeyFrameMax) && m_IsNextAttack)
	{
		return true;
	}



	return false;
}

