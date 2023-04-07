/**
 * @file function.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <functional>


REFERENCES(
R"--(
https://en.cppreference.com/w/cpp/utility/functional/function
https://en.wikipedia.org/wiki/C%2B%2B11#Core_language_usability_enhancements
)--"
)

namespace {
void print_num(int i)
{
  print_safe("\t%i\n", i);
}

// see first reference.
struct Foo {
  Foo(int num) : num_(num) { ANNOUNCE(true); }
  void print_add(int i) const { print_num(num_+i); }
  int num_;
};

struct PrintNum {
  void operator()(int i) const
  {
    print_num(i);
  }
};
}

namespace {
int32_t factorial(int32_t n)
{
  // error C3536: 'fac': cannot be used before it is initialized
  //auto fac = [&](int n){ return (n < 2) ? 1: n * fac(n -1);};
  // store a lambda object to emulate "recursive lambda".
  std::function<int(int)> fac = [&](int n){ return (n < 2) ? 1: n * fac(n -1);};
  return fac(n);
}
}

TEST(
  std_function,
R"--(
Polymorphic wrappers for function objects are similar to function pointers in
semantics and syntax, but are less tightly bound and can indiscriminately refer
to anything which can be called (function pointers, member function pointers, or
functors) whose arguments are compatible with those of the wrapper.
)--",
  SECTION(
    "basic compatibility example",
    IN(PROTECT(std::function<int (int, int)> func;))
    IN(std::plus<int> add;)
    IN(func = add;)
    IN(print_safe("\t%i\n", func(1, 2));)
    IN(PROTECT(std::function<bool (short, short)> func2;))
    IN_DESC(func2 = add;, "this will work as long as the arguments and return type are compatible")
    IN(print_safe("\t%i\n", func2(1, 2));)
    IN(print_safe("\t%i\n", func2(0, 0));)
  )
  SECTION(
    "extensive examples",
    print_safe("%s\n", GIVEN[0].c_str());
    DESC_IN("store a free function", 
    std::function<void(int)> f_display = print_num;)
    IN(f_display(-9);)
    print_safe("\n");

    DESC_IN("store a lambda", 
    std::function<void()> f_display_42 = [](){print_num(42);};)
    IN(f_display_42();)
    print_safe("\n");

    DESC_IN("store the result of a call to std::bind", 
    PROTECT(
    std::function<void()> f_display_31337 = std::bind(print_num, 31337);))
    IN_DESC(f_display_31337();, "no need to pass the param, it is already bound to it!")
    print_safe("\n");

    DESC_IN("store a call to a member function", 
    PROTECT(
    std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;))
    IN(const Foo foo(314159);)
    IN(f_add_display(foo, 1);)
    IN_DESC(f_add_display(314169, 1);, "a temp Foo object is constructed in this case!")
    print_safe("\n");

    DESC_IN("store a call to a data member accessor", 
    std::function<int(Foo const&)> f_num = &Foo::num_;)
    IN(print_safe("\tnum_: %i\n", f_num(foo));)
    print_safe("\n");

    DESC_IN("store a call to a member function and object", 
    PROTECT(std::function<void(int)> f_add_display2 = std::bind( &Foo::print_add, foo, std::placeholders::_1 );))
    IN(f_add_display2(2);)
    print_safe("\n");

    DESC_IN("store a call to a member function and object ptr", 
    PROTECT(std::function<void(int)> f_add_display3 = std::bind( &Foo::print_add, &foo, std::placeholders::_1 );))
    IN(f_add_display3(3);)
    print_safe("\n");

    DESC_IN("store a call to a function object", 
    std::function<void(int)> f_display_obj = PrintNum();)
    IN(f_display_obj(18);)
  )
  SECTION(
    "emulating recursive lambdas",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(PROTECT(for (int i{5}; i != 8; ++i) print_safe("factorial(%i): %i\n", i, factorial(i));))
  )
)