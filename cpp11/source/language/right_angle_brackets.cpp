/**
 * @file right_angle_brackets.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <map>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#right-angle-brackets\n"
  "http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1757.html")

namespace {
typedef std::map<int, std::map <int, std::map <int, int> > > cpp98LongTypedef;
typedef std::map<int, std::map <int, std::map <int, int>>>   cpp11LongTypedef;
}

TEST(
  right_angle_brackets,
  "C++11 is now able to infer when a series of right angle brackets is used as\n"
  "an operator or as a closing statement of typedef, without having to add\n"
  "whitespace.",
  SECTION(
    "cpp11 vs 03 typedef example",
    std::cout << GIVEN[0] << std::endl;
  )
)

