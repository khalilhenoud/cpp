/**
 * @file lock_guard.cpp
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

#include <iostream>
#include <mutex>
#include <thread>


REFERENCES("https://en.cppreference.com/w/cpp/thread/lock_guard")

namespace {
int32_t g_i = 0;
std::mutex g_i_mutex;

void safe_increment()
{
  const std::lock_guard<std::mutex> lock(g_i_mutex);
  ++g_i;
  std::cout << "\tg_i: " << g_i << ", in thread #" << std::this_thread::get_id() << std::endl;
}
}

TEST(
  lock_guard,
  "The class lock_guard is a mutex wrapper that provides a convenient RAII-style\n" 
  "mechanism for owning a mutex for the duration of a scoped block.\n"
  "When a lock_guard object is created, it attempts to take ownership of the\n" 
  "mutex it is given. When control leaves the scope in which the lock_guard\n" 
  "object was created, the lock_guard is destructed and the mutex is released.\n"
  "The lock_guard class is non-copyable.",
  SECTION(
    "cpp17 introduces std::scoped_lock offers a replacement for lock_guard that\n" 
    "provides the ability to lock multiple mutexes using a deadlock avoidance\n" 
    "algorithm.",
    std::cout << GIVEN[0] << std::endl;
    IN(std::cout << "\tg_i: " << g_i << ", in main" << std::endl;)
    IN(std::thread t1(safe_increment);)
    IN(std::thread t2(safe_increment);)
    IN(t1.join();)
    IN(t2.join();)
    IN(std::cout << "\tg_i: " << g_i << ", in main" << std::endl;)
  )
)