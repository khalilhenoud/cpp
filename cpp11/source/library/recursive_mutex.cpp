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
  print_safe("in fun1, shared variable is now %s\n", shared.c_str());
}
void fun2()
{
  std::lock_guard<std::recursive_mutex> _(mutex);
  shared = "fun2";
  print_safe("in fun2, shared variable is now %s\n", shared.c_str());
  fun1();   // recursive mutex is necessary here.
  print_safe("back in fun2, shared variable is %s\n", shared.c_str());
}
};
}

TEST(
  recursive_mutex,
R"--(
The recursive_mutex class is a synchronization primitive that can be used to
protect shared data from being simultaneously accessed by multiple threads.
recursive_mutex offers exclusive, recursive ownership semantics:
  - A calling thread owns a recursive_mutex for a period of time that starts
    when it successfully calls either lock or try_lock. During this period, the
    thread may make additional calls to lock or try_lock. The period of
    ownership ends when the thread makes a matching number of calls to unlock.
  - When a thread owns a recursive_mutex, all other threads will block (for
    calls to lock) or receive a false return value (for try_lock) if they
    attempt to claim ownership of the recursive_mutex.
  - The maximum number of times that a recursive_mutex may be locked is
    unspecified, but after that number is reached, calls to lock will throw
    std::system_error and calls to try_lock will return false.
The behavior of a program is undefined if a recursive_mutex is destroyed while
still owned by some thread. The recursive_mutex class satisfies all requirements
of Mutex and StandardLayoutType.
)--",
  SECTION(
R"--(
one use case for recursive_mutex is protecting shared state in a class whose
member functions may call each other
)--",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(X x;)
    IN(std::thread t1(&X::fun1, &x);)
    IN(std::thread t2(&X::fun2, &x);)
    IN(t1.join();)
    IN(t2.join();)
  )
)