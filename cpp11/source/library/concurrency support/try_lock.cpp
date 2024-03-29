/**
 * @file try_lock.cpp
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
#include <chrono>
#include <functional>
#include <vector>


REFERENCES("https://en.cppreference.com/w/cpp/thread/try_lock")

namespace {
int32_t foo_count = 0;
std::mutex foo_count_mutex;
int32_t bar_count = 0;
std::mutex bar_count_mutex;
int32_t overall_count = 0;
bool done;
std::mutex done_mutex;
std::mutex print_mutex;

void increment(int32_t& counter, std::mutex& m, const char* desc)
{
  using namespace std::chrono_literals;

  for (int32_t i = 0; i < 10; ++i) {
    {
      std::lock_guard<std::mutex> lk(m);
      ++counter;
      {
        std::lock_guard<std::mutex> lk_print(print_mutex);
        print_safe("%s: %i\n", desc, counter);
      }
    }
    std::this_thread::sleep_for(1s);
  }
}

void update_counters()
{
  using namespace std::chrono_literals;

  std::unique_lock<std::mutex> lk_done(done_mutex);
  while (!done) {
    lk_done.unlock();
    int32_t result = std::try_lock(foo_count_mutex, bar_count_mutex);
    if (result == -1) {
      // This will unlock the mutexes at the end of the scope
      std::lock_guard<std::mutex> lk_foo(foo_count_mutex, std::adopt_lock);
      std::lock_guard<std::mutex> lk_bar(bar_count_mutex, std::adopt_lock);
      overall_count += foo_count + bar_count;
      foo_count = 0;
      bar_count = 0;
      {
        std::lock_guard<std::mutex> lk_print(print_mutex);
        print_safe("overall: %i\n", overall_count);
      }
    }
    std::this_thread::sleep_for(2s);
    lk_done.lock();
  }
  lk_done.unlock();
}
}

TEST(
  try_lock,
R"--(
Tries to lock each of the given Lockable objects lock1, lock2, ..., lockn by
calling try_lock in order beginning with the first.
If a call to try_lock fails, no further call to try_lock is performed, unlock is
called for any locked objects and a 0-based index of the object that failed to
lock is returned.
If a call to try_lock results in an exception, unlock is called for any locked
objects before rethrowing.
)--",
  SECTION(
R"--(
The following example uses std::try_lock to periodically tally and reset
counters running in separate threads.
)--",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(std::thread increment_foo(increment, std::ref(foo_count), std::ref(foo_count_mutex), "foo");)
    IN(std::thread increment_bar(increment, std::ref(bar_count), std::ref(bar_count_mutex), "bar");)
    IN(std::thread update_overall(update_counters);)
    IN(increment_foo.join();)
    IN(increment_bar.join();)
    IN(done_mutex.lock();)
    IN(done = true;)
    IN(done_mutex.unlock();)
    IN(update_overall.join();)
    IN(print_safe("\tDone processing\n");)
    IN(print_safe("\tfoo: %i\n", foo_count);)
    IN(print_safe("\tbar: %i\n", bar_count);)
    IN(print_safe("\toverall: %i\n", overall_count);)
  )
)