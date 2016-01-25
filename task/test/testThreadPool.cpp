#include "test.h"

#ifdef TEST_THREAD_POOL

#include "task.h"
#include <iostream>

int sum(int a, int b)
{
   return a + b;
}

void main()
{
   Future<int> future       = async([] { return sum(50, 30); });
   Future<int> continuation = future.then([](const int futureResult) { return sum(futureResult, 20); });
   
   std::cout << future.get() << std::endl;
   std::cout << continuation.get() << std::endl;
}

#endif
