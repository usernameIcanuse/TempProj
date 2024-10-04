#include "stdafx.h"
#include "CorvusStates/CorvusState_Climb_Fall_Attack.h"
#include "Model.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "BehaviorBase.h"
#include "Animation.h"
#include "CorvusStates/CorvusStates.h"
#include "PhysXController.h"

GAMECLASS_C(CCorvusState_Climb_Fall_Attack);
CLONE_C(CCorvusState_Climb_Fall_Attack, CComponent)

HRESULT CCorvusState_Climb_Fall_Attack::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CCorvusState_Climb_Fall_Attack::Initialize(void* pArg)
{
	__super::Initialize(pArg);

	return S_OK;
}

void CCorvusState_Climb_Fall_Attack::Start()
{
	__super::Start();
	m_pModelCom = m_pOwner.lock()->Get_Component<CModel>();
	m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Corvus_SD1_Fall_Attack");
	m_pModelCom.lock()->CallBack_AnimationEnd += bind(&CCorvusState_Climb_Fall_Attack::Call_AnimationEnd, this, placeholders::_1);
}

void CCorvusState_Climb_Fall_Attack::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_pModelCom.lock()->Play_Animation(fTimeDelta);
}

void CCorvusState_Climb_Fall_Attack::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	Check_AndChangeNextState();
}

void CCorvusState_Climb_Fall_Attack::Call_AnimationEnd(_uint iEndAnimIndex)
{
	if (!Get_Enable())
		return;

	Get_OwnerPlayer()->Change_State<CCorvusState_Idle>();

}

void CCorvusState_Climb_Fall_Attack::Call_NextKeyFrame(const _uint& In_KeyIndex)
{
	if (!Get_Enable())
		return;

	_vector fOffSet = { 0.f, -0.8771929824f ,0.f };

	PxControllerFilters Filters;

	m_pPhysXControllerCom.lock()->MoveWithRotation(fOffSet, 0.f, GAMEINSTANCE->Get_DeltaTime(),
		Filters, nullptr, m_pTransformCom);
}

void CCorvusState_Climb_Fall_Attack::OnStateStart(const _float& In_fAnimationBlendTime)
{
	__super::OnStateStart(In_fAnimationBlendTime);


	if (!m_pModelCom.lock().get())
	{
		m_pModelCom = m_pOwner.lock()->Get_Component<CModel>();
	}

	m_pModelCom.lock()->Set_CurrentAnimation(m_iAnimIndex);

		m_pThisAnimationCom = m_pModelCom.lock()->Get_CurrentAnimation();

	m_pThisAnimationCom.lock()->CallBack_NextChannelKey +=
		bind(&CCorvusState_Climb_Fall_Attack::Call_NextKeyFrame, this, placeholders::_1);

#ifdef _DEBUG
	#ifdef _DEBUG_COUT_
		cout << "NorMonState: Stop -> OnStateStart" << endl;
#endif

#endif
}

void CCorvusState_Climb_Fall_Attack::OnStateEnd()
{
	__super::OnStateEnd();

	m_pThisAnimationCom.lock()->CallBack_NextChannelKey -=
		bind(&CCorvusState_Climb_Fall_Attack::Call_NextKeyFrame, this, placeholders::_1);
}

void CCorvusState_Climb_Fall_Attack::OnDestroy()
{
	m_pModelCom.lock()->CallBack_AnimationEnd -= bind(&CCorvusState_Climb_Fall_Attack::Call_AnimationEnd, this, placeholders::_1);
}

void CCorvusState_Climb_Fall_Attack::Free()
{
	
}

_bool CCorvusState_Climb_Fall_Attack::Check_AndChangeNextState()
{
	if (!Check_Requirement())
		return false;

	return false;
}

