/*

   JobQueue implementation based on Sean Parent's "Better Code: Concurrency" talk
   Used by our ThreadPool class

*/

#include <deque>
#include <mutex>
#include <functional>

class JobQueue
{
   std::deque<std::function<void()>> m_jobs;
   std::mutex                        m_mutex;
   std::condition_variable           m_ready;
   bool                              m_done { false };

public:

   JobQueue               (const JobQueue& jobQueue) = delete;
   JobQueue&  operator =  (const JobQueue& jobQueue) = delete;

   JobQueue               (JobQueue&& jobQueue)      = delete;
   JobQueue&  operator =  (JobQueue&& jobQueue)      = delete;

   JobQueue();
   ~JobQueue();
   
   void done();

   // Blocking. Attempts to pop a job and if there isn't any, then wait until we can get one.
   bool pop(std::function<void()>& job);

   // Non Blocking. If there aren't any jobs or the lock is locked, then just return.
   bool attempt_pop(std::function<void()>& job);

   // Blocking
   template<typename F>
   void push(F&& job) 
   {
      {
         std::unique_lock<std::mutex> lock{ m_mutex };
         m_jobs.emplace_back(std::forward<F>(job));
      }
      m_ready.notify_one();
   }

   // Non Blocking
   template<typename F>
   bool attempt_push(F&& job)
   {
      {
         std::unique_lock<std::mutex> lock{ m_mutex, std::try_to_lock };
         if (!lock)
         {
            return false;
         }
         m_jobs.emplace_back(std::forward<F>(job));
      }
      m_ready.notify_one();
      return true;
   }
};
