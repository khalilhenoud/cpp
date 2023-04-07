/**
 * @file timed_mutex.cpp
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
#include <chrono>
#include <vector>
#include <sstream>


REFERENCES(
R"--(
https://en.cppreference.com/w/cpp/thread/timed_mutex
https://en.cppreference.com/w/cpp/thread/timed_mutex/try_lock_for
)--"
)

namespace {
using namespace std::chrono_literals;

std::mutex cout_mutex;  // control access to print
std::timed_mutex mutex;

void job(int32_t id)
{
  std::ostringstream stream;

  for (int32_t i = 0; i < 3; ++i) {
    if (mutex.try_lock_for(100ms)) {
      stream << "success ";
      std::this_thread::sleep_for(100ms);
      mutex.unlock();
    } else {
      stream << "failed ";
    }
    std::this_thread::sleep_for(100ms);
  }

  std::lock_guard<std::mutex> _(cout_mutex);
  print_safe("\t[%i] %s\n", id, stream.str().c_str());
}
}

TEST(
  timed_mutex,
R"--(
The timed_mutex class is a synchronization primitive that can be used to protect
shared data from being simultaneously accessed by multiple threads.
In a manner similar to mutex, timed_mutex offers exclusive, non-recursive
ownership semantics. In addition, timed_mutex provides the ability to attempt to
claim ownership of a timed_mutex with a timeout via the member functions
try_lock_for() and try_lock_until().
)--",
  SECTION(
    "example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(std::vector<std::thread> threads;)
    IN(threads.emplace_back(job, 0);)
    IN(threads.emplace_back(job, 1);)
    IN(threads.emplace_back(job, 2);)
    IN(threads.emplace_back(job, 3);)
    IN(for (auto& thread : threads) thread.join();)
  )
)