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
#include "utilities\shared.h"
#include "utilities\registrar.h"
#include "utilities\classes\named.h"
#include "utilities\classes\carray.h"

#include <string>
#include <vector>


REFERENCES("https://stackoverflow.com/questions/7510182/how-does-stdmove-transfer-values-into-rvalues")

QUESTIONS(
R"--(
Why should the move constructor and move assignment operator be declared 
noexcept?
https://stackoverflow.com/questions/18085383/c11-rvalue-reference-calling-copy-constructor-too
)--"
)

TEST(
  move_semantics,
R"--(
Given a class with r/lvalue semantics, test which functions is called depending
on the value category of the parameter, i.e: xvalue, prvalue, lvalue. Create a
class with r/lvalue semantics, who's functions echo to stdout when called (for
identification). Test which function is called depending on the value category
of the parameter, i.e: xvalue, prvalue, lvalues.
)--",
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
R"--(
Performance testing. Use move semantics with stl containers, and time the 
result. Use move semantics with a user supplied custom class and see the result.
)--",
  SECTION("copy vs move with std::vector",
    IN_TIMED(std::vector<int> elems(1000000);)
    IN_TIMED(auto copyop = elems;)
    IN(print_safe("%llu\n", elems.size());)
    IN(print_safe("%llu\n", copyop.size());)
    IN_TIMED(auto moveop = std::move(elems);)
    IN(print_safe("%llu\n", elems.size());)
    IN(print_safe("%llu\n", moveop.size());)
  )
  SECTION("copy vs move with custom array class",
    // carray<int, true> vec0(100000000, 2);
    // SEE https://stackoverflow.com/questions/13842468/comma-in-c-c-macro
    using arrayint = carray<int>;
    IN_TIMED(arrayint vec0(100000000, 2);)
    IN_TIMED(arrayint vec1 = vec0;)
    IN_TIMED(arrayint vec2 = std::move(vec0);)
    IN(print_safe("%llu\n", vec0.size());)
    IN(print_safe("%llu\n", vec1.size());)
    IN(print_safe("%llu\n", vec2.size());)
  )
)

