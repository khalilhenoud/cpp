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

#include <iostream>
#include <string>
#include <cmath>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#user-defined-literals\n")

//<<
// 'unsigned long long' parameter required for integer literal.
// Changing 'tempCelcius' to int32_t causes compilation error.
unsigned long long operator "" _celcius(unsigned long long tempCelsius)
{
  return std::llround(tempCelsius * 1.8 + 32);
}
//>>

//<<
int32_t operator "" _int(const char* str, std::size_t length)
{
  return std::stoi(str);
}
//>>

TEST(
  user_defined_literals,
  "User-defined literals allow you to extend the language and add your own\n"
  "syntax. To create a literal, define a T operator "" X(...) { ... } function\n"
  "that returns a type T, with a name X. Note that the name of this function\n"
  "defines the name of the literal. Any literal names not starting with an\n"
  "underscore are reserved and won't be invoked. There are rules on what\n"
  "parameters a user-defined literal function should accept, according to what\n"
  "type the literal is called on.\n",
  SECTION(
    "celcius to farenheit conversion.",
    std::cout << GIVEN[0] << std::endl;
    IN(std::cout << '\t' << 24_celcius << std::endl;)
    IN(std::cout << '\t' << 40_celcius << std::endl;)
  )
  SECTION(
    "String to int conversion.",
    std::cout << GIVEN[1] << std::endl;
    IN(std::cout << '\t' << "112001"_int << std::endl;)
    IN(std::cout << '\t' << "650"_int << std::endl;)
    IN(std::cout << '\t' << "-115"_int << std::endl;)
  )
)

