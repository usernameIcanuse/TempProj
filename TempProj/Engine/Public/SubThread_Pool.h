#pragma once
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CSubThread_Pool :
    public CBase
{
    GAMECLASS_H(CSubThread_Pool);

public:
	static shared_ptr<CSubThread_Pool> Create(const _uint In_iSize);

private:
    void Initialize(const _uint In_iSize);
	void WorkerThread(_int iIndex);
public:
	_bool Check_JobDone();
	void Wait_JobDone(const _char* In_szConsoleText = nullptr);
	void Stop_All() { stop_all = true; }

private:
	// �� Worker �������� ����.
	size_t m_iNumThreads;
	// Worker �����带 �����ϴ� ����.
	vector<thread> m_Worker_Threads;
	// ���ϵ��� �����ϴ� job ť.
	queue<function<void()>> m_Jobs;
	// ���� job ť�� ���� cv �� m.
	condition_variable m_CV;
	mutex m_JobMutex;
	vector<_bool> m_WorkerJopdones;
	// ��� ������ ����
	bool stop_all;




private:
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
			std::lock_guard<std::mutex> lock(m_JobMutex);
			m_Jobs.push([job]() { (*job)(); });
		}
		m_CV.notify_one();

		return job_result_future;
	}
};

END