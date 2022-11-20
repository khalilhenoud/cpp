/**
 * @file lock.cpp
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
#include <vector>
#include <string>
#include <functional>
#include <chrono>


REFERENCES("https://en.cppreference.com/w/cpp/thread/lock")

namespace {
using namespace std::chrono_literals;

struct Employee {
  Employee(std::string id)
  : id{id}
  {}

  std::string id;
  std::vector<std::string> lunch_partners;
  std::mutex m;
  
  std::string output() const
  {
    std::string ret = "Employee " + id + " has lunch partners: ";
    for (const auto& partner : lunch_partners)
        ret += partner + " ";
    return ret;
  }
};

void send_mail(Employee &, Employee &)
{
  std::this_thread::sleep_for(1s);
}

void assign_lunch_partner(Employee &e1, Employee &e2)
{
  static std::mutex io_mutex;
  {
    std::lock_guard<std::mutex> lk(io_mutex);
    std::cout << "\t" << e1.id << " and " << e2.id << " are waiting for locks" << std::endl;
  }

  // use std::lock to acquire the two locks without worrying about other calls
  // to assign_lunch_partner deadlocking us.
  {
    std::lock(e1.m, e2.m);
    // the mutexes are already locked, lock_guard is required to unlock the
    // mutexes at the end of the scope. adopt_lock is used to indicate not to
    // try and lock the mutexes again.
    std::lock_guard<std::mutex> lk1(e1.m, std::adopt_lock);
    std::lock_guard<std::mutex> lk2(e2.m, std::adopt_lock);
    {
      std::lock_guard<std::mutex> lk_io(io_mutex);
      std::cout << "\t" << e1.id << " and " << e2.id << " got locks" << std::endl;
    }
    e1.lunch_partners.push_back(e2.id);
    e2.lunch_partners.push_back(e1.id);
  }
  send_mail(e1, e2);
  send_mail(e2, e1);
}
}

TEST(
  std_lock,
  "Locks the given Lockable objects lock1, lock2, ..., lockn using a deadlock\n" 
  "avoidance algorithm to avoid deadlock.\n"
  "The objects are locked by an unspecified series of calls to lock, try_lock,\n" 
  "and unlock. If a call to lock or unlock results in an exception, unlock is\n" 
  "called for any locked objects before rethrowing.",
  SECTION(
    "The following example uses std::lock to lock pairs of mutexes without\n" 
    "deadlock.",
    std::cout << GIVEN[0] << std::endl;
    IN(Employee alice("alice");)
    IN(Employee bob("bob");)
    IN(Employee christina("christina");)
    IN(Employee dave("dave");)
    DESC_IN(
      "assign in parallel threads because mailing users about lunch assignments takes a long time",
      std::vector<std::thread> threads;)
    IN(PROTECT(threads.emplace_back(std::thread(assign_lunch_partner, std::ref(alice), std::ref(bob)));))
    IN(PROTECT(threads.emplace_back(std::thread(assign_lunch_partner, std::ref(christina), std::ref(bob)));))
    IN(PROTECT(threads.emplace_back(std::thread(assign_lunch_partner, std::ref(christina), std::ref(alice)));))
    IN(PROTECT(threads.emplace_back(std::thread(assign_lunch_partner, std::ref(dave), std::ref(bob)));))
    IN(for (auto &thread : threads) thread.join();)
    IN(std::cout << "\t" << alice.output() << std::endl;)
    IN(std::cout << "\t" << bob.output() << std::endl;)
    IN(std::cout << "\t" << christina.output() << std::endl;)
    IN(std::cout << "\t" << dave.output() << std::endl;)
  )
)
