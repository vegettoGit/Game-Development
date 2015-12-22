#include "threadpool.h"
#include <thread>

ThreadPool::ThreadPool()
   : m_threadsCount(std::thread::hardware_concurrency())
{
}

ThreadPool::~ThreadPool()
{
}

ThreadPool& ThreadPool::getInstance()
{
   static ThreadPool threadPoolInstance;
   return threadPoolInstance;
}


