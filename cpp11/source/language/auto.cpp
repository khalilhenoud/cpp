/**
 * @file auto.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <type_traits>
#include <iostream>
#include <typeinfo>


REFERENCES(
  "1- https://github.com/AnthonyCalandra/modern-cpp-features#auto\n"
  "2- https://stackoverflow.com/questions/8542873/c11-auto-semantics\n"
  "3- https://en.cppreference.com/w/cpp/language/auto\n"
  "4- https://stackoverflow.com/questions/7138588/c11-auto-what-if-it-gets-a-constant-reference\n"
  "5- https://stackoverflow.com/questions/28621844/is-there-a-typeid-for-references")

EXERCISES("https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c")

namespace {
// 'auto' in template return type, this is very powerful. Note that the trailing
// return type has access to its parameters, and 'this' when appropriate.
template<class U, class V>
auto mul(U u, V v) -> decltype(u* v)
{
  return u * v;
}
}

TEST(
  auto_placeholder_type_deduction,
  "'typeid' loses references and top level cv for anything but pointer\n"
  "referenced types. See reference(5).\n"
  "'auto' never evaluates to a reference, and const is only maintained for\n"
  "referenced types (const int*, const int&). See reference(4).",
  SECTION(
    "simple types",
    IN(auto d = 0.2;)
    IN(std::cout << '\t' << typeid(d).name() << std::endl;)
    IN(const auto cd = 0.2;)
    IN(std::cout << '\t' << typeid(cd).name() << std::endl;)
    IN(auto i = 1;)
    IN(std::cout << '\t' << typeid(i).name() << std::endl;)
    IN(auto& ri = i;)
    IN(std::cout << '\t' << typeid(ri).name() << std::endl;)
    IN(const auto& cri = i;)
    IN(std::cout << '\t' << typeid(cri).name() << std::endl;)
  )
  SECTION(
    "pointer types",
    IN(auto i = 1;)
    IN(const auto* pi = &i;)
    IN(std::cout << '\t' << typeid(pi).name() << std::endl;)
    IN_DESC(const auto* const cpi = &i;, "notice that only the const for the referenced type is retained!")
    IN(std::cout << '\t' << typeid(cpi).name() << std::endl;)
  )
  SECTION(
    "intializer list",
    IN(PROTECT(auto il = { 0, 1, 2 };))
    IN(std::cout << '\t' << typeid(il).name() << std::endl;)
    IN(auto& ril = il;)
    IN(std::cout << '\t' << typeid(ril).name() << std::endl;)
  )
  SECTION(
    "universal references",
    IN(auto i = 1;)
    IN_DESC(auto&& rri = 3;, "this is a universal instance of type int&&, typeid still loses the reference though!")
    IN(std::cout << '\t' << typeid(rri).name() << std::endl;)
    IN_DESC(auto&& lri = i;, "this is a universal instance of type int&, typeid still loses the reference though!")
    IN(std::cout << '\t' << typeid(lri).name() << std::endl;)
  )
  SECTION(
    "initialization",
    IN_DESC(PROTECT(auto k1 = 2, k2 = 3, k3 = 4;), "every member must be initialied unlike with explicit types below.")
    IN(std::cout << '\t' << typeid(k1).name() << std::endl;)
    IN(PROTECT(int k4, k5, k6 = 0;))
    IN((void)k4; (void)k5; (void)k6;)
    IN_ERROR(auto j;, "error C3531: 'j': a symbol whose type contains 'auto' must have an initializer")
  )
  SECTION(
    "'auto' usage with function templates and lambdas",
    std::cout << GIVEN[0] << std::endl;
    IN(PROTECT(auto add = [](int n, int m) { return m + n; };))
    IN(PROTECT(std::cout << '\t' << add(2, 5) << std::endl;))
    IN_ERROR(PROTECT(auto& sub = [](int n, int m) { return n - m; };), "error: cannot bind non-const lvalue reference to an rvalue")
    IN(PROTECT(auto&& sub = [](int n, int m) { return n - m; };))
    IN(PROTECT(std::cout << '\t' << sub(8, 2) << std::endl;))
    IN(std::cout << '\t' << mul(1, 2) << std::endl;)
    IN(std::cout << '\t' << mul(1, 2.0) << std::endl;)
    IN(std::cout << '\t' << mul(1.5, 1.5) << std::endl;)
  )
)

