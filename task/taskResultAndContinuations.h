/*

   Based on Sean Parent's "Better Code: Concurrency" talk

   Contains: - The result of a task.
             - The task pending continuations.

   Behaviour: Once the result of the task arrives, all the pending tasks are pushed to the thread pool.

   Used by futures and packaged tasks.

*/

template <typename R>
class TaskResultAndContinuations
{
   std::vector<R>                     m_result;
   std::mutex                         m_mutex;
   std::condition_variable            m_ready;
   std::vector<std::function<void()>> m_then;

   TaskResultAndContinuations               (const TaskResultAndContinuations& taskResultAndContinuations) = delete;
   TaskResultAndContinuations&  operator =  (const TaskResultAndContinuations& taskResultAndContinuations) = delete;

   TaskResultAndContinuations               (TaskResultAndContinuations&& taskResultAndContinuations) = delete;
   TaskResultAndContinuations&  operator =  (TaskResultAndContinuations&& taskResultAndContinuations) = delete;

public:

   TaskResultAndContinuations() = default;

   virtual ~TaskResultAndContinuations() 
   {
   }

   template <typename F>
   void then(F&& continuation)
   {
      bool resolved{ false };
      {
         std::unique_lock<std::mutex> lock{ m_mutex };

         // If the task is not completed yet, push a continuation
         if (m_result.empty())
         {
            m_then.push_back(std::forward<F>(continuation));
         }
         else
         {
            resolved = true;
         }
      }
      
      // If the task is completed, then we can push a job directly to the thread pool
      if (resolved)
      {
         ThreadPool::getInstance().async_(std::move(continuation));
      }
   }

   const R& get() 
   {
      std::unique_lock<std::mutex> lock{ m_mutex };
      while (m_result.empty())
      {
         m_ready.wait(lock);
      }
      return m_result.back();
   }
};