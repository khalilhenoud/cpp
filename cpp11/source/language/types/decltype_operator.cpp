/**
 * @file decltype_operator.cpp
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

#include <string>
#include <cstdlib>
#include <typeinfo>
#include <memory>
#include <type_traits>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif


namespace {
// see: https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
// The problem here is the typeid() operator, which itself loses the
// cv-qualifiers and references.
template <class T>
std::string type_name()
{
  typedef typename std::remove_reference<T>::type TR;
  std::unique_ptr<char, void(*)(void*)> own
  (
#ifndef _MSC_VER
    abi::__cxa_demangle(typeid(TR).name(), nullptr,
      nullptr, nullptr),
#else
    nullptr,
#endif
    std::free
  );
  std::string r = own != nullptr ? own.get() : typeid(TR).name();
  if (std::is_const<TR>::value)
    r += " const";
  if (std::is_volatile<TR>::value)
    r += " volatile";
  if (std::is_lvalue_reference<T>::value)
    r += "&";
  else if (std::is_rvalue_reference<T>::value)
    r += "&&";
  return r;
}
}

namespace {
template <typename X, typename Y>
auto add(X x, Y y) -> decltype(x + y)
{
  return x + y;
}
}

REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#decltype
https://stackoverflow.com/questions/16637945/empirically-determine-value-category-of-c11-expression
https://stackoverflow.com/questions/14115744/significance-of-parentheses-in-decltypec
)--"
)

TEST(
  basics,
R"--(
decltype is an operator which returns the declared type of an expression passed
to it. cv-qualifiers and references are maintained if they are part of the 
expression.
)--",
  SECTION(
    "Example with named variables",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(int32_t i = 100;)
    IN(print_safe("\t%s\n", type_name<decltype(i)>().c_str());)
    IN(const int32_t ci = 1000;)
    IN(print_safe("\t%s\n", type_name<decltype(ci)>().c_str());)
    IN(const uint32_t cui = 500u;)
    IN(print_safe("\t%s\n", type_name<decltype(cui)>().c_str());)
    IN(uint8_t u = 'a';)
    IN(print_safe("\t%s\n", type_name<decltype(u)>().c_str());)
    IN(const uint8_t cu = 'b';)
    IN(print_safe("\t%s\n", type_name<decltype(cu)>().c_str());)
    IN(float f = 3.25f;)
    IN(print_safe("\t%s\n", type_name<decltype(f)>().c_str());)
    IN(float& fr = f;)
    IN(print_safe("\t%s\n", type_name<decltype(fr)>().c_str());)
    IN(double d = 5.124;)
    IN(print_safe("\t%s\n", type_name<decltype(d)>().c_str());)
    IN(double *ptr_d = &d;)
    IN(print_safe("\t%s\n", type_name<decltype(ptr_d)>().c_str());)
    IN(const double * const cptr_cd = &d;)
    IN(print_safe("\t%s\n", type_name<decltype(cptr_cd)>().c_str());)
  )
  SECTION(
R"--(
decltype can return the declared type of an entity (hence the name), but can
also be used to query the type of an expression. However, in the latter case the
resulting type is 'adjusted' according to the value category of that expression:
an lvalue expression results in an lvalue reference type, an xvalue in an rvalue
reference type, and a prvalue in just the type.
)--",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(int32_t i = 2;)
    IN(const int32_t ci = 4;)
    IN(print_safe("\t%s\n", type_name<decltype(1)>().c_str());)
    IN(print_safe("\t%s\n", type_name<decltype(std::move(i))>().c_str());)
    IN(print_safe("\t%s\n", type_name<decltype(i)>().c_str());)
    IN(print_safe("\t%s\n", type_name<decltype(ci)>().c_str());)
    IN(print_safe("\t%s\n", type_name<decltype((i))>().c_str());)
    print_safe("\n");
    IN(decltype(i) b = i;)
    IN(const decltype(b)& rb = b;)
    IN(int&& f = 1;)
    IN(decltype(f) m = 2;)
    IN(print_safe("\t%s\n", type_name<decltype(f)>().c_str());)
    IN(print_safe("\t%s\n", type_name<decltype(m)>().c_str());)
    IN(print_safe("\t%s\n", type_name<decltype((f))>().c_str());)
    IN(print_safe("\t%s\n", type_name<decltype((rb))>().c_str());)
    print_safe("\n");
    IN(int32_t& k = i;)
    IN(print_safe("\t%s\n", type_name<decltype(k)>().c_str());)
    IN(print_safe("\t%s\n", type_name<decltype((k))>().c_str());)
  )
  SECTION(
    "Trailing return type usage.",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(print_safe("\t%f\n", add(1, 2.1f));)
    IN_DESC(decltype(add(1, 2.1f)) f = 2.f;, "this is prvalue decltype is 'float'")
    IN(print_safe("\t%s\n", type_name<decltype(f)>().c_str());)
  )
)

