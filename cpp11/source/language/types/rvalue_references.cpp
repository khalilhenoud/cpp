/**
 * @file rvalue_references.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"
#include "utilities\classes\named.h"
#include "utilities\classes\printer.h"


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#rvalue-references")

TEST(
  binds_only_to_rvalues,
R"--(
rvalue references binds strictly to rvalues, xvalues are considered rvalues.
xvalues are the result of std::move(lvalues) and can be used as the rhs of an
assignment operation to an rvalue reference. Binding a strictly lvalue to a
rvalue reference will throw a compiler error.
)--",
  SECTION(
    "simple types",
    IN(int i = 5;)
    IN(int& lref_i = i;)
    IN(int&& rref_any = 2;)
    IN_ERROR(int&& rref_i = i;, "compile error, cannot bind to lvalue.")
    IN(int&& rref_i = std::move(i);)
    IN(print_safe("%i\n", rref_i);)
    IN(rref_i *= 11;)
    IN(print_safe("%i\n", i);)
  )
  SECTION(
    "forwarding references in non templates",
    IN(int i = 6;)
    IN(auto&& universal_rref = 30;)
    IN(print_safe("%i\n", universal_rref);)
    IN(auto&& universal_lref = i;)
    IN(print_safe("%i\n", universal_lref);)
    IN(universal_lref *= 10;)
    IN(print_safe("%i\n", i);)
  )
  SECTION(
    "function type resolution",
    IN(int i = 1;)
    IN(const int ci = 2;)
    IN(printer::print(i);)
    IN(printer::print(ci);)
    IN(printer::print(2);)
    IN(printer::print(std::move(i));)
    IN_DESC(int&& x = 1;, "named rvalue references are lvalues.")
    IN(printer::print(x);)
    IN(printer::print(std::move(x));)
  )
  SECTION(
R"--(
rvalue reference cannot bind to non-temporaries, either pure rvalues or xvalues
(result of std::move on lvalues)!! test with classes.
)--",
    IN(named<true> joe;)
    IN(named<true> mike;)
    IN(auto&& named_rref = std::move(mike);)
    IN(joe = named_rref;)
    IN(named<true> jarrod(named_rref);)
    IN(joe = std::move(mike);)
    IN(named<true> john(std::move(mike));)
  )
)

