/*

   ThreadPool implementation based on Sean Parent's "Better Code: Concurrency" talk

*/

#include "jobQueue.h"
#include <atomic>
#include <thread>
#include <vector>

class ThreadPool
{
   ThreadPool();
   ~ThreadPool();

   void runThread           (unsigned numberThread);

   const unsigned            m_threadsCount { std::thread::hardware_concurrency() };
   std::vector<std::thread>  m_threads;
   std::vector<JobQueue>     m_jobQueues    { m_threadsCount };
   std::atomic<unsigned>     m_jobIndex     { 0 };

public:

   static ThreadPool&  getInstance();

   ThreadPool               (const ThreadPool& threadPool) = delete;
   ThreadPool&  operator =  (const ThreadPool& threadPool) = delete;

   ThreadPool               (ThreadPool&& threadPool)      = delete;
   ThreadPool&  operator =  (ThreadPool&& threadPool)      = delete;

   template <typename F>
   void async_(F&& job)
   {
      auto currentJobIndex = m_jobIndex ++;

      // Attempt to push a job in a job queue
      for (unsigned i = 0; i != m_threadsCount; ++ i)
      {
         if (m_jobQueues[(currentJobIndex + i) % m_threadsCount].attempt_push(std::forward<F>(job)))
         {
            return;
         }
      }

      m_jobQueues[currentJobIndex % m_threadsCount].push(std::forward<F>(job));
   }

};

