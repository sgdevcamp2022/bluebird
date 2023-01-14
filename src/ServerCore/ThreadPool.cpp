#include "pch.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(int num_threads_) : num_threads_(num_threads_), stop(false) {
	workers.reserve(num_threads_);
	for (int i = 0; i < num_threads_; i++) {
		workers.emplace_back([this]() { this->WorkerThread(); });
	}
}

ThreadPool::~ThreadPool() {
	while (!tasks.empty())
		tasks.pop();
	stop = true;
	condition.notify_all();
	for (int i = 0; i < num_threads_; i++)
		workers[i].join();
}

void ThreadPool::WorkerThread()
{
	while (true) {
		std::unique_lock<std::mutex> lk(this->m);
		this->condition.wait(lk, [this]() {return  this->stop || !this->tasks.empty(); });
		if (this->stop && this->tasks.empty())
			return;

		function<void(void)> task = std::move(tasks.front());
		tasks.pop();
		lk.unlock();
		task();
	}
}

bool ThreadPool::enqueue(function<void()> task)
{
	if (stop) {
		throw std::runtime_error("ThreadPool »ç¿ë ÁßÁöµÊ");
	}

	{
		std::lock_guard<std::mutex> lock(m);
		tasks.push([task]() { task(); });
	}
	condition.notify_one();

	return true;
}

void ThreadPool::Join()
{
	for (thread& t : workers)
	{
		if (t.joinable())
			t.join();
	}
	workers.clear();
}
