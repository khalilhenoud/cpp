/**
 * @file tuple.cpp
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

#include <iostream>
#include <tuple>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#tuples")

TEST(
  tuples,
  "Tuples are a fixed-size collection of heterogeneous values. Access the\n" 
  "elements of a std::tuple by unpacking using std::tie, or using std::get.",
  SECTION(
    "example",
    IN(PROTECT(std::tuple<int32_t, const char*, const char*> playerProfile = std::make_tuple(51, "Tom Henderson", "NYC");))
    IN(std::cout << '\t' << "age: " << std::get<0>(playerProfile) << std::endl;)
    IN(std::cout << '\t' << "name: " << std::get<1>(playerProfile) << std::endl;)
    IN(std::cout << '\t' << "location: " << std::get<2>(playerProfile) << std::endl;)
  )
)

