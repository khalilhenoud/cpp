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

#include <iostream>
#include <future>
#include <mutex>
#include <string>
#include <vector>
#include <numeric>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#stdasync\n"
  "https://en.cppreference.com/w/cpp/thread/async")

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
  std::cout << "foo: " << str << ' ' << i << std::endl;
}

void bar(const std::string& str)
{
  std::lock_guard<std::mutex> _(g_print_mutex);
  std::cout << "bar: " << str << std::endl;
}

int32_t operator()(int32_t i) 
{
  {
    std::lock_guard<std::mutex> _(g_print_mutex);
    std::cout << "functor: " << i << std::endl; 
  }
  return i + 10;
}
};
}

TEST(
  std_async,
  "std::async runs the given function either asynchronously or lazily-evaluated,\n" 
  "then returns a std::future which holds the result of that function call.\n"
  "The first parameter is the policy which can be:\n"
  " - std::launch::async | std::launch::deferred It is up to the implementation\n" 
  "   whether to perform asynchronous execution or lazy evaluation.\n"
  " - std::launch::async Run the callable object on a new thread.\n"
  " - std::launch::deferred Perform lazy evaluation on the current thread.",
  SECTION(
    "basic example",
    std::cout << GIVEN[0] << std::endl;
    IN(PROTECT(std::future<int32_t> handle = std::async(std::launch::async, foo);))
    IN(handle.wait();)
    IN(std::cout << '\t' << handle.get() << std::endl;)
  )
  SECTION(
    "parallel sum example",
    std::cout << GIVEN[1] << std::endl;
    IN(PROTECT(std::vector<int32_t> v(10000, 1);))
    IN(std::cout << "the sum is: " << parallel_sum(std::begin(v), std::end(v)) << std::endl;)
  )
  SECTION(
    "policy examples",
    IN(X x;)
    DESC_IN(
      "default policy call, implementation dependant",
      auto a1 = std::async(&X::foo, &x, 42, "hello");)
    DESC_IN(
      "lazy evaluation, only when get() or wait() is called is it evaluated",
      auto a2 = std::async(std::launch::deferred, &X::bar, &x, "world!");)
    DESC_IN(
      "async policy, usually evaluated on a separate thread",
      auto a3 = std::async(std::launch::async, X(), 43);)
    IN(a2.wait());
    IN(std::cout << a3.get() << std::endl;)
    std::cout << "// if a1 is not done at this point, destructor of a1 prints \"Hello 42\" here" << std::endl;
  )
)