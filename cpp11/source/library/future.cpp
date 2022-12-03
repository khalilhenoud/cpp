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

#include <iostream>
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
  "The class template std::future provides a mechanism to access the result of\n" 
  "asynchronous operations:\n"
  " - An asynchronous operation (created via std::async, std::packaged_task, or\n" 
  "   std::promise) can provide a std::future object to the creator of that\n" 
  "   asynchronous operation.\n"
  " - The creator of the asynchronous operation can then use a variety of\n" 
  "   methods to query, wait for, or extract a value from the std::future. These\n" 
  "   methods may block if the asynchronous operation has not yet provided a\n" 
  "   value.\n"
  " - When the asynchronous operation is ready to send a result to the creator,\n" 
  "   it can do so by modifying shared state (e.g. std::promise::set_value) that\n" 
  "   is linked to the creator's std::future.\n"
  "Note that std::future references shared state that is not shared with any\n" 
  "other asynchronous return objects (as opposed to std::shared_future).",
  SECTION(
    "futures from packaged_task",
    IN(std::packaged_task<int32_t()> task([]{ return 7; });)
    IN(std::future<int32_t> f1 = task.get_future();)
    IN(std::thread t(std::move(task));)
    IN(std::cout << "\tf1: " << f1.get() << std::endl;)
    IN(t.join();)
  )
  SECTION(
    "future from an async",
    IN(std::future<int32_t> f2 = std::async(std::launch::async, []{ return 8; });)
    IN(std::cout << "\tf2: " << f2.get() << std::endl;)
  )
  SECTION(
    "future from a promise",
    IN(std::promise<int32_t> promise;)
    IN(std::future<int32_t> f3 = promise.get_future();)
    DESC_IN(
    "set the value at the thread exit",
    std::thread([&promise]{ promise.set_value_at_thread_exit(9); }).detach();)
    IN(std::cout << "\tf3: " << f3.get() << std::endl;)
  )
  SECTION(
    "example with exceptions",
    std::cout << GIVEN[0] << std::endl;
    IN(std::promise<int32_t> promise;)
    IN(std::future<int32_t> future = promise.get_future();)
    IN(std::thread t(throw_exception, std::move(promise));)
    IN(PROTECT(
      try { 
        std::cout << future.get(); 
      } catch(const std::exception& e) {
        std::cout << "\texception from the thread: " << e.what() << std::endl;
      }
    ))
    IN(t.join();)
  )
)