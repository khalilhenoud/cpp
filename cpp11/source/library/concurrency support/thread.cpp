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

#include <vector>
#include <thread>
#include <mutex>
#include <chrono>


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#stdthread
https://en.cppreference.com/w/cpp/thread/thread
https://en.cppreference.com/w/cpp/thread/get_id
https://en.cppreference.com/w/cpp/thread/yield
https://en.cppreference.com/w/cpp/thread/sleep_until
https://en.cppreference.com/w/cpp/thread/sleep_for
https://stackoverflow.com/questions/22803600/when-should-i-use-stdthreaddetach
)--"
)

namespace {
std::mutex g_display_mutex;

void thread_proc(const char* name, int32_t placement)
{
  {
    std::lock_guard<std::mutex> _(g_display_mutex);
    print_safe("\tthread name: %s, placement: %i\n", name, placement);
    print_safe("\tthread id: %u\n", std::this_thread::get_id());
  }

  // this is implemenation dependent.
  std::this_thread::yield();
  std::this_thread::sleep_for(std::chrono::seconds(1));

  {
    std::lock_guard<std::mutex> _(g_display_mutex);
    print_safe("\tthread name: %s, stage2\n", name);
  }

  std::this_thread::sleep_until(
    std::chrono::steady_clock::now() + 
    std::chrono::seconds(2));

  {
    std::lock_guard<std::mutex> _(g_display_mutex);
    print_safe("\tthread name: %s, final print\n", name);
  }
}
}

TEST(
  thread,
R"--(
The std::thread library provides a standard way to control threads, such as
spawning and killing them. In the example below, multiple threads are spawned to
do different calculations and then the program waits for all of them to finish.

Note:
-----
  - The arguments to the thread function are moved or copied by value. If a
    reference argument needs to be passed to the thread function, it has to be
    wrapped (e.g., with std::ref or std::cref).
  - Any return value from the function is ignored. If the function throws an
    exception, std::terminate is called. In order to pass return values or
    exceptions back to the calling thread, std::promise or std::async may be
    used.
)--",
  SECTION(
    "thread example and this_thread functionality",
    print_safe("%s\n", GIVEN[0].c_str());
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