#include "stdafx.h"
#include "NorMonState/NorMonState_Idle.h"
#include "Model.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "Player.h"
//#include "BehaviorBase.h"
#include "Animation.h"
#include "AIStateBase.h"
#include "NorMonStateS.h"
#include "Character.h"
#include "Collider.h"
#include "Attack_Area.h"



GAMECLASS_C(CNorMonState_Idle);
CLONE_C(CNorMonState_Idle, CComponent)

void CNorMonState_Idle::Set_MonIdleType(NORMONSTERIDLETYPE IDLETYPE)
{
	m_eNorMonIdleType = IDLETYPE;
}

HRESULT CNorMonState_Idle::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CNorMonState_Idle::Initialize(void* pArg)
{
	__super::Initialize(pArg);




	return S_OK;
}

void CNorMonState_Idle::Start()
{
	__super::Start();


	if (m_eMonType == MONSTERTYPE::AXEMAN)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Armature|Armature|Armature|Armature|DemoM02_Idle1|BaseLayer|Armature|Arm");
			break;
		case Client::NORMONSTERIDLETYPE::SITIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Armature|Armature|Armature|Armature|LV1Villager_M_Sit_Idle|BaseLayer|Arm");
			break;
		case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Armature|Armature|Armature|Armature|LV1Villager_M_SP_Idle1|BaseLayer|Arm");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Armature|Armature|Armature|Armature|DemoM02_Idle1|BaseLayer|Armature|Arm");
			break;
		}
	}

	if (m_eMonType == MONSTERTYPE::KNIFEWOMAN)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LV0Villager_F.ao|LV1Villager_F_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::SITIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LV0Villager_F.ao|LV1Villager_F_Sit_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LV0Villager_F.ao|LV1Villager_F_SP_Idle1");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LV0Villager_F.ao|LV1Villager_F_Idle");
			break;
		}
	}

	if (m_eMonType == MONSTERTYPE::GARDENER)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_Gardener01_Base01.ao|Gardener_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::SITIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_Gardener01_Base01.ao|Gardener_Sit_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_Gardener01_Base01.ao|Gardener_SP_Idle1");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_Gardener01_Base01.ao|Gardener_Idle");
			break;
		}
	}

	if (m_eMonType == MONSTERTYPE::ENHANCE_GARDENER)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_Gardener01_Base01.ao|Gardener_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_Gardener01_Base01.ao|Gardener_Idle");
			break;
		}
	}

	if (m_eMonType == MONSTERTYPE::SHIELDAXEMAN)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Armature|Armature|Armature|Armature|DemoM02_Idle1|BaseLayer|Armature|Arm");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Armature|Armature|Armature|Armature|DemoM02_Idle1|BaseLayer|Armature|Arm");
			break;
		}
	}

	if (m_eMonType == MONSTERTYPE::BALLOON)
	{
		m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Armature|Idle|Idle");
	}

	if (m_eMonType == MONSTERTYPE::SKULLSPEARMAN)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|HArmorLV1_Halberds_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::SITIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|HArmor_Halberds_Sit_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|HArmor_Halberds_SP_Idle2");
			break;
		case Client::NORMONSTERIDLETYPE::SPIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|HArmor_Halberds_SP_Idle1");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|HArmorLV1_Halberds_Idle");
			break;

		}
	}

	if (m_eMonType == MONSTERTYPE::SKULLSHIELDMAN)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|LArmor_Shield_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::SITIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|LArmor_Shield_Sit_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|LArmor_Shield_SP_Idle2");
			break;
		case Client::NORMONSTERIDLETYPE::SPIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|LArmor_Shield_SP_Idle1");
			break;
		case Client::NORMONSTERIDLETYPE::RUNATTACKIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|LArmor_Shield_IdleN");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV0_02.ao|LArmor_Shield_Idle");
			break;

		}

	}

	if (m_eMonType == MONSTERTYPE::ARMORSHIELDMAN)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|LArmor_Shield_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::SITIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|LArmor_Shield_Sit_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|LArmor_Shield_SP_Idle2");
			break;
		case Client::NORMONSTERIDLETYPE::SPIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|LArmor_Shield_SP_Idle1");
			break;
		case Client::NORMONSTERIDLETYPE::RUNATTACKIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|LArmor_Shield_IdleN");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|LArmor_Shield_Idle");
			break;
		}
	}

	if (m_eMonType == MONSTERTYPE::WEAKARMORSHIELDMAN)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV1_01.ao|LArmor_Shield_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::SITIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV1_01.ao|LArmor_Shield_Sit_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV1_01.ao|LArmor_Shield_SP_Idle2");
			break;
		case Client::NORMONSTERIDLETYPE::SPIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV1_01.ao|LArmor_Shield_SP_Idle1");
			break;
		case Client::NORMONSTERIDLETYPE::RUNATTACKIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV1_01.ao|LArmor_Shield_IdleN");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV1_01.ao|LArmor_Shield_Idle");
			break;

		}
	}


	if (m_eMonType == MONSTERTYPE::ARMORSPEARMAN)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|HArmorLV1_Halberds_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::SITIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|HArmor_Halberds_Sit_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|HArmor_Halberds_SP_Idle2");
			break;
		case Client::NORMONSTERIDLETYPE::SPIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|HArmor_Halberds_SP_Idle1");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|HArmorLV1_Halberds_Idle");
			break;

		}
	}


	if (m_eMonType == MONSTERTYPE::WEAKARMORSPEARMAN)
	{
		switch (m_eNorMonIdleType)
		{
		case Client::NORMONSTERIDLETYPE::NORIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV1_01.ao|HArmorLV1_Halberds_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::SITIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV1_01.ao|HArmor_Halberds_Sit_Idle");
			break;
		case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV1_01.ao|HArmor_Halberds_SP_Idle2");
			break;
		case Client::NORMONSTERIDLETYPE::SPIDLE:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_LArmorLV1_01.ao|HArmor_Halberds_SP_Idle1");
			break;
		case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
			m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("SK_C_HArmorTypeLV1_01.ao|HArmorLV1_Halberds_Idle");
			break;

		}
	}
}




void CNorMonState_Idle::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	//Turn_Transform(fTimeDelta);
	m_pModelCom.lock()->Play_Animation(fTimeDelta);
}

void CNorMonState_Idle::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	//TODO �����ȵſ� ȭ����
	//if (Get_OwnerCharacter().lock()->Get_PreState().lock() == Get_Owner().lock()->Get_Component<CNorMonState_Awake>().lock())
	//{
	//	m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Armature|Armature|Armature|Armature|LV1Villager_M_IdleGeneral|BaseLayer");
	//}
	//
	//if (Get_OwnerCharacter().lock()->Get_PreState().lock() == Get_Owner().lock()->Get_Component<CNorMonState_SitToIdle>().lock())
	//{
	//	m_iAnimIndex = m_pModelCom.lock()->Get_IndexFromAnimName("Armature|Armature|Armature|Armature|LV1Villager_M_IdleGeneral|BaseLayer");
	//}


	Check_AndChangeNextState();

}


void CNorMonState_Idle::OnStateStart(const _float& In_fAnimationBlendTime)
{
	__super::OnStateStart(In_fAnimationBlendTime);


	m_pModelCom.lock()->Set_CurrentAnimation(m_iAnimIndex);


#ifdef _DEBUG
#ifdef _DEBUG_COUT_
	cout << "NorMonState: IdleIDLEIDLE -> OnStateStart" << endl;
#endif
#endif


}

void CNorMonState_Idle::OnStateEnd()
{
	__super::OnStateEnd();

}

void CNorMonState_Idle::OnEventMessage(_uint iArg)
{
	__super::OnEventMessage(iArg);

	if ((_uint)EVENT_TYPE::ON_RESET_OBJ == iArg)
	{
	     m_bClosePlayerCheck = false;
	     m_bCloseToRun = false;
	     m_bGoAtk = false;
	     m_iIdleType = 0; // �̰� enum���� �����ϸ�ɵ�  ���ϰ��Ұ��� ����
	}
}

void CNorMonState_Idle::Free()
{

}

_bool CNorMonState_Idle::Check_AndChangeNextState()
{
	if (!Check_Requirement())
		return false;

	weak_ptr<CPlayer> pCurrentPlayer = GET_SINGLE(CGameManager)->Get_CurrentPlayer();

	if (!pCurrentPlayer.lock())
		return false;

	if (KEY_INPUT(KEY::NUM3, KEY_STATE::TAP))
	{
		switch (m_eMonType)
		{

		case Client::MONSTERTYPE::ARMORSHIELDMAN:
			Get_OwnerCharacter().lock()->Change_State<CNorMonState_TakeExecution>(0.05f);
			break;
		case Client::MONSTERTYPE::WEAKARMORSHIELDMAN:
			Get_OwnerCharacter().lock()->Change_State<CNorMonState_TakeExecution>(0.05f);
			break;
		case Client::MONSTERTYPE::ARMORSPEARMAN:
			Get_OwnerCharacter().lock()->Change_State<CNorMonState_TakeExecution>(0.05f);
			break;
		case Client::MONSTERTYPE::WEAKARMORSPEARMAN:
			Get_OwnerCharacter().lock()->Change_State<CNorMonState_TakeExecution>(0.05f);
			break;

		}
		return true;
	}
		
	

_float fPToMDistance = Get_DistanceWithPlayer(); // �÷��̾�� ���� �Ÿ�
_float fMToMDistance = GetStartPositionToCurrentPositionDir(); // ���ͽ�ŸƮ�����ǰ� �������� ������ ������ �Ÿ�

if (!m_bPatrol)
{
	if (fMToMDistance >= 20.f) // �Ÿ�20���ٸ־����� �ٸ��� �ٲ��� ���ư��Ա� 30���ٸ־����� Ʈ����
	{
		m_iIdleType = 3;
	}

	// 1. ���̵���º��� �˻�  �ٵ��̋��� �Ÿ��� �������������
	// ù��°�ξ��̵������ ������ ��ģ���� ��������
	if (fPToMDistance <= 5.f && m_iIdleType == 0)
	{

		switch (m_eMonType)
		{
		case Client::MONSTERTYPE::AXEMAN:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SITIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SitToIdle>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;

			}
			break;
		case Client::MONSTERTYPE::KNIFEWOMAN:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SITIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SitToIdle>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::SKULL:
			break;
		case Client::MONSTERTYPE::GARDENER:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SITIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SitToIdle>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::ENHANCE_GARDENER:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::SHIELDAXEMAN:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::SKULLSHIELDMAN:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SITIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SitToIdle>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SPIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::RUNATTACKIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SpecialAttackStart>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::SKULLSPEARMAN:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SITIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SitToIdle>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SPIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::ARMORSHIELDMAN:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SITIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SitToIdle>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SPIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::RUNATTACKIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SpecialAttackStart>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::WEAKARMORSHIELDMAN:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SITIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SitToIdle>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SPIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::RUNATTACKIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SpecialAttackStart>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::ARMORSPEARMAN:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SITIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SitToIdle>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SPIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::WEAKARMORSPEARMAN:
			switch (m_eNorMonIdleType)
			{
			case Client::NORMONSTERIDLETYPE::NORIDLE:
				TurnMechanism();
				break;
			case Client::NORMONSTERIDLETYPE::SITIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_SitToIdle>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::FIDGETIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SPIDLE:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Awake>(0.05f);
				break;
			case Client::NORMONSTERIDLETYPE::SUPRISEATTACK:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Suprise_Attack>(0.05f);
				break;
			}
			break;

		}
		m_iIdleType = 1;
		m_bCloseToRun = true;
		return true;

	}

	// 2.�系�� ������ �ٽþ��̵�ο� ����´� ������ NORIDLE������
	// ���̵�Ÿ������ ���԰� �̶� �ϰ˻��ѹ� ���ؾ��� 90���� ���������̰ų�
	// 90����ū�����ϋ� �˻縦�ؾ��ϱ⿡ ���� �⺻���̵鵵 ����̾ƴ�
	// �⺻���̵��̸� �����������
	if (m_bCloseToRun && m_iIdleType == 1)
	{

		switch (m_eMonType)
		{
		case Client::MONSTERTYPE::AXEMAN:
			TurnMechanism();
			break;
		case Client::MONSTERTYPE::KNIFEWOMAN:
			TurnMechanism();
			break;
		case Client::MONSTERTYPE::SKULL:
			break;
		case Client::MONSTERTYPE::GARDENER:
			TurnMechanism();
			break;
		case Client::MONSTERTYPE::ENHANCE_GARDENER:
			TurnMechanism();
			break;
		case Client::MONSTERTYPE::SHIELDAXEMAN:
			TurnMechanism();
			break;
		case Client::MONSTERTYPE::SKULLSHIELDMAN:
			TurnMechanism();
			break;
		case Client::MONSTERTYPE::SKULLSPEARMAN:
			TurnMechanism();
			break;
		case Client::MONSTERTYPE::ARMORSHIELDMAN:
			TurnMechanism();
			break;
		case Client::MONSTERTYPE::WEAKARMORSHIELDMAN:
			TurnMechanism();
			break;
		case Client::MONSTERTYPE::ARMORSPEARMAN:
			TurnMechanism();
			break;
		case Client::MONSTERTYPE::WEAKARMORSPEARMAN:
			TurnMechanism();
			break;

		}


		m_iIdleType = 2;
		m_bClosePlayerCheck = true;
		return true;
	}
	//�̷��� ���ִ°Ŵ� �ϰ˻縦�߰� ����λ��°� �������� 90����ŭ���������� (�װź�����������)
	//������ ��������ؼ� 90����ũ�� �ٽ��ϰ˻��ϰ� �ƴϸ� �����ڵ�ΰ��ߵ�

	if (fPToMDistance <= 5.f && m_iIdleType == 2)
	{

		switch (m_eMonType)
		{
		case Client::MONSTERTYPE::AXEMAN:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				}
			}
			break;
		case Client::MONSTERTYPE::KNIFEWOMAN:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				}
			}
			break;
		case Client::MONSTERTYPE::SKULL:
			break;
		case Client::MONSTERTYPE::GARDENER:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				}
			}
			break;
		case Client::MONSTERTYPE::ENHANCE_GARDENER:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				}
			}
			break;
		case Client::MONSTERTYPE::SHIELDAXEMAN:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				}
			}
			break;
		case Client::MONSTERTYPE::SKULLSHIELDMAN:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				}
			}
			break;
		case Client::MONSTERTYPE::SKULLSPEARMAN:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				}
			}
			break;
		case Client::MONSTERTYPE::ARMORSHIELDMAN:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				}
			}
			break;
		case Client::MONSTERTYPE::WEAKARMORSHIELDMAN:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				}
			}
			break;
		case Client::MONSTERTYPE::ARMORSPEARMAN:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				}
			}
			break;
		case Client::MONSTERTYPE::WEAKARMORSPEARMAN:
			if (ComputeAngleWithPlayer() <= 0.f)
			{
				TurnMechanism();
			}
			else
			{
				Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
				m_bClosePlayerCheck = true;
				m_bCloseToRun = true;
				int iRunORWalk = rand() % 2;
				switch (iRunORWalk)
				{
				case 0:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
					break;
				case 1:
					Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
					break;
				}
			}
			break;
		}


		return true;
	}

	//
	if (m_bCloseToRun && m_iIdleType == 2 && m_bClosePlayerCheck)
	{
		Get_Owner().lock()->Get_Component<CNorMonState_Run>().lock()->Set_ClosePlayer(true);
		int iRunORWalk = rand() % 2;

		switch (m_eMonType)
		{
		case Client::MONSTERTYPE::AXEMAN:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::KNIFEWOMAN:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::SKULL:
			break;
		case Client::MONSTERTYPE::GARDENER:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::ENHANCE_GARDENER:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::SHIELDAXEMAN:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::SKULLSHIELDMAN:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::SKULLSPEARMAN:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::ARMORSHIELDMAN:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::WEAKARMORSHIELDMAN:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
				break;
			}
			break;
		case Client::MONSTERTYPE::ARMORSPEARMAN:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.05f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.1f);
				break;
			}
			break;
		case Client::MONSTERTYPE::WEAKARMORSPEARMAN:
			switch (iRunORWalk)
			{
			case 0:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Run>(0.1f);
				break;
			case 1:
				Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_F>(0.05f);
				break;
			}
			break;
		}

		return true;
	}


	if (m_iIdleType == 3)
	{
		Get_OwnerCharacter().lock()->Change_State<CNorMonState_Walk_B>(0.05f);
		return true;
	}

}
    else
    {
        Get_OwnerCharacter().lock()->Change_State<CNorMonState_Petrol>(0.05f);
        return true;
    }

	




	return false;
}

