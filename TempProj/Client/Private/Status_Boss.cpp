#include "stdafx.h"
#include "Status_Boss.h"

GAMECLASS_C(CStatus_Boss)
CLONE_C(CStatus_Boss, CComponent)


HRESULT CStatus_Boss::Initialize(void* pArg)
{
	__super::Initialize(pArg);


	return S_OK;
}


void CStatus_Boss::Update_HitedTime(_float fTimeDelta)
{
	//���� �ֱٿ� ���� �ð��� ���� ó���Ǵ� �װ�... �޶���.

	if (m_tMonsterDesc.m_fHitedTime >= m_tMonsterDesc.m_fHpBarDisableTime)//15
	{
		return;
	}
	else if (m_tMonsterDesc.m_fHitedTime >= m_tMonsterDesc.m_fRecoveryTime)//8
	{
		//ü�� ȸ�� ����, UI�� ü�� ȸ�� ������ ����.
		CallBack_RecoeoryStart();

		m_tMonsterDesc.m_fCurrentHP_white = min
		(
			m_tMonsterDesc.m_fCurrentHP_white += ((m_tMonsterDesc.m_fMaxHP_white *
				m_tMonsterDesc.m_fRecoveryAmountPercentageFromSecond) *
				m_tMonsterDesc.m_fRecoveryMag) * fTimeDelta,
			m_tMonsterDesc.m_fCurrentHP_Green);

		return;
	}
	else if (m_tMonsterDesc.m_fHitedTime >= m_tMonsterDesc.m_fRecoveryAlramTime)//5
	{
		//ü�� ȸ�� �˶�
		if (m_tMonsterDesc.m_fCurrentHP_Green > 0.f &&
			(m_tMonsterDesc.m_fCurrentHP_white < m_tMonsterDesc.m_fCurrentHP_Green))
			CallBack_RecoeoryAlram();

		return;
	}
}

void CStatus_Boss::Set_NextPhase()
{
	m_tMonsterDesc.m_fCurrentHP_white = m_tMonsterDesc.m_fMaxHP_white;
	m_tMonsterDesc.m_fCurrentHP_Green = m_tMonsterDesc.m_fMaxHP_Green;
	m_tMonsterDesc.m_fCurrentParryingGauge = 0.f;
	m_tMonsterDesc.m_iLifeCount -= 1;

	Callback_NextPhase();
}

void CStatus_Boss::Minus_LifePoint(_uint iPoint)
{
	m_tMonsterDesc.m_iLifeCount -= iPoint;
}
