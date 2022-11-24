/**
 * @file condition_variable.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <string>


REFERENCES(
  "https://en.cppreference.com/w/cpp/thread/condition_variable\n"
  "https://en.cppreference.com/w/cpp/thread/condition_variable_any\n"
  "https://en.cppreference.com/w/cpp/thread/cv_status\n"
  "https://stackoverflow.com/questions/3513045/conditional-variable-vs-semaphore\n"
  "https://stackoverflow.com/questions/16350473/why-do-i-need-stdcondition-variable\n"
  "https://stackoverflow.com/questions/5716437/condition-variable\n"
  "https://stackoverflow.com/questions/3710017/how-to-write-your-own-condition-variable-using-atomic-primitives\n"
  "https://en.cppreference.com/w/cpp/thread/condition_variable/notify_one")

namespace {
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
  // wait until we are signaled to start processing.
  std::unique_lock<std::mutex> lk(m);
  cv.wait(lk, [](){ return ready; });

  // wait atomically reacquires the lock and wakes the worker thread.
  std::cout << "Worker thread is processing data\n";
  data += " after processing";

  // its time to notify the main thread that the work is done.
  processed = true;
  std::cout << "Worker thread signals data processing completed\n";
  
  // Manual unlocking is done before notifying, to avoid waking up the waiting
  // thread only to block again (see notify_one for details).
  lk.unlock();
  cv.notify_one();
}

void runner()
{
  std::thread worker(worker_thread);

  data = "Example data";
  // send data to the worker thread to be processed
  {
    std::lock_guard<std::mutex> lk(m);
    ready = true;
    std::cout << "signal that data is ready to be processed" << std::endl;
  }
  cv.notify_one();

  // wait for the worker thread to indicate that the work has been processed
  {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [](){ return processed; });
  }
  std::cout << "work has been processed, data = " << data << std::endl;

  worker.join(); 
}
}

namespace {
namespace non_std {
enum class cv_status {
  no_timeout,
  timeout  
};
}
}

TEST(
  condition_variable,
  "The condition_variable class is a synchronization primitive used with a\n" 
  "std::mutex to block one or more threads until another thread both modifies a\n" 
  "shared variable (the condition) and notifies the condition_variable.\n"
  "The thread that intends to modify the shared variable must:\n"
  " 1 - Acquire a std::mutex (typically via std::lock_guard)\n"
  " 2 - Modify the shared variable while the lock is owned\n"
  " 3 - Call notify_one or notify_all on the std::condition_variable (can be\n" 
  "     done after releasing the lock)\n"
  "Even if the shared variable is atomic, it must be modified while owning the\n" 
  "mutex to correctly publish the modification to the waiting thread.\n"
  "Any thread that intends to wait on a std::condition_variable must:\n"
  " 1 - Acquire a std::unique_lock<std::mutex> on the mutex used to protect the\n" 
  "     shared variable\n"
  " 2 - Do one of the following:\n"
  "      1 - Check the condition, in case it was already updated and notified\n"
  "      2 - Call wait, wait_for, or wait_until on the std::condition_variable\n" 
  "          (atomically releases the mutex and suspends thread execution until\n" 
  "          the condition variable is notified, a timeout expires, or a\n" 
  "          spurious wakeup occurs, then atomically acquires the mutex before\n" 
  "          returning)\n"
  "      3 - Check the condition and resume waiting if not satisfied\n"
  "     or:\n"
  "      1 - Use the predicated overload of wait, wait_for, and wait_until,\n" 
  "          which performs the same three steps\n"
  "std::condition_variable works only with std::unique_lock<std::mutex>, which\n" 
  "allows for maximal efficiency on some platforms. std::condition_variable_any\n" 
  "provides a condition variable that works with any BasicLockable object, such\n" 
  "as std::shared_lock(cpp14).\n"
  "Condition variables permit concurrent invocation of the wait, wait_for,\n" 
  "wait_until, notify_one and notify_all member functions.\n"
  "The class std::condition_variable is a StandardLayoutType. It is not\n" 
  "CopyConstructible, MoveConstructible, CopyAssignable, or MoveAssignable.",
  SECTION(
    "condition_variable is used in combination with a std::mutex to facilitate\n" 
    "inter-thread communication.",
    std::cout << GIVEN[0] << std::endl;
    IN(runner();)
  )
)

TEST(
  condition_variable_any,
  "The condition_variable_any class is a generalization of\n" 
  "std::condition_variable. Whereas std::condition_variable works only on\n" 
  "std::unique_lock<std::mutex>, condition_variable_any can operate on any lock\n" 
  "that meets the BasicLockable requirements.\n"
  "The class std::condition_variable_any is a StandardLayoutType. It is not\n" 
  "CopyConstructible, MoveConstructible, CopyAssignable, or MoveAssignable.\n"
  "If the lock is std::unique_lock<std::mutex>, std::condition_variable may\n" 
  "provide better performance.",
  RESERVED_SECTION
)

TEST(
  cv_status,
  "The scoped enumeration std::cv_status describes whether a timed wait returned\n" 
  "because of timeout or not.\n" 
  "std::cv_status is used by the wait_for and wait_until member functions of\n" 
  "std::condition_variable and std::condition_variable_any.",
  SECTION(
    "definition",
    std::cout << GIVEN[1] << std::endl;
  )
)