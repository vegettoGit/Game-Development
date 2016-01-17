/*

   Based on Sean Parent's "Better Code: Concurrency" talk

   Used by packaged tasks.

*/

#include "taskResultAndContinuations.h"

template <typename> class Task;
template <typename> class PackagedTask;

template <typename R, typename... Args>
class Task<R(Args...)> : TaskResultAndContinuations<R> 
{
   std::function<R(Args...)> m_job;

public:

   template<typename F>
   Task(F&& job) 
      : m_job(std::forward<F>(job))
   {
   }

   template <typename... A>
   void operator()(A&&... args) 
   {
      this->set(m_job(std::forward<A>(args)...));
      m_job = nullptr;
   }
};

template<typename R, typename ...Args >
class PackagedTask<R(Args...)>
{
   std::weak_ptr<Task<R(Args...)>> m_task;

public:

   PackagedTask() = default;

   template <typename... A>
   void operator()(A&&... args) const 
   {
      auto task = m_task.lock();
      if (task)
      {
         (*task)(std::forward<A>(args)...);
      }
   }
};

