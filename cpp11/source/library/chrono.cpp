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
R"--(
The chrono library contains a set of utility functions and types that deal with
durations, clocks, and time points. One use case of this library is benchmarking
code:
)--",
  SECTION(
    "example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(std::chrono::time_point<std::chrono::steady_clock> start, end;))
    IN(start = std::chrono::steady_clock::now();)
    IN(waste_cycles();)
    IN(end = std::chrono::steady_clock::now();)
    IN(std::chrono::duration<double> elapsed_seconds = end - start;)
    IN(print_safe("\telapsed seconds: %f\n", elapsed_seconds.count());)
  )
)