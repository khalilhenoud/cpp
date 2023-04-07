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

#include <mutex>
#include <thread>
#include <vector>
#include <memory>


REFERENCES(
R"--(
https://en.cppreference.com/w/cpp/thread/call_once
https://stackoverflow.com/questions/55490024/stdcall-once-when-should-it-be-used#:~:text=std%3A%3Acall_once()%20can,if%20many%20threads%20execute%20it
https://stackoverflow.com/questions/22692783/is-stdcall-once-reentrant-and-thread-safe#:~:text=std%3A%3Acall_once%20is%20thread,it%20will%20cause%20a%20deadlock
https://stackoverflow.com/questions/2799023/what-exactly-is-a-reentrant-function
https://en.cppreference.com/w/cpp/thread/once_flag
)--"
)

NOTES(
R"--(
The class std::once_flag is a helper structure for std::call_once.
An object of type std::once_flag that is passed to multiple calls to
std::call_once allows those calls to coordinate with each other such that only
one of the calls will actually run to completion.
std::once_flag is neither copyable nor movable.
)--"
)

namespace {
// for each flag, exactly one function gets executed successfully once
std::unique_ptr<std::once_flag> flag1, flag2;

void simple_do_once()
{
  std::call_once(*flag1, [](){
    print_safe("simple example, called once\n");
  });
}

void may_throw_function(bool do_throw)
{
  if (do_throw) {
    print_safe("did throw: call_once will retry\n");
    throw std::exception();
  }
  print_safe("didn't throw: call once will not attempt again\n");
}

void do_once(bool do_throw)
{
  try {
    std::call_once(*flag2, may_throw_function, do_throw);
  }
  catch (...) {
  }
}
}

TEST(
  call_once,
R"--(
Executes the callable object f exactly once, even if called concurrently, from
several threads. In detail:
 - If, by the time call_once is called, flag indicates that f was already
   called, call_once returns right away (such a call to call_once is known as
   passive).
 - Otherwise, call_once invokes std::forward<Callable>(f) with the arguments
   std::forward<Args>(args)... (as if by std::invoke). Unlike the std::thread
   constructor or std::async, the arguments are not moved or copied because they
   don't need to be transferred to another thread of execution. (such a call to
   call_once is known as active).
    - If that invocation throws an exception, it is propagated to the caller of
      call_once, and the flag is not flipped so that another call will be
      attempted (such a call to call_once is known as exceptional).
    - If that invocation returns normally (such a call to call_once is known as
      returning), the flag is flipped, and all other calls to call_once with the
      same flag are guaranteed to be passive.
)--",
  SECTION(
    "call_once is closely related to double-checked locking programming pattern",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(flag1 = std::make_unique<std::once_flag>();))
    IN(PROTECT(flag2 = std::make_unique<std::once_flag>();))
    IN(std::vector<std::thread> threads_vector;)
    IN(threads_vector.emplace_back(simple_do_once);)
    IN(threads_vector.emplace_back(simple_do_once);)
    IN(threads_vector.emplace_back(simple_do_once);)
    IN(threads_vector.emplace_back(simple_do_once);)
    IN(for (auto& thread : threads_vector) thread.join();)
    IN(threads_vector.clear();)
    print_safe("\n");
    IN(threads_vector.emplace_back(do_once, true);)
    IN(threads_vector.emplace_back(do_once, true);)
    IN(threads_vector.emplace_back(do_once, false);)
    IN(threads_vector.emplace_back(do_once, true);)
    IN(for (auto& thread : threads_vector) thread.join();)
  )
)