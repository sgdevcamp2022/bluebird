#include "pch.h"
#include "JobQueue.h"
#include "GlobalQueue.h"

void JobQueue::Push(JobRef job, bool pushOnly)
{
	const int32 prevCount = _jobCount.fetch_add(1);
	_jobs.Push(job);

	//첫번째 Job을 넣은 쓰레드가 실행까지 담당
	if (prevCount == 0)
	{
		// 이미 실행중인 JobQueue가 없으면 실행
		if (LCurrentJobQueue == nullptr && pushOnly == false)
		{
			Execute();
		}
		else
		{
			GGlobalQueue->Push(shared_from_this());
		}
	}
}

// 1) 일감이 너-무 물리면?
// 2) DoAsync 타고 타고 가서- 절대 끝나지 않는 상황
void JobQueue::Execute()
{
	LCurrentJobQueue = this;

	while (true)
	{
		Vector<JobRef> jobs;
		_jobs.PopAll(jobs);

		const int32 jobCount = static_cast<int32>(jobs.size());
		for (int32 i = 0; i < jobCount; i++)
			jobs[i]->Execute();

		//남은 일감이 0개라면 종료
		if (_jobCount.fetch_sub(jobCount) == jobCount)
		{
			LCurrentJobQueue = nullptr;
			return;
		}

		const uint64 now = ::GetTickCount64();
		if (now >= LEndTickCount)
		{
			LCurrentJobQueue = nullptr;
			GGlobalQueue->Push(shared_from_this());
			break;
		}
	}
}