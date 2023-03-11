/**
 * @file lock_tag.cpp
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


REFERENCES("https://en.cppreference.com/w/cpp/thread/lock_tag")

namespace {
struct bank_account {
  explicit bank_account(int32_t balance) 
  : balance{balance} 
  {}

  int32_t balance;
  std::mutex m;
};

void transfer(bank_account& from, bank_account& to, int32_t amount)
{
  // avoid moving to the same account, will deadlock the code.
  if (&from == &to)
    return;

  std::lock(from.m, to.m);
  // this will unlock the mutexes at the end of the scope.
  std::lock_guard<std::mutex> lk_from(from.m, std::adopt_lock);
  std::lock_guard<std::mutex> lk_to(to.m, std::adopt_lock);

  /*  // equivalent approach
  std::unique_lock<std::mutex> lk_from(from.m, std::defer_lock);
  std::unique_lock<std::mutex> lk_to(from.m, std::defer_lock);
  std::lock(from.m, to.m);
  */
  from.balance -= amount;
  to.balance += amount;
}
}

TEST(
  lock_tag,
R"--(
std::defer_lock, std::try_to_lock and std::adopt_lock are instances of empty
struct tag types std::defer_lock_t, std::try_to_lock_t and std::adopt_lock_t
respectively.
They are used to specify locking strategies for std::lock_guard,
std::unique_lock and std::shared_lock(cpp14).
)--",
  SECTION(
    "example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(bank_account my_account{100};)
    IN(bank_account your_account{50};)
    IN(PROTECT(std::thread t1{transfer, std::ref(my_account), std::ref(your_account), 10};))
    IN(PROTECT(std::thread t2{transfer, std::ref(your_account), std::ref(my_account), 5};))
    IN(t1.join();)
    IN(t2.join();)
    IN(print_safe("\tmy account balance = %i\n", my_account.balance);)
    IN(print_safe("\tyour account balance = %i\n", your_account.balance);)
  )
)