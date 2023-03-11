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

#include <random>
#include <functional>


REFERENCES("https://en.cppreference.com/w/cpp/numeric/random")

TEST(
  random,
R"--(
The C standard library provides the ability to generate pseudorandom numbers via
the function rand. However, the algorithm is delegated entirely to the library
vendor. C++ inherited this functionality with no changes, but C++11 provides a
new method for generating pseudorandom numbers.

C++11's random number functionality is split into two parts: a generator engine
that contains the random number generator's state and produces the pseudorandom
numbers; and a distribution, which determines the range and mathematical
distribution of the outcome. These two are combined to form a random number
generator object.

Unlike the C standard rand, the C++11 mechanism will come with three base
generator engine algorithms:
  - linear_congruential_engine
  - subtract_with_carry_engine (lagged Fibonacci)
  - mersenne_twister_engine
C++11 also provides a number of standard distributions:
  - uniform_int_distribution
  - uniform_real_distribution
  - bernoulli_distribution
  - binomial_distribution
  - geometric_distribution
  - negative_binomial_distribution
  - poisson_distribution
  - exponential_distribution
  - gamma_distribution
  - weibull_distribution
  - extreme_value_distribution
  - normal_distribution
  - lognormal_distribution
  - chi_squared_distribution
  - cauchy_distribution
  - fisher_f_distribution
  - student_t_distribution
  - discrete_distribution
  - piecewise_constant_distribution
  - piecewise_linear_distribution
)--",
  SECTION(
    "generators and distributors example",
    IN(PROTECT(std::uniform_int_distribution<int32_t> distribution(0, 99);))
    IN_DESC(std::mt19937 engine;, "Mersenne twister MT19937")
    IN(PROTECT(auto generator = std::bind(distribution, engine);))
    DESC_IN(
    "generate a uniform integral variate between 0 and 99",
    print_safe("\t%i\n", generator());)
    DESC_IN(
    "do the same but without the binding", 
    print_safe("\t%i\n", distribution(engine));)
    IN(print_safe("\t%i\n", generator());)
    IN(print_safe("\t%i\n", generator());)
    IN(print_safe("\t%i\n", generator());)
  )
)