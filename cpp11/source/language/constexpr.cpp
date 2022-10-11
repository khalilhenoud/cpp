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

#include <iostream>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#constexpr\n"
  "https://en.cppreference.com/w/cpp/language/constexpr\n")

//<<
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
//>>

//<<
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
//>>

TEST(
  basics,
  "Constant expressions are expressions evaluated by the compiler at\n" 
  "compile-time. Only non-complex computations can be carried out in a constant\n"
  "expression. Use the constexpr specifier to indicate the variable, function,\n"
  "etc. is a constant expression.\n",
  SECTION(
    "compiler optimization and disassembly",
    std::cout << GIVEN[0] << std::endl;
    DESC_IN("// Assembly:\n"
            "// mov DWORD PTR [rbp-4], 4", int32_t a = constexpr_square(2);)
    std::cout << std::endl;
    DESC_IN("// Assembly:\n"
            "// mov edi, 2\n"
            "// call square(int32_t)\n"
            "// mov DWORD PTR [rbp-8], eax", int32_t b = square(2);)
    std::cout << std::endl;
    IN_ERROR(constexpr int32_t c = square(2);, "error C2131: expression did not evaluate to a constant")
    IN(constexpr int32_t c = constexpr_square(2);)
  )
  SECTION(
    "constexpr values are those that the compiler can evaluate at compile-time",
    IN_DESC(constexpr int32_t c = constexpr_square(2);, "All constexpr variables are const")
    IN_ERROR(int32_t& lref = c;, "error C2440: 'initializing': cannot convert from 'const int32_t' to 'int32_t &'")
    IN(const int32_t& lref = c;)
    std::cout << std::endl;
    IN_ERROR(constexpr int32_t& cexplref = c;, "error C2440: 'initializing': cannot convert from 'const int32_t' to 'int32_t &'")
    IN(constexpr const int32_t& cexplref = c;)
    std::cout << std::endl;
    IN(const int32_t d = 2;)
    IN_ERROR(constexpr const int32_t& cexplrefd = d;, "error: 'd' is not a constant expression")
  )
  SECTION(
    "Constant expressions with classes example",
    std::cout << GIVEN[1] << std::endl;
    IN(PROTECT(constexpr Complex complex1{1., 2.};))
    IN(std::cout << '\t' << complex1.real() << std::endl;)
    IN(PROTECT(Complex complex2{ 4., 5. };))
    IN(std::cout << '\t' << complex2.real() << std::endl;)
  )
)

