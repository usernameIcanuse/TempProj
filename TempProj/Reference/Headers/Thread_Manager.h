#pragma once
#include "Base.h"
#include "GameObject_Thread.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CThread_Manager final : public CBase
{
	DECLARE_SINGLETON(CThread_Manager)


private:
	struct GAMEOBJECT_THREAD
	{
		future<void> Future;
		shared_ptr<CGameObject_Thread> pInstance;
	};

public:
	_uint Get_NumThread() const { return num_threads_; }

public:
	void Initialize(const _uint In_iNumLayer);
	void Bind_ThreadObject(const THREAD_TYPE In_eThread_Type, weak_ptr<CGameObject> pGameObject);
	void Bind_GameObjectWorks(const _flag In_ThreadTypeFlag);

	_bool Check_JobDone();
	void Wait_JobDone(const _char* In_szConsoleText = nullptr);

private:

	void Clear_EngineThreads(const THREAD_TYPE In_eThread_Type);

	void WorkerThread(_int iIndex);
	
	


public:

	GAMEOBJECT_THREAD			m_GameObject_Threads[(_uint)THREAD_TYPE::TYPE_END];

private:
	// �� Worker �������� ����.
	size_t num_threads_;
	// Worker �����带 �����ϴ� ����.
	vector<thread> worker_threads_;
	// ���ϵ��� �����ϴ� job ť.
	queue<function<void()>> jobs_;
	// ���� job ť�� ���� cv �� m.
	condition_variable cv_job_q_;
	mutex m_job_q_;
	vector<_bool> worker_jopdones;


	// ��� ������ ����
	bool stop_all;


public:
	virtual void OnDestroy() override;
	void Free();
	

public:
	template <class F, class... Args>
	std::future<typename std::result_of<F(Args...)>::type> Enqueue_Job(
		F&& f, Args&&... args)
	{
		if (stop_all) {
			throw std::runtime_error("ThreadPool ��� ������");
		}

		using return_type = typename std::invoke_result_t<F, Args...>;
		auto job = std::make_shared<std::packaged_task<return_type()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...));
		
		std::future<return_type> job_result_future = job->get_future();
		{
			std::lock_guard<std::mutex> lock(m_job_q_);
			jobs_.push([job]() { (*job)(); });
		}
		cv_job_q_.notify_one();

		return job_result_future;
	}
};

END
