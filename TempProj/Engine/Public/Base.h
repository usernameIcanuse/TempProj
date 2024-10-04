#pragma once

#include "Engine_Defines.h"
#include "Json/Json_Utility.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	CBase() = default;
	virtual ~CBase() = default;


public:
	//�ش� ��ü�� Ȱ��ȭ ���¸� �ٲߴϴ�. Ȱ��ȭ ���°� ���Ѵٸ� OnEnable / OnDisable �̺�Ʈ �Լ��� ȣ���մϴ�.
	_bool Set_Enable(_bool _Enable, void* _Arg = nullptr);
	bool Get_Enable();

	void Set_ThisInstance(weak_ptr<CBase> Other);

	virtual void Write_Json(json& Out_Json) {};
	virtual void Load_FromJson(const json& In_Json) {};

public: /* For Event Function */
	//Ÿ�̸� �̺�Ʈ ȣ��
	virtual void OnTimerEvent(const _uint _iEventIndex) {}

	//���� ���� �� ȣ��
	virtual void OnLevelEnter() {}
	virtual void OnLevelExit() {}

	//��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
	virtual void OnEnable(void* _Arg = nullptr) {}

	//��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
	virtual void OnDisable() {}

	//��ü�� �����Ǳ� ���� ȣ��˴ϴ�. Free���� ���� ������ ȣ��˴ϴ�.
	//Free�� ����Ʈ �����Ͱ� ������ ���Ŀ� ȣ��˴ϴ�.
	virtual void OnDestroy() {}

	//�̺�Ʈ �޼����Դϴ�.
	virtual void OnEventMessage(_uint iArg) {}
	virtual void OnEventMessage(void* pArg) {}

private:
	virtual void OnEngineEventMessage(const ENGINE_EVENT_TYPE In_eEngineEvent) {};

protected:
	weak_ptr<CBase> m_this;

private:
	_bool			m_bEnable = true;

protected:
	void Free();

protected:
	template<typename T>
	static weak_ptr<T> Weak_Cast(weak_ptr<CBase> Instance)
	{
		return dynamic_pointer_cast<T>(Instance.lock());
	}

	template<typename T>
	static shared_ptr<T> Shared_Cast(shared_ptr<CBase> Instance)
	{
		return dynamic_pointer_cast<T>(Instance);
	}

	template<typename T>
	static weak_ptr<T> Weak_StaticCast(weak_ptr<CBase> Instance)
	{
#ifdef _DEBUG
		return dynamic_pointer_cast<T>(Instance.lock());
#else // _DEBUG
		return static_pointer_cast<T>(Instance.lock());
#endif // _DEBUG
	}

	template<typename T>
	static shared_ptr<T> Shared_StaticCast(shared_ptr<CBase> Instance)
	{
		return static_pointer_cast<T>(Instance);
	}


	template<typename T>
	static weak_ptr<T> Cast(weak_ptr<CBase> Instance)
	{
		return dynamic_pointer_cast<T>(Instance.lock());
	}

	template<typename T>
	static shared_ptr<T> Cast(shared_ptr<CBase> Instance)
	{
		return dynamic_pointer_cast<T>(Instance);
	}

	
};

END

