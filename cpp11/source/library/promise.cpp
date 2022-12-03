/**
 * @file promise.cpp
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

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <numeric>
#include <vector>


REFERENCES("https://en.cppreference.com/w/cpp/thread/promise")

namespace {
void accumulate(
  std::vector<int32_t>::iterator first,
  std::vector<int32_t>::iterator last,
  std::promise<int32_t> accumulate_promise)
{
  // set the value in the shared state and make it ready (notify future).
  accumulate_promise.set_value(std::accumulate(first, last, 0));
}
}

namespace {
void do_work(std::promise<void> barrier)
{
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1s);
  barrier.set_value();
}
}

TEST(
  promise,
  "The class template std::promise provides a facility to store a value or an\n" 
  "exception that is later acquired asynchronously via a std::future object\n" 
  "created by the std::promise object. Note that the std::promise object is\n" 
  "meant to be used only once.\n"
  "Each promise is associated with a shared state, which contains some state\n" 
  "information and a result which may be not yet evaluated, evaluated to a value\n" 
  "(possibly void) or evaluated to an exception. A promise may do three things\n" 
  "with the shared state:\n"
  " - make ready: the promise stores the result or the exception in the shared\n" 
  "   state. Marks the state ready and unblocks any thread waiting on a future\n" 
  "   associated with the shared state.\n"
  " - release: the promise gives up its reference to the shared state. If this\n" 
  "   was the last such reference, the shared state is destroyed. Unless this\n" 
  "   was a shared state created by std::async which is not yet ready, this\n" 
  "   operation does not block.\n"
  " - abandon: the promise stores the exception of type std::future_error with\n" 
  "   error code std::future_errc::broken_promise, makes the shared state ready,\n" 
  "   and then releases it.\n"
  "The promise is the \"push\" end of the promise-future communication channel:\n" 
  "the operation that stores a value in the shared state synchronizes-with (as\n" 
  "defined in std::memory_order) the successful return from any function that is\n" 
  "waiting on the shared state (such as std::future::get). Concurrent access to\n" 
  "the same shared state may conflict otherwise: for example multiple callers of\n" 
  "std::shared_future::get must either all be read-only or provide external\n" 
  "synchronization.",
  SECTION(
    "This example shows how promise<int> can be used as signals between threads.",
    std::cout << GIVEN[0] << std::endl;
    IN(PROTECT(std::vector<int32_t> numbers = {1, 2, 3, 4, 5, 6};))
    IN(std::promise<int32_t> accumulate_promise;)
    IN(std::future<int32_t> accumulate_future = accumulate_promise.get_future();)
    IN(std::thread work_thread(
            accumulate, 
            std::begin(numbers), std::end(numbers), 
            std::move(accumulate_promise));)
    DESC_IN(
    "future.get() calls future.wait() internally.", 
    std::cout << "\tresult = " << accumulate_future.get() << std::endl;)
    IN(work_thread.join();)
  )
  SECTION(
    "Demonstrate using promise<void> to signal state between threads.",
    std::cout << GIVEN[1] << std::endl;
    IN(std::promise<void> barrier;)
    IN(std::future<void> barrier_future = barrier.get_future();)
    IN(std::thread work_thread(do_work, std::move(barrier));)
    IN(barrier_future.wait();)
    IN(work_thread.join();)
  )
)