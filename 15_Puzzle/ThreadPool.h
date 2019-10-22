// Author: Yiang Lu
// Date created: 22/Oct/2019
#include <functional>
#include <thread>
#include <vector>

#pragma once
class ThreadPool
{
	typedef std::function<void()> Task;

public:
	explicit ThreadPool(unsigned int threadNumber)
	{
		run(threadNumber);
	}
	~ThreadPool()
	{
		end();
	}

private:
	void run(unsigned int threadNumber)
	{

	}

	void end() // exception
	{
		{

		}
	}
};

