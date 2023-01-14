#pragma once

class SpinLock {
public:
	void lock() {
		bool expected = false;
		bool desired = true;

		while (_locked.compare_exchange_strong(expected, desired) == false)
		{
			expected = false;
		}
	}
	void unlock() {
		_locked.store(false);
	}

private:
	std::atomic<bool> _locked = false;
};