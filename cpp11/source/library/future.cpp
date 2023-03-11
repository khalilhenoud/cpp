/**
 * @file future.cpp
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


REFERENCES("https://en.cppreference.com/w/cpp/thread/future")

namespace {
void throw_exception(std::promise<int32_t> promise) 
{
  try {
    throw std::runtime_error("hello I am an exception!");
  } catch(...) {
    try {
      // store the exception in the promise.
      promise.set_exception(std::current_exception());
    } catch(...) {} // set_exception may throw too.
  }
}
}

TEST(
  future,
R"--(
The class template std::future provides a mechanism to access the result of
asynchronous operations:
  - An asynchronous operation (created via std::async, std::packaged_task, or
    std::promise) can provide a std::future object to the creator of that
    asynchronous operation.
  - The creator of the asynchronous operation can then use a variety of methods
    to query, wait for, or extract a value from the std::future. These methods
    may block if the asynchronous operation has not yet provided a value.
  - When the asynchronous operation is ready to send a result to the creator, it
    can do so by modifying shared state (e.g. std::promise::set_value) that is
    linked to the creator's std::future.
Note that std::future references shared state that is not shared with any other
asynchronous return objects (as opposed to std::shared_future).
)--",
  SECTION(
    "futures from packaged_task",
    IN(std::packaged_task<int32_t()> task([]{ return 7; });)
    IN(std::future<int32_t> f1 = task.get_future();)
    IN(std::thread t(std::move(task));)
    IN(print_safe("\tf1: %i\n", f1.get());)
    IN(t.join();)
  )
  SECTION(
    "future from an async",
    IN(std::future<int32_t> f2 = std::async(std::launch::async, []{ return 8; });)
    IN(print_safe("\tf2: %i\n", f2.get());)
  )
  SECTION(
    "future from a promise",
    IN(std::promise<int32_t> promise;)
    IN(std::future<int32_t> f3 = promise.get_future();)
    DESC_IN(
    "set the value at the thread exit",
    std::thread([&promise]{ promise.set_value_at_thread_exit(9); }).detach();)
    IN(print_safe("\tf3: %i\n", f3.get());)
  )
  SECTION(
    "example with exceptions",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(std::promise<int32_t> promise;)
    IN(std::future<int32_t> future = promise.get_future();)
    IN(std::thread t(throw_exception, std::move(promise));)
    IN(PROTECT(
      try { 
        print_safe("%i\n", future.get()); 
      } catch(const std::exception& e) {
        print_safe("\texception from the thread: %s\n", e.what());
      }
    ))
    IN(t.join();)
  )
)