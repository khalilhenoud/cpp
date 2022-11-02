/**
 * @file random.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <random>
#include <functional>


REFERENCES("https://en.cppreference.com/w/cpp/numeric/random")

TEST(
  random,
  "The C standard library provides the ability to generate pseudorandom numbers\n" 
  "via the function rand. However, the algorithm is delegated entirely to the\n" 
  "library vendor. C++ inherited this functionality with no changes, but C++11\n" 
  "provides a new method for generating pseudorandom numbers.\n"
  "C++11's random number functionality is split into two parts: a generator\n" 
  "engine that contains the random number generator's state and produces the\n" 
  "pseudorandom numbers; and a distribution, which determines the range and\n" 
  "mathematical distribution of the outcome. These two are combined to form a\n" 
  "random number generator object.\n"
  "Unlike the C standard rand, the C++11 mechanism will come with three base\n" 
  "generator engine algorithms:\n"
  " - linear_congruential_engine\n"
  " - subtract_with_carry_engine (lagged Fibonacci)\n"
  " - mersenne_twister_engine\n"
  "C++11 also provides a number of standard distributions:\n"
  " - uniform_int_distribution\n"
  " - uniform_real_distribution\n"
  " - bernoulli_distribution\n"
  " - binomial_distribution\n"
  " - geometric_distribution\n"
  " - negative_binomial_distribution\n"
  " - poisson_distribution\n"
  " - exponential_distribution\n"
  " - gamma_distribution\n"
  " - weibull_distribution\n"
  " - extreme_value_distribution\n"
  " - normal_distribution\n"
  " - lognormal_distribution\n"
  " - chi_squared_distribution\n"
  " - cauchy_distribution\n"
  " - fisher_f_distribution\n"
  " - student_t_distribution\n"
  " - discrete_distribution\n"
  " - piecewise_constant_distribution\n"
  " - piecewise_linear_distribution",
  SECTION(
    "generators and distributors example",
    IN(PROTECT(std::uniform_int_distribution<int32_t> distribution(0, 99);))
    IN_DESC(std::mt19937 engine;, "Mersenne twister MT19937")
    IN(PROTECT(auto generator = std::bind(distribution, engine);))
    DESC_IN("generate a uniform integral variate between 0 and 99", std::cout << '\t' << generator() << std::endl;)
    DESC_IN("do the same but without the binding", std::cout << '\t' << distribution(engine) << std::endl;)
    IN(std::cout << '\t' << generator() << std::endl;)
    IN(std::cout << '\t' << generator() << std::endl;)
    IN(std::cout << '\t' << generator() << std::endl;)
  )
)