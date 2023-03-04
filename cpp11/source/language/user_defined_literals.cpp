/**
 * @file user_defined_literals.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <string>
#include <cmath>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#user-defined-literals")

namespace {
// 'unsigned long long' parameter required for integer literal.
// Changing 'tempCelcius' to int32_t causes compilation error.
unsigned long long operator "" _celcius(unsigned long long tempCelsius)
{
  return std::llround(tempCelsius * 1.8 + 32);
}
}

namespace {
int32_t operator "" _int(const char* str, std::size_t length)
{
  return std::stoi(str);
}
}

TEST(
  user_defined_literals,
R"--(
User-defined literals allow you to extend the language and add your own syntax. 
To create a literal, define a T operator "" X(...) { ... } function that returns
a type T, with a name X. Note that the name of this function defines the name of
the literal. 
Any literal names not starting with an underscore are reserved and won't be
invoked. There are rules on what parameters a user-defined literal function
should accept, according to what type the literal is called on.
)--",
  SECTION(
    "celcius to farenheit conversion.",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(print_safe("\t%llu\n", 24_celcius);)
    IN(print_safe("\t%llu\n", 40_celcius);)
  )
  SECTION(
    "String to int conversion.",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(print_safe("\t%i\n", "112001"_int);)
    IN(print_safe("\t%i\n", "650"_int);)
    IN(print_safe("\t%i\n", "-115"_int);)
  )
)

