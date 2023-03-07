/**
 * @file async.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <future>
#include <mutex>
#include <string>
#include <vector>
#include <numeric>


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#stdasync
https://en.cppreference.com/w/cpp/thread/async
)--"
)

namespace {
int32_t foo()
{
  return 1000;
}
}

namespace {
template <typename RandomIt>
int32_t parallel_sum(RandomIt beg, RandomIt end)
{
  auto len = end - beg;
  if (len < 1000)
    return std::accumulate(beg, end, 0);

  RandomIt mid = beg + len/2;
  auto handle = std::async(
    std::launch::async, 
    parallel_sum<RandomIt>, mid, end);
  int32_t sum = parallel_sum(beg, mid);
  return sum + handle.get();
}
}

namespace {
std::mutex g_print_mutex;

struct X {
void foo(int32_t i, const std::string& str)
{
  std::lock_guard<std::mutex> _(g_print_mutex);
  print_safe("foo: %s %i\n", str.c_str(), i);
}

void bar(const std::string& str)
{
  std::lock_guard<std::mutex> _(g_print_mutex);
  print_safe("bar: %s\n", str.c_str());
}

int32_t operator()(int32_t i) 
{
  {
    std::lock_guard<std::mutex> _(g_print_mutex);
    print_safe("functor: %i\n", i); 
  }
  return i + 10;
}
};
}

TEST(
  std_async,
R"--(
std::async runs the given function either asynchronously or lazily-evaluated,
then returns a std::future which holds the result of that function call.
The first parameter is the policy which can be:
 - std::launch::async | std::launch::deferred It is up to the implementation
   whether to perform asynchronous execution or lazy evaluation.
 - std::launch::async Run the callable object on a new thread.
 - std::launch::deferred Perform lazy evaluation on the current thread.
)--",
  SECTION(
    "basic example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(std::future<int32_t> handle = std::async(std::launch::async, foo);))
    IN(handle.wait();)
    IN(print_safe("\t%i\n", handle.get());)
  )
  SECTION(
    "parallel sum example",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(PROTECT(std::vector<int32_t> v(10000, 1);))
    IN(print_safe("the sum is: %i\n", parallel_sum(std::begin(v), std::end(v)));)
  )
  SECTION(
    "policy examples",
    print_safe("%s\n", GIVEN[2].c_str());
    IN(X x;)
    DESC_IN(
      "default policy call, implementation dependant",
      auto a1 = std::async(&X::foo, &x, 42, "hello");)
    DESC_IN(
      "lazy evaluation, only when get() or wait() is called is it evaluated",
      auto a2 = std::async(std::launch::deferred, &X::bar, &x, "world!");)
    DESC_IN(
      "async policy, usually evaluated on a separate thread",
      auto a3 = std::async(std::launch::async, &X::operator(), x, 43);)
    IN(a2.wait());
    IN(print_safe("\t%i\n", a3.get());)
    print_safe(R"--(// if a1 is not done at this point, destructor of a1 prints "hello 42" here)--");
  )
)