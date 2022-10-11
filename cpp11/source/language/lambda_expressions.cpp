/**
 * @file lambda_expressions.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <functional>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#lambda-expressions\n"
  "https://stackoverflow.com/questions/2431596/modifying-reference-member-from-const-member-function-in-c\n")

//<<
namespace {
struct capture_this {
  void print_me(void)
  {
    [this]() {
      std::cout << '\t' << this->name << std::endl;
    }();
  }

  const char* name = "does have access to 'this'";
};
}
//>>

//<<
namespace {
// C++14 the function could have been declared 'decltype(auto)' or 'auto'.
template<class Func, class... Args>
auto func_call(Func&& func, Args&&... args) -> decltype(func(args...))
{
  return func(args...);
}
}
//>>

TEST(
  lamba_expressions,
  "A lambda is an unnamed function object capable of capturing variables in\n" 
  "scope. It features: a capture list; an optional set of parameters with an\n"
  "optional trailing return type; and a body.\n",
  SECTION(
    "[] - captures nothing.",
    IN(std::cout << []() { return "Lambda with no capture clause."; }() << std::endl;)
  )
  SECTION(
    "[=] - capture local objects (local variables, parameters) in scope by value",
    IN(PROTECT(int32_t i = 5, v = 10, k = 15;))
    IN(std::cout << [=]() { return i + v + k; }() << std::endl;)
    IN(std::cout << "i = " << i << ", v = " << v << ", k = " << k << std::endl;)
  )
  SECTION(
    "[&] - capture local objects (local variables, parameters) in scope by reference",
    IN(PROTECT(int32_t i = 5, v = 10, k = 15;))
    IN(std::cout << [&]() { i *= 2;  return i + v + k; }() << std::endl;)
    IN(std::cout << "i = " << i << ", v = " << v << ", k = " << k << std::endl;)
  )
  SECTION(
    "[this] - capture this by reference.",
    std::cout << GIVEN[0] << std::endl;
    IN(capture_this().print_me();)
  )
  SECTION(
    "[a, &b] - capture objects a by value, b by reference.",
    IN(PROTECT(int32_t i = 5, v = 10, k = 15;))
    IN(PROTECT(std::cout << [i, &v, k]() { v*= 2; return i + v + k; }() << std::endl;))
    IN(std::cout << "i = " << i << ", v = " << v << ", k = " << k << std::endl;)
  )
  SECTION(
    "By default, value-captures cannot be modified inside the lambda because the\n"
    "compiler-generated method is marked as const. The mutable keyword allows\n"
    "modifying captured variables. The keyword is placed after the\n" 
    "parameter-list (which must be present even if it is empty).",
    IN(PROTECT(int32_t i = 5, v = 10, k = 15;))
    IN_ERROR(std::cout << [=]() { i = 55; return i; }() << std::endl;, "error C3491: 'i': a by copy capture cannot be modified in a non-mutable lambda.")
    IN_DESC(std::cout << [=]() mutable { i = 55; return i; }() << std::endl;, "note that 'i' is only modified inside the function!")
    IN(std::cout << "i = " << i << ", v = " << v << ", k = " << k << std::endl;)
  )
  SECTION(
    "Trailing return type in lambda.",
    IN(PROTECT(int32_t i = 5, v = 55, k = 15;))
    IN(std::cout << [=]() -> uint8_t { return i + v + k; }() << std::endl;)
  )
)

TEST(
  usage_examples,
  "More examples, in particular with regards on lambda assignment.\n",
  SECTION(
    "A lambda is an unnamed functor, we can use 'auto' to capture it. A lamba\n"
    "expression is a prvalue.",
    IN(auto uno = []() { return "example uno"; };)
    IN(std::cout << uno() << std::endl;)
    IN_ERROR(auto& due = []() { return "due"; };, "error: cannot bind non-const lvalue reference to an rvalue")
    IN(const auto& due = []() { return "due"; };)
    IN(std::cout << due() << std::endl;)
    IN(auto&& tre = []() { return "tre"; };)
    IN(std::cout << tre() << std::endl;)
  )
  SECTION(
    "Binding to std::function<> example.",
    IN(std::function<const char*()> quatro = []() { return "quatro"; };)
    IN(std::cout << quatro() << std::endl;)
  )
  SECTION(
    "Using a lambda as a function argument.",
    std::cout << GIVEN[1] << std::endl;
    IN(auto&& add = [](int32_t a, int32_t b, float c) { return a + b + c; };)
    IN(std::cout << func_call(add, 3, 3, 2.5f) << std::endl;)
  )
)

