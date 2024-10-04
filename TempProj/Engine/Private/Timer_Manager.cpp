#include "Timer_Manager.h"
#include "Timer.h"

IMPLEMENT_SINGLETON(CTimer_Manager)

void CTimer_Manager::Reserve_TimeScaleLayer(_uint iNumLayers)
{
	m_TimeScaleLayers.reserve(iNumLayers);

	for (_uint i = 0; i < iNumLayers; i++)
	{
		m_TimeScaleLayers.push_back(1.f);
	}

}

void CTimer_Manager::Tick(const _float& _fOriginDeltaTime, const _float& _fTimeScale)
{
	for (auto iter = m_TimerEvents.begin(); iter != m_TimerEvents.end();)
	{
		if (!(*iter).pInstance.lock().get())
		{
			iter = m_TimerEvents.erase(iter);
			continue;
		}

		if ((*iter).fCurTime < 0.f)
		{
			(*iter).pInstance.lock()->OnTimerEvent((*iter).iEventNum);

			if ((*iter).bLoop)
			{
				(*iter).fCurTime = (*iter).fMaxTime;
				continue;
			}
			else
			{
				iter = m_TimerEvents.erase(iter);
				continue;
			}
		}

		if ((*iter).bAlwaysCall)
		{
			(*iter).pInstance.lock()->OnTimerEvent((*iter).iEventNum);
		}

		(*iter).fCurTime -= (_float)(_fOriginDeltaTime * (_float)((*iter).bUseTimeScale ? _fTimeScale : 1.f));
		iter++;
	}

}

HRESULT CTimer_Manager::Add_Timer(_uint eTimer)
{
	if (nullptr != Find_Timer(eTimer))
		return E_FAIL;

	shared_ptr<CTimer> pTimer = CTimer::Create();
	if (nullptr == pTimer)
		return E_FAIL;

	m_Timers.emplace(eTimer, pTimer);

	return S_OK;
}

_float CTimer_Manager::Compute_Timer(_uint eTimer)
{
	shared_ptr<CTimer> pTimer;

	// Ÿ�̸Ӹ� Find�ϸ� ������ ���ϰ� �����.
	// ���α׷��� �������� ȣ��Ǵ� Ÿ�̸Ӱ� �ִ�.
	// �ش� Ÿ�̸Ӹ� �� ��������(�󵵰� Tick���� ����.) �׷��ٸ� Find�ϴ°� ������?
	// ���� �ʴ�. ���� 0�� Ÿ�̸Ӵ� ���� �ð��� �˻��ϴ� Ÿ�̸ӷ� ������Ų��.
	if (0 == eTimer)
	{
		pTimer = (*m_Timers.begin()).second;
	}

	else
	{
		pTimer = Find_Timer(eTimer);
	}


	if (nullptr == pTimer.get())
		return 0.f;

	return pTimer->Compute_Timer();
}

void CTimer_Manager::Set_TimeScale(_uint In_iIndex, _float In_fTimeScale)
{
	m_TimeScaleLayers[In_iIndex] = In_fTimeScale;
}

_float CTimer_Manager::Get_TimeScale(_uint In_iIndex)
{
	return m_TimeScaleLayers[In_iIndex];
}

HRESULT CTimer_Manager::Add_TimerEvent(_uint _iEventNum, weak_ptr<CBase> _Instance, _float _fTime, _bool _bLoop, _bool _bUseTimeScale, _bool _bAlwaysCall)
{
	TIMEREVENT TimerEvent;

	TimerEvent.fMaxTime = TimerEvent.fCurTime = _fTime;
	TimerEvent.iEventNum = _iEventNum;
	TimerEvent.pInstance = _Instance;
	TimerEvent.bLoop = _bLoop;
	TimerEvent.bUseTimeScale = _bUseTimeScale;
	TimerEvent.bAlwaysCall = _bAlwaysCall;

	m_TimerEvents.push_back(TimerEvent);

	return S_OK;
}

shared_ptr<CTimer> CTimer_Manager::Find_Timer(_uint eTimer)
{

	auto iter = m_Timers.find(eTimer);

	if (m_Timers.end() == iter)
	{
		return shared_ptr<CTimer>();
	}

	return (*iter).second;
}

void CTimer_Manager::Free()
{

	m_Timers.clear();
}
