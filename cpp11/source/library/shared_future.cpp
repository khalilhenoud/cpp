/**
 * @file shared_future.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <future> 
#include <chrono>


REFERENCES("https://en.cppreference.com/w/cpp/thread/shared_future")

namespace {
std::chrono::duration<double, std::milli>
timing_test(
  const std::chrono::time_point<std::chrono::high_resolution_clock>& start,
  std::shared_future<void> ready_future,
  std::promise<void> tx_ready_promise)
{
  tx_ready_promise.set_value();   // notify the future.
  ready_future.wait();            // this is safe, as it was passed by value (copied).
  return std::chrono::high_resolution_clock::now() - start;
}

void runner()
{
  std::promise<void> ready_promise, t1_ready_promise, t2_ready_promise;
  std::shared_future<void> ready_future(ready_promise.get_future());

  std::chrono::time_point<std::chrono::high_resolution_clock> start;

  std::future<void> fut1 = t1_ready_promise.get_future();
  std::future<void> fut2 = t2_ready_promise.get_future();

  // futures of type std::future<std::chrono::duration<double, std::milli>>
  auto result1 = std::async(std::launch::async, timing_test, std::cref(start), ready_future, std::move(t1_ready_promise));
  auto result2 = std::async(std::launch::async, timing_test, std::cref(start), ready_future, std::move(t2_ready_promise));

  // wait for the t1, t2 promises signals us (with set_value).
  fut1.wait();
  fut2.wait();

  // the threads are ready adn blocked on ready_future.wait().
  // note: this is read only, though still not thread safe. I think a
  // conditional variable would have been preferable in this case.
  start = std::chrono::high_resolution_clock::now();

  // signals the threads to go.
  ready_promise.set_value();

  print_safe("\ttiming_test 2: %f ms after start\n", result2.get().count());
  print_safe("\ttiming_test 1: %f ms after start\n", result1.get().count());
}
}

TEST(
  shared_future,
R"--(
The class template std::shared_future provides a mechanism to access the result
of asynchronous operations, similar to std::future, except that multiple threads
are allowed to wait for the same shared state. 

Unlike std::future, which is only moveable (so only one instance can refer to 
any particular asynchronous result), std::shared_future is copyable and multiple
shared future objects may refer to the same shared state.

Access to the same shared state from multiple threads is safe if each thread
does it through its own copy of a shared_future object.
)--",
  SECTION(
R"--(
A shared_future may be used to signal multiple threads simultaneously, similar
to std::condition_variable::notify_all().
)--",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(runner();)
  )
)