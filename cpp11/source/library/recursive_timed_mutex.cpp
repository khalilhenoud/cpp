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

#include <iostream>
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
  std::cout << "\t" << stream.str() << std::endl;
}
}

TEST(
  recursive_timed_mutex,
  "The recursive_timed_mutex class is a synchronization primitive that can be\n" 
  "used to protect shared data from being simultaneously accessed by multiple\n" 
  "threads.\n"
  "In a manner similar to std::recursive_mutex, recursive_timed_mutex provides\n" 
  "exclusive, recursive ownership semantics. In addition, recursive_timed_mutex\n" 
  "provides the ability to attempt to claim ownership of a recursive_timed_mutex\n" 
  "with a timeout via the try_lock_for and try_lock_until member functions.\n"
  "The recursive_timed_mutex class satisfies all requirements of TimedMutex and\n" 
  "StandardLayoutType.",
  SECTION(
    "example",
    std::cout << GIVEN[0] << std::endl;
    IN(std::vector<std::thread> threads;)
    IN(threads.emplace_back(job2, 0);)
    IN(threads.emplace_back(job2, 1);)
    IN(threads.emplace_back(job2, 2);)
    IN(threads.emplace_back(job2, 3);)
    IN(for (auto& thread : threads) thread.join();)
  )
)