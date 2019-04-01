#pragma once

#include "def.hh"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <future>
#include <queue>

struct ThreadPool
{
	explicit ThreadPool(size_t poolSize = std::max(std::thread::hardware_concurrency() - 1u, 1u));
	~ThreadPool();
	
	template <typename F, typename... Args> auto enqueue(F func, Args ... args) //Note: thread pool can't accept moved args yet because of buggy type deduction in C++
	{
		auto invokeBinding = std::bind(std::forward<F>(func), std::forward<Args>(args)...);
		using invokePkg = std::packaged_task<std::invoke_result_t<decltype(invokeBinding)>()>;
		invokePkg pkg {std::move(invokeBinding)};
		auto future = pkg.get_future();
		this->queueMutex.lock();
		this->taskQueue.push(std::make_unique<Task<invokePkg>>(std::move(pkg)));
		this->queueMutex.unlock();
		this->queueCV.notify_one();
		return future;
	}

private:
	std::atomic_bool runSem {true};
	std::condition_variable queueCV;
	std::mutex queueMutex, cvMutex;
	std::vector<std::thread> threads;
	
	struct TaskBase
	{
		virtual void execute() = 0;
	};
	
	template <typename P> struct Task : public TaskBase
	{
		P pkg;
		explicit Task(P &&pkg) : pkg {std::forward<P &&>(pkg) }{}
		void execute() override {pkg();}
	};
	
	std::queue<UP<TaskBase>> taskQueue;
	
	void threadRun();
};

extern ThreadPool threadPool;
