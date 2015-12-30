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
      // Attempt to grab a job from a job queue, then do the job
      std::function<void()> job;

      for (unsigned i = 0; i != m_threadsCount * 32; ++i) 
      {
         if (m_jobQueues[(numberThread + i) % m_threadsCount].attempt_pop(job))
         {
            break;
         }
      }

      if (!job && !m_jobQueues[numberThread].pop(job))
      {
         break;
      }

      job();
   }
}


