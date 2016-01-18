/*

   Based on Sean Parent's "Better Code: Concurrency" talk

   Used by packaged tasks.

*/

#include "taskResultAndContinuations.h"


template <typename> class Task;
template <typename> class PackagedTask;
template <typename> class Future;

template <typename> struct ResultOf;

template <typename R, typename... Args>
struct ResultOf<R(Args...)>
{
   using type = R;
};

template <typename F> using ResultOfT = typename ResultOf<F>::type;

template <typename S, typename F>
auto Package(F&& job)->std::pair<PackagedTask<S>, Future<ResultOfT<S>>>;


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
   Future
*/
template <typename R>
class Future
{
   std::shared_ptr<TaskResultAndContinuations<R>> m_taskResultAndContinuations;

   template <typename S, typename F>
   friend auto Package(F&& job)->std::pair<PackagedTask<S>, Future<ResultOfT<S>>>;

   explicit Future(std::shared_ptr<TaskResultAndContinuations<R>> taskResultAndContinuations)
      : m_taskResultAndContinuations(std::move(taskResultAndContinuations))
   {
   }

public:

   Future() = default;

   template <typename F>
   auto then(F&& job)
   {
      auto pack = Package<ResultOfT<F(R)>()>([taskResultAndContinuations = m_taskResultAndContinuations, continuation = std::forward<F>(job)]()
      {
         return continuation(taskResultAndContinuations->m_result.back());
      });
      m_taskResultAndContinuations->then(std::move(pack.first));
      return pack.second;
   }

   const R& get() const
   {
      return m_taskResultAndContinuations->get();
   }
};


/*
   PackagedTask
*/
template<typename R, typename ...Args >
class PackagedTask<R(Args...)>
{
   std::weak_ptr<Task<R(Args...)>> m_task;

   template <typename S, typename F>
   friend auto Package(F&& job)->std::pair<PackagedTask<S>, Future<ResultOfT<S>>>;

   explicit PackagedTask(std::weak_ptr<Task<R(Args...)>> task) 
      : m_task(std::move(task)) 
   {
   }

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


/* 
    Package
*/
template <typename S, typename F>
auto Package(F&& job) -> std::pair<PackagedTask<S>, Future<ResultOfT<S>>>
{
   auto task = std::make_shared<Task<S>>(std::forward<F>(job));
   return make_pair(PackagedTask<S>(task), Future<ResultOfT<S>>(task));
}

