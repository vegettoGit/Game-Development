/*

   Based on Sean Parent's "Better Code: Concurrency" talk

   Used by packaged tasks.

*/

#include "taskResultAndContinuations.h"

template <typename> class Task;
template <typename> class PackagedTask;


/*
   Task
*/
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


/* 
   Package 
*/
template <typename> struct ResultOf;

template <typename R, typename... Args>
struct ResultOf<R(Args...)> 
{ 
   using type = R; 
};

template <typename F> using ResultOfT = typename ResultOf<F>::type;

template <typename S, typename F>
auto Package(F&& f)->std::pair<PackagedTask<S>, Future<ResultOfT<S>>>;


/*
   PackagedTask
*/
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

