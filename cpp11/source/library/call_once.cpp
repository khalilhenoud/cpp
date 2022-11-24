/**
 * @file call_once.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


REFERENCES(
  "https://en.cppreference.com/w/cpp/thread/call_once\n"
  "https://stackoverflow.com/questions/55490024/stdcall-once-when-should-it-be-used#:~:text=std%3A%3Acall_once()%20can,if%20many%20threads%20execute%20it.\n"
  "https://stackoverflow.com/questions/22692783/is-stdcall-once-reentrant-and-thread-safe#:~:text=std%3A%3Acall_once%20is%20thread,it%20will%20cause%20a%20deadlock.\n"
  "https://stackoverflow.com/questions/2799023/what-exactly-is-a-reentrant-function\n"
  "https://en.cppreference.com/w/cpp/thread/once_flag")

NOTES(
  "The class std::once_flag is a helper structure for std::call_once.\n"
  "An object of type std::once_flag that is passed to multiple calls to\n" 
  "std::call_once allows those calls to coordinate with each other such that\n" 
  "only one of the calls will actually run to completion.\n"
  "std::once_flag is neither copyable nor movable.")

namespace {
// for each flag, exactly one function gets executed successfully once
std::once_flag flag1, flag2;

void simple_do_once()
{
  std::call_once(flag1, [](){
    std::cout << "simple example, called once" << std::endl;
  });
}

void may_throw_function(bool do_throw)
{
  if (do_throw) {
    std::cout << "did throw: call_once will retry" << std::endl;
    throw std::exception();
  }
  std::cout << "didn't throw: call once will not attempt again" << std::endl;
}

void do_once(bool do_throw)
{
  try {
    std::call_once(flag2, may_throw_function, do_throw);
  }
  catch (...) {
  }
}
}

TEST(
  call_once,
  "Executes the callable object f exactly once, even if called concurrently,\n" 
  "from several threads. In detail:\n"
  " - If, by the time call_once is called, flag indicates that f was already\n" 
  "   called, call_once returns right away (such a call to call_once is known as\n" 
  "   passive).\n"
  " - Otherwise, call_once invokes std::forward<Callable>(f) with the arguments\n" 
  "   std::forward<Args>(args)... (as if by std::invoke). Unlike the std::thread\n" 
  "   constructor or std::async, the arguments are not moved or copied because\n" 
  "   they don't need to be transferred to another thread of execution. (such a\n" 
  "   call to call_once is known as active).\n"
  "     - If that invocation throws an exception, it is propagated to the caller\n" 
  "       of call_once, and the flag is not flipped so that another call will be\n" 
  "       attempted (such a call to call_once is known as exceptional).\n"
  "     - If that invocation returns normally (such a call to call_once is known\n" 
  "       as returning), the flag is flipped, and all other calls to call_once\n" 
  "       with the same flag are guaranteed to be passive.",
  SECTION(
    "call_once is closely related to double-checked locking programming pattern",
    std::cout << GIVEN[0] << std::endl;
    IN(std::vector<std::thread> threads_vector;)
    IN(threads_vector.emplace_back(simple_do_once);)
    IN(threads_vector.emplace_back(simple_do_once);)
    IN(threads_vector.emplace_back(simple_do_once);)
    IN(threads_vector.emplace_back(simple_do_once);)
    IN(for (auto& thread : threads_vector) thread.join();)
    IN(threads_vector.clear();)
    std::cout << std::endl;
    IN(threads_vector.emplace_back(do_once, true);)
    IN(threads_vector.emplace_back(do_once, true);)
    IN(threads_vector.emplace_back(do_once, false);)
    IN(threads_vector.emplace_back(do_once, true);)
    IN(for (auto& thread : threads_vector) thread.join();)
  )
)