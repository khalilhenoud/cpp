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
R"--(
The class template std::promise provides a facility to store a value or an
exception that is later acquired asynchronously via a std::future object created
by the std::promise object. Note that the std::promise object is meant to be
used only once.

Each promise is associated with a shared state, which contains some state
information and a result which may be not yet evaluated, evaluated to a value
(possibly void) or evaluated to an exception. A promise may do three things with
the shared state:
  - make ready: the promise stores the result or the exception in the shared
    state. Marks the state ready and unblocks any thread waiting on a future
    associated with the shared state.
  - release: the promise gives up its reference to the shared state. If this was
    the last such reference, the shared state is destroyed. Unless this was a
    shared state created by std::async which is not yet ready, this operation
    does not block.
  - abandon: the promise stores the exception of type std::future_error with
    error code std::future_errc::broken_promise, makes the shared state ready,
    and then releases it.

The promise is the "push" end of the promise-future communication channel:
the operation that stores a value in the shared state synchronizes-with (as
defined in std::memory_order) the successful return from any function that is
waiting on the shared state (such as std::future::get). Concurrent access to the
same shared state may conflict otherwise: for example multiple callers of
std::shared_future::get must either all be read-only or provide external
synchronization.
)--",
  SECTION(
    "This example shows how promise<int> can be used as signals between threads.",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(std::vector<int32_t> numbers = {1, 2, 3, 4, 5, 6};))
    IN(std::promise<int32_t> accumulate_promise;)
    IN(std::future<int32_t> accumulate_future = accumulate_promise.get_future();)
    IN(std::thread work_thread(
            accumulate, 
            std::begin(numbers), std::end(numbers), 
            std::move(accumulate_promise));)
    DESC_IN(
    "future.get() calls future.wait() internally.", 
    print_safe("\tresult = %i\n", accumulate_future.get());)
    IN(work_thread.join();)
  )
  SECTION(
    "Demonstrate using promise<void> to signal state between threads.",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(std::promise<void> barrier;)
    IN(std::future<void> barrier_future = barrier.get_future();)
    IN(std::thread work_thread(do_work, std::move(barrier));)
    IN(barrier_future.wait();)
    IN(work_thread.join();)
  )
)