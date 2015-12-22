/*

   ThreadPool implementation based on Sean Parent's "Better Code: Concurrency" talk

*/

class ThreadPool
{
   ThreadPool();
   ~ThreadPool();

   ThreadPool               (const ThreadPool& threadPool) = delete;
   ThreadPool&  operator =  (const ThreadPool& threadPool) = delete;

   ThreadPool               (ThreadPool&& threadPool)      = delete;
   ThreadPool&  operator =  (ThreadPool&& threadPool)      = delete;

   const unsigned  m_threadsCount;

public:

   static ThreadPool&  getInstance();
};
