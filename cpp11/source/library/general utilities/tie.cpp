/**
 * @file tie.cpp
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

#include <tuple>
#include <utility>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#stdtie")

TEST(
  tie,
R"--(
Creates a tuple of lvalue references. Useful for unpacking std::pair and
std::tuple objects. Use std::ignore as a placeholder for ignored values.
In C++17, structured bindings should be used instead.
)--",
  SECTION(
    "example",
    DESC_IN("with tuple", std::string name;)
    IN(PROTECT(std::tie(std::ignore, name, std::ignore) = std::make_tuple(51, "Liam Smith", "QC");))
    IN(print_safe("\tname: %s\n", name.c_str());)
    print_safe("\n");
    DESC_IN("with pair", PROTECT(const char* yes, *no;))
    IN(PROTECT(std::tie(yes, no) = std::make_pair("yes", "no");))
    IN(print_safe("\tchoices: %s, %s\n", yes, no);)
  )
)

