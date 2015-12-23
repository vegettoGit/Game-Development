#include "jobqueue.h"

JobQueue::JobQueue()
{
}

JobQueue::~JobQueue()
{
}

void JobQueue::done()
{
   {
      std::unique_lock<std::mutex> lock{ m_mutex };
      m_done = true;
   }
   m_ready.notify_all();
}

bool JobQueue::pop(std::function<void()>& job)
{
   std::unique_lock<std::mutex> lock{ m_mutex };
   
   while (m_jobs.empty() && !m_done)
   {
      m_ready.wait(lock);
   }

   if (m_jobs.empty())
   {
      return false;
   }

   job = std::move(m_jobs.front());
   m_jobs.pop_front();

   return true;
}



