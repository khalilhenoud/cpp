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

#include <functional>


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#lambda-expressions
https://stackoverflow.com/questions/2431596/modifying-reference-member-from-const-member-function-in-c
)--"
)

namespace {
struct capture_this {
  void print_me(void)
  {
    [this]() {
      print_safe("\t%s\n", this->name);
    }();
  }

  const char* name = "does have access to 'this'";
};
}

namespace {
// C++14 the function could have been declared 'decltype(auto)' or 'auto'.
template<class Func, class... Args>
auto func_call(Func&& func, Args&&... args) -> decltype(func(args...))
{
  return func(args...);
}
}

TEST(
  lamba_expressions,
R"--(
A lambda is an unnamed function object capable of capturing variables in scope.
It features: a capture list; an optional set of parameters with an optional
trailing return type; and a body.
)--",
  SECTION(
    "[] - captures nothing.",
    IN(print_safe("%s\n", []() { return "Lambda with no capture clause."; }());)
  )
  SECTION(
    "[=] - capture local objects (local variables, parameters) in scope by value",
    IN(PROTECT(int32_t i = 5, v = 10, k = 15;))
    IN(print_safe("%i\n", [=]() { return i + v + k; }());)
    IN(print_safe("i = %i, v = %i, k = %i\n", i, v, k);)
  )
  SECTION(
    "[&] - capture local objects (local variables, parameters) in scope by reference",
    IN(PROTECT(int32_t i = 5, v = 10, k = 15;))
    IN(print_safe("%i\n", [&]() { i *= 2;  return i + v + k; }());)
    IN(print_safe("i = %i, v = %i, k = %i\n", i, v, k);)
  )
  SECTION(
    "[this] - capture this by reference.",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(capture_this().print_me();)
  )
  SECTION(
    "[a, &b] - capture objects a by value, b by reference.",
    IN(PROTECT(int32_t i = 5, v = 10, k = 15;))
    IN(PROTECT(print_safe("%i\n", [i, &v, k]() { v*= 2; return i + v + k; }());))
    IN(print_safe("i = %i, v = %i, k = %i\n", i, v, k);)
  )
  SECTION(
R"--(
By default, value-captures cannot be modified inside the lambda because the
compiler-generated method is marked as const. The mutable keyword allows
modifying captured variables. The keyword is placed after the parameter-list 
(which must be present even if it is empty).
)--",
    IN(PROTECT(int32_t i = 5, v = 10, k = 15;))
    IN_ERROR(print_safe("%i\n", [=]() { i = 55; return i; }());, "error C3491: 'i': a by copy capture cannot be modified in a non-mutable lambda.")
    IN_DESC(print_safe("%i\n", [=]() mutable { i = 55; return i; }());, "note that 'i' is only modified inside the function!")
    IN(print_safe("i = %i, v = %i, k = %i\n", i, v, k);)
  )
  SECTION(
    "Trailing return type in lambda.",
    IN(PROTECT(int32_t i = 5, v = 55, k = 15;))
    IN(print_safe("%c\n", [=]() -> uint8_t { return i + v + k; }());)
  )
)

TEST(
  usage_examples,
  "More examples, in particular with regards on lambda assignment.",
  SECTION(
R"--(
A lambda is an unnamed functor, we can use 'auto' to capture it. A lamba
expression is a prvalue.
)--",
    IN(auto uno = []() { return "example uno"; };)
    IN(print_safe("%s\n", uno());)
    IN_ERROR(auto& due = []() { return "due"; };, "error: cannot bind non-const lvalue reference to an rvalue")
    IN(const auto& due = []() { return "due"; };)
    IN(print_safe("%s\n", due());)
    IN(auto&& tre = []() { return "tre"; };)
    IN(print_safe("%s\n", tre());)
  )
  SECTION(
    "Binding to std::function<> example.",
    IN(std::function<const char*()> quatro = []() { return "quatro"; };)
    IN(print_safe("%s\n", quatro());)
  )
  SECTION(
    "Using a lambda as a function argument.",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(auto&& add = [](int32_t a, int32_t b, float c) { return a + b + c; };)
    IN(print_safe("%f\n", func_call(add, 3, 3, 2.5f));)
  )
)

