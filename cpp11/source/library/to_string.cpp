/**
 * @file to_string.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <string>
#include <iostream>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#stdto_string\n"
  "https://en.cppreference.com/w/cpp/string/basic_string/to_string")

TEST(
  to_string,
  "Converts a numeric argument to a std::string.",
  SECTION(
    "example",
    IN(std::cout << std::to_string(1.2) << std::endl;)
    IN(std::cout << std::to_string(123) << std::endl;)
    IN(std::cout << std::to_string(0x11) << std::endl;)
  )
)