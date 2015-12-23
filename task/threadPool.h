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

   ThreadPool               (const ThreadPool& threadPool) = delete;
   ThreadPool&  operator =  (const ThreadPool& threadPool) = delete;

   ThreadPool               (ThreadPool&& threadPool)      = delete;
   ThreadPool&  operator =  (ThreadPool&& threadPool)      = delete;

   void runThread           (unsigned numberThread);

   const unsigned            m_threadsCount { std::thread::hardware_concurrency() };
   std::vector<std::thread>  m_threads;
   std::vector<JobQueue>     m_jobQueues    { m_threadsCount };
   std::atomic<unsigned>     m_jobIndex     { 0 };

public:

   static ThreadPool&  getInstance();
};

