/**
 * @file attributes.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#attributes
https://en.cppreference.com/w/cpp/language/attributes
)--"
  )

namespace {
// `noreturn` attribute indicates `f` doesn't return.
[[noreturn]] void f()
{
  throw "error";
}
}

TEST(
  attributes,
R"--(
Attributes provide a universal syntax over __attribute__(...), __declspec, etc. 
C++11 only defines 2 attributes (noreturn, carries_dependency), more attributes 
can be supported based on the compiler. However the usage of attributes can be 
greatly extended in the proper context, see the link below:
https://www.codesynthesis.com/~boris/blog/2012/04/18/cxx11-generalized-attributes/
)--",
  SECTION(
    "'noreturn' function example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(
      try
      {
        f();
      }
      catch (...)
      {
        print_safe("Caught the [[noreturn]] exception throwing function.\n");
      }
    )
  )
)

