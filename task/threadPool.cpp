#include "threadpool.h"

ThreadPool::ThreadPool()
{
   for (unsigned i = 0; i != m_threadsCount; ++i)
   {
      m_threads.emplace_back([&, i] { runThread(i); });
   }
}

ThreadPool::~ThreadPool()
{
   for (auto& jobQueue : m_jobQueues)
   {
      jobQueue.done();
   }

   for (auto& t : m_threads)
   {
      t.join();
   }
}

ThreadPool& ThreadPool::getInstance()
{
   static ThreadPool threadPoolInstance;
   return threadPoolInstance;
}

void ThreadPool::runThread(unsigned numberThread)
{
   while (true) 
   {
      // TODO: Attempt to grab a job from the job queue
   }
}


