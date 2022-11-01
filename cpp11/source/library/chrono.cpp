/**
 * @file chrono.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <chrono>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#stdchrono")

namespace {
void waste_cycles()
{
  for (int32_t i = 0; i < 10000000; ++i);
}
}

TEST(
  chrono,
  "The chrono library contains a set of utility functions and types that deal\n" 
  "with durations, clocks, and time points. One use case of this library is\n" 
  "benchmarking code:",
  SECTION(
    "example",
    std::cout << GIVEN[0] << std::endl;
    IN(PROTECT(std::chrono::time_point<std::chrono::steady_clock> start, end;))
    IN(start = std::chrono::steady_clock::now();)
    IN(waste_cycles();)
    IN(end = std::chrono::steady_clock::now();)
    IN(std::chrono::duration<double> elapsed_seconds = end - start;)
    IN(std::cout << "\telapsed seconds: " << elapsed_seconds.count() << std::endl;)
  )
)