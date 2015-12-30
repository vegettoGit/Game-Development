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
};