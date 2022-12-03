/**
 * @file unique_lock.cpp
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
#include <functional>


REFERENCES(
  "https://en.cppreference.com/w/cpp/thread/unique_lock\n"
  "https://stackoverflow.com/questions/34078208/passing-object-by-reference-to-stdthread-in-c11")


namespace {
struct Box {
  explicit Box(int32_t num)
  : num_things{num}
  {}

  int32_t num_things = 0;
  std::mutex m;
};

void transfer(Box& from, Box& to, int32_t num)
{
  // defer locking the mutex for now
  std::unique_lock<std::mutex> lock1{from.m, std::defer_lock};
  std::unique_lock<std::mutex> lock2{to.m, std::defer_lock};

  // use std::lock to acquire the locks (std::lock uses a deadlock safe
  // algorithm)
  std::lock(lock1, lock2);

  from.num_things -= num;
  to.num_things += num;

  // 'from.m' and 'to.m' mutexes unlocked in 'unique_lock' dtors
}
}

TEST(
  unique_lock,
  "The class unique_lock is a general-purpose mutex ownership wrapper allowing\n" 
  "deferred locking, time-constrained attempts at locking, recursive locking,\n" 
  "transfer of lock ownership, and use with condition variables.\n"
  "The class unique_lock is movable, but not copyable.\n"
  "The class unique_lock meets the BasicLockable requirements. If Mutex meets\n" 
  "the Lockable requirements, unique_lock also meets the Lockable requirements\n" 
  "(ex.: can be used in std::lock); if Mutex meets the TimedLockable\n" 
  "requirements, unique_lock also meets the TimedLockable requirements.",
  SECTION(
    "example",
    std::cout << GIVEN[0] << std::endl;
    IN(Box acc1{100};)
    IN(Box acc2{50};)
    std::cout << std::endl;
    IN(PROTECT(std::thread t1{transfer, std::ref(acc1), std::ref(acc2), 10};))
    IN(PROTECT(std::thread t2{transfer, std::ref(acc2), std::ref(acc1), 5};))
    IN(t1.join();)
    IN(t2.join();)
    std::cout << std::endl;
    IN(std::cout << "\tacc1: " << acc1.num_things << std::endl;)
    IN(std::cout << "\tacc2: " << acc2.num_things << std::endl;)
  )
)