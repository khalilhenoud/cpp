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

#include <iostream>
//<<
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
//>>

//<<
namespace {
template <typename X, typename Y>
auto add(X x, Y y) -> decltype(x + y)
{
  return x + y;
}
}
//>>

REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#decltype\n"
  "https://stackoverflow.com/questions/16637945/empirically-determine-value-category-of-c11-expression\n"
  "https://stackoverflow.com/questions/14115744/significance-of-parentheses-in-decltypec\n")

TEST(
  basics,
  "decltype is an operator which returns the declared type of an expression\n"
  "passed to it. cv-qualifiers and references are maintained if they are part\n"
  "of the expression.\n",
  SECTION(
    "Example with named variables",
    std::cout << GIVEN[0] << std::endl;
    IN(int32_t i = 100;)
    IN(std::cout << '\t' << type_name<decltype(i)>() << std::endl;)
    IN(const int32_t ci = 1000;)
    IN(std::cout << '\t' << type_name<decltype(ci)>() << std::endl;)
    IN(const uint32_t cui = 500u;)
    IN(std::cout << '\t' << type_name<decltype(cui)>() << std::endl;)
    IN(uint8_t u = 'a';)
    IN(std::cout << '\t' << type_name<decltype(u)>() << std::endl;)
    IN(const uint8_t cu = 'b';)
    IN(std::cout << '\t' << type_name<decltype(cu)>() << std::endl;)
    IN(float f = 3.25f;)
    IN(std::cout << '\t' << type_name<decltype(f)>() << std::endl;)
    IN(float& fr = f;)
    IN(std::cout << '\t' << type_name<decltype(fr)>() << std::endl;)
    IN(double d = 5.124;)
    IN(std::cout << '\t' << type_name<decltype(d)>() << std::endl;)
    IN(double *ptr_d = &d;)
    IN(std::cout << '\t' << type_name<decltype(ptr_d)>() << std::endl;)
    IN(const double * const cptr_cd = &d;)
    IN(std::cout << '\t' << type_name<decltype(cptr_cd)>() << std::endl;)
  )
  SECTION(
    "decltype can return the declared type of an entity (hence the name), but\n"
    "can also be used to query the type of an expression. However, in the latter\n"
    "case the resulting type is 'adjusted' according to the value category of\n"
    "that expression: an lvalue expression results in an lvalue reference type,\n"
    "an xvalue in an rvalue reference type, and a prvalue in just the type.",
    std::cout << GIVEN[0] << std::endl;
    IN(int32_t i = 2;)
    IN(const int32_t ci = 4;)
    IN(std::cout << '\t' << type_name<decltype(1)>() << std::endl;)
    IN(std::cout << '\t' << type_name<decltype(std::move(i))>() << std::endl;)
    IN(std::cout << '\t' << type_name<decltype(i)>() << std::endl;)
    IN(std::cout << '\t' << type_name<decltype(ci)>() << std::endl;)
    IN(std::cout << '\t' << type_name<decltype((i))>() << std::endl;)
    std::cout << std::endl;
    IN(decltype(i) b = i;)
    IN(const decltype(b)& rb = b;)
    IN(int&& f = 1;)
    IN(decltype(f) m = 2;)
    IN(std::cout << '\t' << type_name<decltype(f)>() << std::endl;)
    IN(std::cout << '\t' << type_name<decltype(m)>() << std::endl;)
    IN(std::cout << '\t' << type_name<decltype((f))>() << std::endl;)
    IN(std::cout << '\t' << type_name<decltype((rb))>() << std::endl;)
    std::cout << std::endl;
    IN(int32_t& k = i;)
    IN(std::cout << '\t' << type_name<decltype(k)>() << std::endl;)
    IN(std::cout << '\t' << type_name<decltype((k))>() << std::endl;)
  )
  SECTION(
    "Trailing return type usage.",
    std::cout << GIVEN[1] << std::endl;
    IN(std::cout << '\t' << add(1, 2.1f) << std::endl;)
    IN_DESC(decltype(add(1, 2.1f)) f = 2.f;, "this is prvalue decltype is 'float'")
    IN(std::cout << '\t' << type_name<decltype(f)>() << std::endl;)
  )
)

