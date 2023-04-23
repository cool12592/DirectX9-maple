#pragma once
#include <map>
#include <thread>
#include <functional>
#include "Functor.h"
class ThreadPool
{
public:
	ThreadPool() {}
	~ThreadPool()
	{
		for (auto& iter = threads_.begin(); iter != threads_.end(); ++iter)
			safeDelete((*iter).second);
	}

	bool insertThread(int priority,std::function<void()> func)
	{
		auto& iter = threads_.find(priority);
		if (threads_.end() != iter)
			return false;

		std::thread* newThread = new std::thread(func);
		threads_.emplace(priority, newThread);
		return true;
	}
	void joinThreads()
	{
		for (auto& tr : threads_)
			tr.second->join();
	}
	
private:
	std::map<int,std::thread*> threads_;
};

