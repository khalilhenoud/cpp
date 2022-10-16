/**
 * @file move_semantics.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-07-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<iostream>
#include<string>
#include<vector>

#include "utilities\shared.h"
#include "utilities\registrar.h"
#include "utilities\classes\named.h"
#include "utilities\classes\carray.h"


REFERENCES("https://stackoverflow.com/questions/7510182/how-does-stdmove-transfer-values-into-rvalues")

QUESTIONS(
  "Why should the move constructor and move assignment operator be declared\n"
  "noexcept?\n"
  "https://stackoverflow.com/questions/18085383/c11-rvalue-reference-calling-copy-constructor-too")

TEST(
  move_semantics,
  "Given a class with r/lvalue semantics, test which functions is called\n"
  "depending on the value category of the parameter, i.e: xvalue, prvalue,\n"
  "lvalue. Create a class with r/lvalue semantics, who's functions echo to\n"
  "stdout when called (for identification). Test which function is called\n"
  "depending on the value category of the parameter, i.e: xvalue, prvalue,\n"
  "lvalues.",
  SECTION("copy assign operator",
    IN(named<false> alex("alex", false);)
    IN(named<false> mike("mike", false);)
    IN(mike = alex;)
    IN(mike.print_data();)
    IN(alex.print_data();)
  )
  SECTION("move assign operator",
    IN(named<true> mike("mike", false);)
    IN(mike = named<true>("benjamin", false);)
    IN(mike.print_data();)
  )
  SECTION("move internal data swap part1",
    IN(named<false> alex("alex", false);)
    IN(named<false> mike("mike", false);)
    IN(mike = std::move(alex);)
    IN(mike.print_data();)
    IN(alex.print_data();)
  )
  SECTION("move internal data swap part2",
    IN(named<false> joe("joe");)
    IN(named<false> mike("mike");)
    IN(joe.clear_data();)
    IN(joe.print_data();)
    IN(joe = std::move(mike);)
    IN(mike.print_data();)
    IN(joe.print_data();)
  )
  SECTION("named rvalue references are lvalues!",
    IN(named<true> joe("joe", false);)
    IN(named<true> mike("mike", false);)
    IN(auto&& rval = std::move(joe);)
    IN(rval.print_data();)
    IN(mike = rval;)
    IN(rval.clear_data();)
    IN(rval.print_data();)
    IN(joe.print_data();)
  )
)

TEST(
  performance_test,
  "Performance testing. Use move semantics with stl containers, and time the \n"
  "result. Use move semantics with a user supplied custom class and see the\n" 
  "result.",
  SECTION("copy vs move with std::vector",
    IN_TIMED(std::vector<int> elems(1000000);)
    IN_TIMED(auto copyop = elems;)
    IN(std::cout << elems.size() << std::endl;)
    IN(std::cout << copyop.size() << std::endl;)
    IN_TIMED(auto moveop = std::move(elems);)
    IN(std::cout << elems.size() << std::endl;)
    IN(std::cout << moveop.size() << std::endl;)
  )
  SECTION("copy vs move with custom array class",
    // carray<int, true> vec0(100000000, 2);
    // SEE https://stackoverflow.com/questions/13842468/comma-in-c-c-macro
    using arrayint = carray<int>;
    IN_TIMED(arrayint vec0(100000000, 2);)
    IN_TIMED(arrayint vec1 = vec0;)
    IN_TIMED(arrayint vec2 = std::move(vec0);)
    IN(std::cout << vec0.size() << std::endl;)
    IN(std::cout << vec1.size() << std::endl;)
    IN(std::cout << vec2.size() << std::endl;)
  )
)

