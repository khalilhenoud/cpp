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

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <sstream>


REFERENCES(
  "https://en.cppreference.com/w/cpp/thread/timed_mutex\n"
  "https://en.cppreference.com/w/cpp/thread/timed_mutex/try_lock_for")

namespace {
using namespace std::chrono_literals;

std::mutex cout_mutex;  // control access to std::cout
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
  std::cout << "\t[" << id << "]" << stream.str() << std::endl;
}
}

TEST(
  timed_mutex,
  "The timed_mutex class is a synchronization primitive that can be used to\n" 
  "protect shared data from being simultaneously accessed by multiple threads.\n"
  "In a manner similar to mutex, timed_mutex offers exclusive, non-recursive\n" 
  "ownership semantics. In addition, timed_mutex provides the ability to\n" 
  "attempt to claim ownership of a timed_mutex with a timeout via the member\n" 
  "functions try_lock_for() and try_lock_until().",
  SECTION(
    "example",
    std::cout << GIVEN[0] << std::endl;
    IN(std::vector<std::thread> threads;)
    IN(threads.emplace_back(job, 0);)
    IN(threads.emplace_back(job, 1);)
    IN(threads.emplace_back(job, 2);)
    IN(threads.emplace_back(job, 3);)
    IN(for (auto& thread : threads) thread.join();)
  )
)