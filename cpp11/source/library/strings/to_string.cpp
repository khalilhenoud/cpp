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


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#stdto_string
https://en.cppreference.com/w/cpp/string/basic_string/to_string
)--"
)

TEST(
  to_string,
  "Converts a numeric argument to a std::string.",
  SECTION(
    "example",
    IN(print_safe("\t%s\n", std::to_string(1.2).c_str());)
    IN(print_safe("\t%s\n", std::to_string(123).c_str());)
    IN(print_safe("\t%s\n", std::to_string(0x11).c_str());)
  )
)