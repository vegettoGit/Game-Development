#include "vector3.h"

// Intentionally created to test move constructor
Vector3 PassAndReturn(Vector3 test)
{
   return test;
}

void main()
{
   // Constructor
   Vector3 test1(1.0f, 2.0f, 3.0f);
   
   // Copy constructor
   Vector3 test2(test1);

   // Constructor
   // We would then expect move constructor (rvalue), but might not happen (copy elision) depending on compiler settings
   Vector3 test3(Vector3(4.0f, 5.0f, 6.0f));

   // Constructor of temporary (rvalue)
   // Move constructor of temporary directly into test4 (return value optimization happens)
   // Destructor of temporary
   Vector3 test4(PassAndReturn(Vector3(7.0f, 8.0f, 9.0f)));

   // test4 destructor
   // test3 destructor
   // test2 destructor
   // test1 destructor

   return;
}