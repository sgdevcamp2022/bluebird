#pragma once

class ThreadPool {
public:
	ThreadPool(int num_threads_);
	~ThreadPool();

	bool enqueue(function<void()>);
	void Join();
private:
	void WorkerThread();

private:
	vector<std::thread> workers;
	queue<std::function<void()>> tasks;

	size_t num_threads_;
	condition_variable condition;
	mutex m;
	bool stop;
};