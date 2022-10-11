/**
 * @file forwarding_references.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-08-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"
#include "utilities\classes\printer.h"


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#forwarding-references\n")

EXERCISES(
  "1- Implement std::forward, and test it, make sure to compare to the std\n" 
  "implementation in terms of correctness:\n"
  "https://en.cppreference.com/w/cpp/utility/forward#Example\n\n"
  "2- Implement functionality to check the type of an expression and use it on\n"
  "the code from:\n"
  "https://github.com/AnthonyCalandra/modern-cpp-features#forwarding-references\n"
  "Interesting read:\n"
  "https://stackoverflow.com/questions/16637945/empirically-determine-value-category-of-c11-expression\n"
  "https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c\n")		


//<<
namespace {
template<class T>
void f(T&& t)
{
  // using std::forward here is necessary, as 't' is a named variable making it
  // an lvalue of type T&&. @see perfect forwarding.
  printer::print(std::forward<T>(t));
}
}
//>>

TEST(
  forwarding_references,
  "Also known (unofficially) as universal references. A forwarding reference is\n"
  "created with the syntax T&& where T is a template type parameter, or using\n"
  "auto&&. This enables perfect forwarding: the ability to pass arguments while\n"
  "maintaining their value category (e.g. lvalues stay as lvalues,\n"
  "temporaries are forwarded as rvalues).\n",
  SECTION(
    "Template type parameter deduction with lvalues and rvalues",
    std::cout << GIVEN[0] << std::endl;
    IN(int x = 0;)
    IN_DESC(f(0);, "0 is a prvalue, T resolves to 'int', making the type 'int&&'.")
    IN_DESC(f(x);, "x is an lvalue, T resolves to 'int&', making the type 'int& &&', becoming 'int&'.")
    IN(int& y = x;)
    IN_DESC(f(y), "y is an lvalue, T resolves to 'int& &', making the type 'int& & &&', becoming 'int&'.")
    IN_DESC(int&& z = 0;, "z is an lvalue of type 'int&&'.")
    IN_DESC(f(z);, "z is an lvalue, T resolves to 'int&& &', making the type 'int&& & &&', becoming 'int&'.")
    IN_DESC(f(std::move(z));, "std::move() turns an lvalue into an xvalue, T resolves to 'int', making the type 'int&&'.")
  )
)

