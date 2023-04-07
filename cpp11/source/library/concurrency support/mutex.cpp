/**
 * @file mutex.cpp
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

#include <thread>
#include <mutex>
#include <map>
#include <string>


REFERENCES("https://en.cppreference.com/w/cpp/thread/mutex")

namespace {
std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;

void save_page(const std::string &url)
{
  // simulate a long page fetch
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::string result = "fake content";

  std::lock_guard<std::mutex> _(g_pages_mutex);
  g_pages[url] = result;
}
}

TEST(
  std_mutex,
R"--(
The mutex class is a synchronization primitive that can be used to protect
shared data from being simultaneously accessed by multiple threads.
mutex offers exclusive, non-recursive ownership semantics:
  - A calling thread owns a mutex from the time that it successfully calls 
    either lock or try_lock until it calls unlock.
  - When a thread owns a mutex, all other threads will block (for calls to lock)
    or receive a false return value (for try_lock) if they attempt to claim
    ownership of the mutex.
  - A calling thread must not own the mutex prior to calling lock or try_lock.
  - std::mutex is neither copyable nor movable.
The behavior of a program is undefined if a mutex is destroyed while still owned
by any threads, or a thread terminates while owning a mutex. The mutex class
satisfies all requirements of Mutex and StandardLayoutType.
)--",
  SECTION(
    "mutex example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(std::thread t1(save_page, "http://foo");)
    IN(std::thread t2(save_page, "http://bar");)
    IN(t1.join();)
    IN(t2.join();)
    print_safe("\n");
    DESC_IN(
    "safe to access g_pages, threads are joined.",
    for (const auto& pair : g_pages)
      print_safe("\t%s => %s\n", pair.first.c_str(), pair.second.c_str()); 
    )
  )
)