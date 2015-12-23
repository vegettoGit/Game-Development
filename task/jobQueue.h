/*

   JobQueue implementation based on Sean Parent's "Better Code: Concurrency" talk
   Used by our ThreadPool class

*/

#include <deque>
#include <mutex>
#include <functional>

class JobQueue
{

   JobQueue               (const JobQueue& jobQueue) = delete;
   JobQueue&  operator =  (const JobQueue& jobQueue) = delete;

   JobQueue               (JobQueue&& jobQueue)      = delete;
   JobQueue&  operator =  (JobQueue&& jobQueue)      = delete;

   std::deque<std::function<void()>> m_jobs;
   std::mutex                        m_mutex;
   std::condition_variable           m_ready;

public:

   JobQueue();
   ~JobQueue();

   template<typename F>
   void push(F&& job) 
   {
      {
         std::unique_lock<std::mutex> lock{ m_mutex };
         m_jobs.emplace_back(std::forward<F>(job));
      }
      m_ready.notify_one();
   }
};
