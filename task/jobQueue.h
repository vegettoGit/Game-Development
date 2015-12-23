/*

   JobQueue implementation based on Sean Parent's "Better Code: Concurrency" talk
   Used by our ThreadPool class

*/

class JobQueue
{

   JobQueue               (const JobQueue& jobQueue) = delete;
   JobQueue&  operator =  (const JobQueue& jobQueue) = delete;

   JobQueue               (JobQueue&& jobQueue)      = delete;
   JobQueue&  operator =  (JobQueue&& jobQueue)      = delete;

public:

   JobQueue();
   ~JobQueue();
};
