/**
 * @file strong_typed_enums.cpp
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
  "https://github.com/AnthonyCalandra/modern-cpp-features#strongly-typed-enums\n"
  "https://stackoverflow.com/questions/12581064/enum-vs-strongly-typed-enum\n")

//<<
// Specifying underlying type as `unsigned int`
enum class Color : unsigned int { Red = 0xff0000, Green = 0x00ff00, Blue = 0x0000ff };
// `Red`/`Green` in `Alert` don't conflict with `Color`
enum class Alert : bool { Red, Green };
//>>

TEST(
  strong_typed_enums,
  "Type-safe enums that solve a variety of problems with C-style enums\n" 
  "including: implicit conversions, inability to specify the underlying type,\n"
  "scope pollution.\n",
  SECTION(
    "examples",
    std::cout << GIVEN[0] << std::endl;
    IN(Color c = Color::Red;)
    IN(Alert red = Alert::Red;)
    IN_ERROR(bool b = red;, "error C2440: 'initializing': cannot convert from 'Alert' to 'bool', even if the underlaying type is the same!")
    IN_DESC(bool b = (bool)red;, "explicit casts are needed in this case!")
    IN(std::cout << '\t' << b << std::endl;)
    std::cout << std::endl;
    IN_ERROR(std::cout << '\t' << (Alert::Red != Color::Red) << std::endl;, "error C2676: binary '!=': 'Alert' does not define this operator or a conversion to a type acceptable to the predefined operator")
    IN(std::cout << '\t' << sizeof(c) << std::endl;)
    IN(std::cout << '\t' << uint32_t(c) << std::endl;)
    IN(std::cout << '\t' << sizeof(red) << std::endl;)
    IN(std::cout << '\t' << uint32_t(red) << std::endl;)
  )
)

