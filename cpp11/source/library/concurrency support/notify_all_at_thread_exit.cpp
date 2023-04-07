/**
 * @file notify_all_at_thread_exit.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <thread>
#include <condition_variable>
#include <mutex>
#include <string>
#include <cassert>


REFERENCES(
R"--(
https://en.cppreference.com/w/cpp/thread/notify_all_at_thread_exit
https://stackoverflow.com/questions/22794382/are-c11-thread-local-variables-automatically-static
)--"
)

namespace {
std::mutex m;
std::condition_variable cv;

bool ready = false;
std::string result;

void thread_func()
{
  // Although this would seem not to make sense, this is identical to:
  //      static thread_local std::string thread_local_data = "42";
  // see ref [2].
  thread_local std::string thread_local_data = "42";
  std::unique_lock<std::mutex> lk(m);

  // assign a value using the thread_local data.
  result = thread_local_data;
  ready = true;

  std::notify_all_at_thread_exit(cv, std::move(lk));
}     // 1- destroy thread local variables.
      // 2- unlock mutex, now in internal storage.
      // 3- notify cv (cv.notify_all()).

void runner()
{
  std::thread t(thread_func);
  t.detach();

  // simulate work.
  std::this_thread::sleep_for(std::chrono::seconds(2));

  // wait for the detached thread.
  std::unique_lock<std::mutex> lk(m);
  cv.wait(lk, []{return ready;});

  // IMPORTANT: do not use lk going forward, see the associated text.
  assert(result == "42");
  print_safe("result = %s\n", result.c_str());
}
}

TEST(
  notify_all_at_thread_exit,
R"--(
notify_all_at_thread_exit provides a mechanism to notify other threads that a
given thread has completely finished, including destroying all thread_local
objects. It operates as follows:
 - Ownership of the previously acquired lock lk is transferred to internal
   storage.
 - The execution environment is modified such that when the current thread
   exits, the condition variable cond is notified as if by:
      lk.unlock();
      cond.notify_all();
The implied lk.unlock is sequenced after (as defined in std::memory_order) the
destruction of all objects with thread local storage duration associated
with the current thread.

An equivalent effect may be achieved with the facilities provided by
std::promise or std::packaged_task.

Notes:
------
Calling this function if lock.mutex() is not locked by the current thread is
undefined behavior.
Calling this function if lock.mutex() is not the same mutex as the one used by
all other threads that are currently waiting on the same condition variable is 
undefined behavior.
The supplied lock lk is held until the thread exits. Once this function has been
called, no more threads may acquire the same lock in order to wait on cond. If 
some thread is waiting on this condition variable, it should not attempt to
release and reacquire the lock when it wakes up spuriously.
In typical use cases, this function is the last thing called by a detached
thread.
)--",
  SECTION(
R"--(
This partial code fragment illustrates how notify_all_at_thread_exit can be used
to avoid accessing data that depends on thread locals while those thread locals
are in the process of being destructed:
)--",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(runner();)
  )
)
