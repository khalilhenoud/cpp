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
#include <typeinfo>


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#auto
https://stackoverflow.com/questions/8542873/c11-auto-semantics
https://en.cppreference.com/w/cpp/language/auto
https://stackoverflow.com/questions/7138588/c11-auto-what-if-it-gets-a-constant-reference
https://stackoverflow.com/questions/28621844/is-there-a-typeid-for-references
)--"
)

EXERCISES(
R"--(
https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
)--"
)

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
R"--(
'typeid' loses references and top level cv for anything but pointer referenced 
types. See reference(5).
'auto' never evaluates to a reference, and const is only maintained for
referenced types (const int*, const int&). See reference(4).
)--",
  SECTION(
    "simple types",
    IN(auto d = 0.2;)
    IN(print_safe("\t%s\n", typeid(d).name());)
    IN(const auto cd = 0.2;)
    IN(print_safe("\t%s\n", typeid(cd).name());)
    IN(auto i = 1;)
    IN(print_safe("\t%s\n", typeid(i).name());)
    IN(auto& ri = i;)
    IN(print_safe("\t%s\n", typeid(ri).name());)
    IN(const auto& cri = i;)
    IN(print_safe("\t%s\n", typeid(cri).name());)
  )
  SECTION(
    "pointer types",
    IN(auto i = 1;)
    IN(const auto* pi = &i;)
    IN(print_safe("\t%s\n", typeid(pi).name());)
    IN_DESC(const auto* const cpi = &i;, "notice that only the const for the referenced type is retained!")
    IN(print_safe("\t%s\n", typeid(cpi).name());)
  )
  SECTION(
    "intializer list",
    IN(PROTECT(auto il = { 0, 1, 2 };))
    IN(print_safe("\t%s\n", typeid(il).name());)
    IN(auto& ril = il;)
    IN(print_safe("\t%s\n", typeid(ril).name());)
  )
  SECTION(
    "universal references",
    IN(auto i = 1;)
    IN_DESC(auto&& rri = 3;, "this is a universal instance of type int&&, typeid still loses the reference though!")
    IN(print_safe("\t%s\n", typeid(rri).name());)
    IN_DESC(auto&& lri = i;, "this is a universal instance of type int&, typeid still loses the reference though!")
    IN(print_safe("\t%s\n", typeid(lri).name());)
  )
  SECTION(
    "initialization",
    IN_DESC(PROTECT(auto k1 = 2, k2 = 3, k3 = 4;), "every member must be initialied unlike with explicit types below.")
    IN(print_safe("\t%s\n", typeid(k1).name());)
    IN(PROTECT(int k4, k5, k6 = 0;))
    IN((void)k4; (void)k5; (void)k6;)
    IN_ERROR(auto j;, "error C3531: 'j': a symbol whose type contains 'auto' must have an initializer")
  )
  SECTION(
    "'auto' usage with function templates and lambdas",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(auto add = [](int n, int m) { return m + n; };))
    IN(PROTECT(print_safe("\t%i\n", add(2, 5));))
    IN_ERROR(PROTECT(auto& sub = [](int n, int m) { return n - m; };), "error: cannot bind non-const lvalue reference to an rvalue")
    IN(PROTECT(auto&& sub = [](int n, int m) { return n - m; };))
    IN(PROTECT(print_safe("\t%i\n", sub(8, 2));))
    IN(print_safe("\t%i\n", mul(1, 2));)
    IN(print_safe("\t%d\n", mul(1, 2.0));)
    IN(print_safe("\t%d\n", mul(1.5, 1.5));)
  )
)

