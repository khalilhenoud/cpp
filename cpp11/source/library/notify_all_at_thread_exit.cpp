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

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <string>
#include <cassert>


REFERENCES(
  "[1] https://en.cppreference.com/w/cpp/thread/notify_all_at_thread_exit\n"
  "[2] https://stackoverflow.com/questions/22794382/are-c11-thread-local-variables-automatically-static")

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
  std::cout << "result = " << result << std::endl;
}
}

TEST(
  notify_all_at_thread_exit,
  "notify_all_at_thread_exit provides a mechanism to notify other threads that a\n" 
  "given thread has completely finished, including destroying all thread_local\n" 
  "objects. It operates as follows:\n"
  " - Ownership of the previously acquired lock lk is transferred to internal\n" 
  "   storage.\n"
  " - The execution environment is modified such that when the current thread\n" 
  "   exits, the condition variable cond is notified as if by:\n"
  "             lk.unlock();\n"
  "             cond.notify_all();\n"
  "The implied lk.unlock is sequenced after (as defined in std::memory_order)\n" 
  "the destruction of all objects with thread local storage duration associated\n" 
  "with the current thread.\n"
  "An equivalent effect may be achieved with the facilities provided by\n" 
  "std::promise or std::packaged_task.\n"
  "notes:\n"
  "Calling this function if lock.mutex() is not locked by the current thread is\n" 
  "undefined behavior.\n"
  "Calling this function if lock.mutex() is not the same mutex as the one used\n" 
  "by all other threads that are currently waiting on the same condition\n" 
  "variable is undefined behavior.\n"
  "The supplied lock lk is held until the thread exits. Once this function has\n" 
  "been called, no more threads may acquire the same lock in order to wait on\n" 
  "cond. If some thread is waiting on this condition variable, it should not\n" 
  "attempt to release and reacquire the lock when it wakes up spuriously.\n"
  "In typical use cases, this function is the last thing called by a detached\n" 
  "thread.",
  SECTION(
    "This partial code fragment illustrates how notify_all_at_thread_exit can be\n" 
    "used to avoid accessing data that depends on thread locals while those\n" 
    "thread locals are in the process of being destructed:",
    std::cout << GIVEN[0] << std::endl;
    IN(runner();)
  )
)
