/**
 * @file recursive_mutex.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <mutex>
#include <thread>


REFERENCES("https://en.cppreference.com/w/cpp/thread/recursive_mutex")

namespace {
class X {
  std::recursive_mutex mutex;
  std::string shared;
public:
void fun1()
{
  std::lock_guard<std::recursive_mutex> _(mutex);
  shared = "fun1";
  std::cout << "in fun1, shared variable is now " << shared << std::endl;
}
void fun2()
{
  std::lock_guard<std::recursive_mutex> _(mutex);
  shared = "fun2";
  std::cout << "in fun2, shared variable is now " << shared << std::endl;
  fun1();   // recursive mutex is necessary here.
  std::cout << "back in fun2, shared variable is " << shared << std::endl;
}
};
}

TEST(
  recursive_mutex,
  "The recursive_mutex class is a synchronization primitive that can be used to\n" 
  "protect shared data from being simultaneously accessed by multiple threads.\n"
  "recursive_mutex offers exclusive, recursive ownership semantics:\n"
  " - A calling thread owns a recursive_mutex for a period of time that starts\n" 
  "   when it successfully calls either lock or try_lock. During this period,\n" 
  "   the thread may make additional calls to lock or try_lock. The period of\n" 
  "   ownership ends when the thread makes a matching number of calls to unlock.\n"
  " - When a thread owns a recursive_mutex, all other threads will block (for\n" 
  "   calls to lock) or receive a false return value (for try_lock) if they\n" 
  "   attempt to claim ownership of the recursive_mutex.\n"
  " - The maximum number of times that a recursive_mutex may be locked is\n" 
  "   unspecified, but after that number is reached, calls to lock will throw\n" 
  "   std::system_error and calls to try_lock will return false.\n"
  "The behavior of a program is undefined if a recursive_mutex is destroyed\n" 
  "while still owned by some thread. The recursive_mutex class satisfies all\n" 
  "requirements of Mutex and StandardLayoutType.",
  SECTION(
    "one use case for recursive_mutex is protecting shared state in a class\n" 
    "whose member functions may call each other",
    std::cout << GIVEN[0] << std::endl;
    IN(X x;)
    IN(std::thread t1(&X::fun1, &x);)
    IN(std::thread t2(&X::fun2, &x);)
    IN(t1.join();)
    IN(t2.join();)
  )
)