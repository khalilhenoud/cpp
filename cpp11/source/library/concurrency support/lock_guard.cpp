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
  print_safe("\tg_i: %i, in thread #%u\n", g_i, std::this_thread::get_id());
}
}

TEST(
  lock_guard,
R"--(
The class lock_guard is a mutex wrapper that provides a convenient RAII-style
mechanism for owning a mutex for the duration of a scoped block.
When a lock_guard object is created, it attempts to take ownership of the mutex
it is given. When control leaves the scope in which the lock_guard object was
created, the lock_guard is destructed and the mutex is released.
The lock_guard class is non-copyable.
)--",
  SECTION(
R"--(
cpp17 introduces std::scoped_lock offers a replacement for lock_guard that
provides the ability to lock multiple mutexes using a deadlock avoidance
algorithm.
)--",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(print_safe("\tg_i: %i, in main\n", g_i);)
    IN(std::thread t1(safe_increment);)
    IN(std::thread t2(safe_increment);)
    IN(t1.join();)
    IN(t2.join();)
    IN(print_safe("\tg_i: %i, in main\n", g_i);)
  )
)