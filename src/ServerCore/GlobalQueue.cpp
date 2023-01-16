#include "pch.h"
#include "GlobalQueue.h"

GlobalQueue::GlobalQueue()
{
}

GlobalQueue::~GlobalQueue()
{
}

void GlobalQueue::Push(JobQueueRef jobQueue)
{
	_jobQueue.Push(jobQueue);
}

JobQueueRef GlobalQueue::Pop()
{
	return _jobQueue.Pop();
}
