/**
 * @file recursive_timed_mutex.cpp
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
#include <sstream>
#include <chrono>

using namespace std::chrono_literals;


REFERENCES("https://en.cppreference.com/w/cpp/thread/recursive_timed_mutex")

namespace {
std::recursive_timed_mutex mutex;
std::mutex g_print_mutex;

void job1(std::ostringstream& stream)
{
  for (int32_t i = 0; i < 3; ++i) {
    if (mutex.try_lock_for(100ms)) {
      stream << "job1::success ";
      std::this_thread::sleep_for(100ms);
      mutex.unlock();
    } else {
      stream << "job1::failed ";
    }
    std::this_thread::sleep_for(100ms);
  }
}

void job2(int32_t i)
{
  std::ostringstream stream;

  for (int32_t i = 0; i < 3; ++i) {
    if (mutex.try_lock_for(100ms)) {
      stream << "success ";
      std::this_thread::sleep_for(100ms);
      mutex.unlock();
    } else {
      stream << "failed ";
      job1(stream);
    }
    std::this_thread::sleep_for(100ms);
  }

  std::lock_guard<std::mutex> _(g_print_mutex);
  print_safe("\t%s\n", stream.str().c_str());
}
}

TEST(
  recursive_timed_mutex,
R"--(
The recursive_timed_mutex class is a synchronization primitive that can be used
to protect shared data from being simultaneously accessed by multiple threads.
In a manner similar to std::recursive_mutex, recursive_timed_mutex provides
exclusive, recursive ownership semantics. In addition, recursive_timed_mutex
provides the ability to attempt to claim ownership of a recursive_timed_mutex
with a timeout via the try_lock_for and try_lock_until member functions.
The recursive_timed_mutex class satisfies all requirements of TimedMutex and
StandardLayoutType.
)--",
  SECTION(
    "example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(std::vector<std::thread> threads;)
    IN(threads.emplace_back(job2, 0);)
    IN(threads.emplace_back(job2, 1);)
    IN(threads.emplace_back(job2, 2);)
    IN(threads.emplace_back(job2, 3);)
    IN(for (auto& thread : threads) thread.join();)
  )
)