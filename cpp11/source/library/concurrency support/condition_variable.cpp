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

#include <thread>
#include <condition_variable>
#include <mutex>
#include <string>


REFERENCES(
R"--(
https://en.cppreference.com/w/cpp/thread/condition_variable
https://en.cppreference.com/w/cpp/thread/condition_variable_any
https://en.cppreference.com/w/cpp/thread/cv_status
https://stackoverflow.com/questions/3513045/conditional-variable-vs-semaphore
https://stackoverflow.com/questions/16350473/why-do-i-need-stdcondition-variable
https://stackoverflow.com/questions/5716437/condition-variable
https://stackoverflow.com/questions/3710017/how-to-write-your-own-condition-variable-using-atomic-primitives
https://en.cppreference.com/w/cpp/thread/condition_variable/notify_one
)--"
)

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
  print_safe("Worker thread is processing data\n");
  data += " after processing";

  // its time to notify the main thread that the work is done.
  processed = true;
  print_safe("Worker thread signals data processing completed\n");
  
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
    print_safe("signal that data is ready to be processed\n");
  }
  cv.notify_one();

  // wait for the worker thread to indicate that the work has been processed
  {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [](){ return processed; });
  }
  print_safe("work has been processed, data = %s\n", data.c_str());

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
R"--(
The condition_variable class is a synchronization primitive used with a
std::mutex to block one or more threads until another thread both modifies a
shared variable (the condition) and notifies the condition_variable.
The thread that intends to modify the shared variable must:
  1 - Acquire a std::mutex (typically via std::lock_guard)
  2 - Modify the shared variable while the lock is owned
  3 - Call notify_one or notify_all on the std::condition_variable (can be done
      after releasing the lock)
Even if the shared variable is atomic, it must be modified while owning the
mutex to correctly publish the modification to the waiting thread.
Any thread that intends to wait on a std::condition_variable must:
  1 - Acquire a std::unique_lock<std::mutex> on the mutex used to protect the
      shared variable
  2 - Do one of the following:
    1 - Check the condition, in case it was already updated and notified
    2 - Call wait, wait_for, or wait_until on the std::condition_variable
        (atomically releases the mutex and suspends thread execution until the
        condition variable is notified, a timeout expires, or a spurious wakeup 
        occurs, then atomically acquires the mutex before returning)
    3 - Check the condition and resume waiting if not satisfied
     or:
      1 - Use the predicated overload of wait, wait_for, and wait_until, which
          performs the same three steps
std::condition_variable works only with std::unique_lock<std::mutex>, which
allows for maximal efficiency on some platforms. std::condition_variable_any
provides a condition variable that works with any BasicLockable object, such as
std::shared_lock(cpp14).
Condition variables permit concurrent invocation of the wait, wait_for,
wait_until, notify_one and notify_all member functions.
The class std::condition_variable is a StandardLayoutType. It is not
CopyConstructible, MoveConstructible, CopyAssignable, or MoveAssignable.
)--",
  SECTION(
R"--(
condition_variable is used in combination with a std::mutex to facilitate 
inter-thread communication.
)--",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(runner();)
  )
)

TEST(
  condition_variable_any,
R"--(
The condition_variable_any class is a generalization of std::condition_variable.
Whereas std::condition_variable works only on std::unique_lock<std::mutex>, 
condition_variable_any can operate on any lock that meets the BasicLockable
requirements.
The class std::condition_variable_any is a StandardLayoutType. It is not
CopyConstructible, MoveConstructible, CopyAssignable, or MoveAssignable.
If the lock is std::unique_lock<std::mutex>, std::condition_variable may provide
better performance.
)--",
  RESERVED_SECTION
)

TEST(
  cv_status,
R"--(
The scoped enumeration std::cv_status describes whether a timed wait returned
because of timeout or not.
std::cv_status is used by the wait_for and wait_until member functions of
std::condition_variable and std::condition_variable_any.
)--",
  SECTION(
    "definition",
    print_safe("%s\n", GIVEN[1].c_str());
  )
)