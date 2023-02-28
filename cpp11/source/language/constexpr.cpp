/**
 * @file constexpr.cpp
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
https://github.com/AnthonyCalandra/modern-cpp-features#constexpr
https://en.cppreference.com/w/cpp/language/constexpr
)--"
  )

namespace {
constexpr int32_t constexpr_square(int32_t i)
{
  return i * i;
}

int32_t square(int32_t i)
{
  return i * i;
}
}

namespace {
struct Complex {
  constexpr Complex(double r, double i) : re(r), im(i) {}
  constexpr double real() const { return re; }
  constexpr double imag() { return im; }

private:
  double re;
  double im;
};
}

TEST(
  basics,
R"--(
Constant expressions are expressions evaluated by the compiler at compile-time. 
Only non-complex computations can be carried out in a constant expression. Use 
the constexpr specifier to indicate the variable, function, etc. is a constant 
expression.
)--",
  SECTION(
    "compiler optimization and disassembly",
    print_safe("%s\n", GIVEN[0].c_str());
    print_safe( "// Assembly:\n"
                "// mov DWORD PTR [rbp-4], 4\n");
    IN(int32_t a = constexpr_square(2);)
    print_safe("\n");

    print_safe( "// Assembly:\n"
                "// mov edi, 2\n"
                "// call square(int32_t)\n"
                "// mov DWORD PTR [rbp-8], eax\n");
    IN(int32_t b = square(2);)
    print_safe("\n");
    IN_ERROR(constexpr int32_t c = square(2);, "error C2131: expression did not evaluate to a constant")
    IN(constexpr int32_t c = constexpr_square(2);)
  )
  SECTION(
    "constexpr values are those that the compiler can evaluate at compile-time",
    IN_DESC(constexpr int32_t c = constexpr_square(2);, "All constexpr variables are const")
    IN_ERROR(int32_t& lref = c;, "error C2440: 'initializing': cannot convert from 'const int32_t' to 'int32_t &'")
    IN(const int32_t& lref = c;)
    print_safe("\n");
    IN_ERROR(constexpr int32_t& cexplref = c;, "error C2440: 'initializing': cannot convert from 'const int32_t' to 'int32_t &'")
    IN(constexpr const int32_t& cexplref = c;)
    print_safe("\n");
    IN(const int32_t d = 2;)
    IN_ERROR(constexpr const int32_t& cexplrefd = d;, "error: 'd' is not a constant expression")
  )
  SECTION(
    "Constant expressions with classes example",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(PROTECT(constexpr Complex complex1{1., 2.};))
    IN(print_safe("\t%f\n", complex1.real());)
    IN(PROTECT(Complex complex2{4., 5. };))
    IN(print_safe("\t%f\n", complex2.real());)
  )
)

