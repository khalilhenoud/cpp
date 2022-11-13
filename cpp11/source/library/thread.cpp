/**
 * @file thread.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#stdthread\n"
  "https://en.cppreference.com/w/cpp/thread/thread\n"
  "https://en.cppreference.com/w/cpp/thread/get_id\n"
  "https://en.cppreference.com/w/cpp/thread/yield\n"
  "https://en.cppreference.com/w/cpp/thread/sleep_until\n"
  "https://en.cppreference.com/w/cpp/thread/sleep_for\n"
  "https://stackoverflow.com/questions/22803600/when-should-i-use-stdthreaddetach")

namespace {
std::mutex g_display_mutex;

void thread_proc(const char* name, int32_t placement)
{
  {
    std::lock_guard<std::mutex> _(g_display_mutex);
    std::cout << "\tthread name: " << name << ", placement: " << placement << std::endl;
    std::cout << "\tthread id: " << std::this_thread::get_id() << std::endl;
  }

  // this is implemenation dependent.
  std::this_thread::yield();
  std::this_thread::sleep_for(std::chrono::seconds(1));

  {
    std::lock_guard<std::mutex> _(g_display_mutex);
    std::cout << "\tthread name: " << name << ", stage 2" << std::endl;
  }

  std::this_thread::sleep_until(std::chrono::steady_clock::now() + std::chrono::seconds(2));

  {
    std::lock_guard<std::mutex> _(g_display_mutex);
    std::cout << "\tthread name: " << name << ", final print" << std::endl;
  }
}
}

TEST(
  thread,
  "The std::thread library provides a standard way to control threads, such as\n" 
  "spawning and killing them. In the example below, multiple threads are spawned\n" 
  "to do different calculations and then the program waits for all of them to\n" 
  "finish.",
  SECTION(
    "thread example and this_thread functionality",
    std::cout << GIVEN[0] << std::endl;
    IN(std::vector<std::thread> thread_vector;)
    IN(int32_t placement = 0;)
    IN(PROTECT(thread_vector.emplace_back(thread_proc, "john", ++placement);))
    IN(PROTECT(thread_vector.emplace_back(thread_proc, "peter", ++placement);))
    IN(PROTECT(thread_vector.emplace_back(thread_proc, "alen", ++placement);))
    IN(PROTECT(thread_vector.emplace_back(thread_proc, "micheal", ++placement);))
    IN(PROTECT(thread_vector.emplace_back(thread_proc, "nioh", ++placement);))
    IN(for (auto& thread : thread_vector) thread.join();)
  )
)