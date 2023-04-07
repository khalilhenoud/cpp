/**
 * @file packaged_task.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <future>
#include <thread>
#include <functional>
#include <cmath>


REFERENCES("https://en.cppreference.com/w/cpp/thread/packaged_task")

namespace {
// unique function to avoid disambiguating the std::pow overload set.
int32_t f(int32_t x, int32_t y)
{ 
  return std::pow(x, y);
}
}

TEST(
  packaged_task,
R"--(
The class template std::packaged_task wraps any Callable target (function,
lambda expression, bind expression, or another function object) so that it can
be invoked asynchronously. Its return value or exception thrown is stored in a
shared state which can be accessed through std::future objects.
Just like std::function, std::packaged_task is a polymorphic, allocator-aware
container: the stored callable target may be allocated on heap or with a
provided allocator.
)--",
  SECTION(
    "packaged_task with lambda",
    IN(PROTECT(std::packaged_task<int32_t(int32_t, int32_t)> task([](int32_t a, int32_t b) { return (int32_t)std::pow(a, b); });))
    IN(std::future<int32_t> future = task.get_future();)
    IN(task(2, 9);)
    IN(print_safe("\ttask value: %i\n", future.get());)
  )
  SECTION(
    "packaged_task with bind",
    IN(PROTECT(std::packaged_task<int32_t()> task(std::bind(f, 2, 10));))
    IN(std::future<int32_t> future = task.get_future();)
    IN(task();)
    IN(print_safe("\ttask value: %i\n", future.get());)
  )
  SECTION(
    "task with thread",
    IN(PROTECT(std::packaged_task<int32_t(int32_t, int32_t)> task(f);))
    IN(std::future<int32_t> future = task.get_future();)
    IN(std::thread t(std::move(task), 2, 11);)
    IN(print_safe("\ttask value: %i\n", future.get());)
    IN(t.join();)
  )
)