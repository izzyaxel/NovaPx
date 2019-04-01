#include "threadPool.hh"

ThreadPool threadPool;

ThreadPool::ThreadPool(size_t poolSize)
{
	for(size_t i = 0; i < poolSize; i++) this->threads.emplace_back(&ThreadPool::threadRun, this);
}

ThreadPool::~ThreadPool()
{
	this->runSem.store(false);
	this->queueCV.notify_all();
	for(std::thread &th : this->threads) if(th.joinable()) th.join();
}

void ThreadPool::threadRun()
{
	while(this->runSem)
	{
		{
			std::unique_lock lock {this->cvMutex};
			this->queueCV.wait_for(lock, std::chrono::milliseconds(5000));
		}
		{
			std::unique_lock lock {this->queueMutex};
			if(this->taskQueue.empty()) continue;
			auto task = std::move(this->taskQueue.front());
			this->taskQueue.pop();
			lock.unlock();
			task->execute();
		}
	}
}
