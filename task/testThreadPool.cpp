#include "test.h"

#ifdef TEST_THREAD_POOL

#include "threadPool.h"

void main()
{
   ThreadPool& threadPool = ThreadPool::getInstance();

   // At this point we should be able to know how many threads we can support

   return;
}

#endif
