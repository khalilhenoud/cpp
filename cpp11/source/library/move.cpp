/**
 * @file move.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>


REFERENCES(
  "[1] https://github.com/AnthonyCalandra/modern-cpp-features#stdmove\n"
  "[2] https://stackoverflow.com/questions/7027523/what-can-i-do-with-a-moved-from-object")

TEST(
  std_move,
  "std::move indicates that the object passed to it may have its resources\n" 
  "transferred. Using objects that have been moved from should be used with\n" 
  "care, as they can be left in an unspecified state (see: reference [2]?).",
  SECTION(
    "basics",
    std::cout << "move example..." << std::endl;
  )
)