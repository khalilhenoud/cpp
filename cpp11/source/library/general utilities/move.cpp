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
#include "utilities\classes\named.h"
#include "utilities\classes\carray.h"

#include <type_traits>
#include <memory>


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#stdmove
https://stackoverflow.com/questions/7027523/what-can-i-do-with-a-moved-from-object
)--"
)

namespace {
namespace non_std {
template<typename T>
typename std::remove_reference<T>::type&& move(T&& arg)
{
  return static_cast<typename std::remove_reference<T>::type&&>(arg);
}
}
}

TEST(
  std_move,
R"--(
'std::move' indicates that the object passed to it may have its resources 
transferred. Using objects that have been moved from should be used with care,
as they can be left in an unspecified state (see: reference [2]?).
)--",
  SECTION(
    "Performing a move is nothing more than casting to an rvalue reference",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(named<true> jake("jake", false);)
    IN(named<true> kira("kira", false);)
    IN(kira = non_std::move(jake);)
    IN(kira.print_data();)
  )
  SECTION(
    "'named' example but using standard move.",
    IN(named<true> nomad("nomad", false);)
    IN(named<true> stephan("stephan", false);)
    IN_DESC(stephan = std::move(nomad);, "using standard move in this case")
    IN(stephan.print_data();)
  )
  SECTION(
    "Using non std move with carray class:",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(carray<uint32_t, true> oneto5(5, 1);))
    IN(oneto5.print_data();)
    IN(PROTECT(carray<uint32_t, true> sixto10(5, 6);))
    IN(sixto10.print_data();)
    IN(sixto10 = non_std::move(oneto5);)
    IN(sixto10.print_data();)
  )
  SECTION(
    "'carray' example but with standard move",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(carray<uint32_t, true> oneto5(5, 1);))
    IN(oneto5.print_data();)
    IN(PROTECT(carray<uint32_t, true> sixto10(5, 6);))
    IN(sixto10.print_data();)
    IN_DESC(sixto10 = std::move(oneto5);, "using standard move in this case")
    IN(sixto10.print_data();)
  )
  SECTION(
    "Transferring std::unique_ptr's using non standard move",
    print_safe("%s\n", GIVEN[0].c_str());
    IN_DESC(std::unique_ptr<int32_t> p1{new int32_t{1}};, "cpp14 introduces make_unique, use that instead")
    IN_ERROR(std::unique_ptr<int32_t> p2 = p1;, "error C2280: '...': attempting to reference a deleted function")
    IN(std::unique_ptr<int32_t> p3 = non_std::move(p1);)
    IN(print_safe("\t%i\n", *p3);)
  )
  SECTION(
    "'unique_ptr' example but with standard move",
    IN_DESC(std::unique_ptr<int32_t> p1{new int32_t{5}};, "cpp14 introduces make_unique, use that instead")
    IN_ERROR(std::unique_ptr<int32_t> p2 = p1;, "error C2280: '...': attempting to reference a deleted function")
    IN(std::unique_ptr<int32_t> p3 = std::move(p1);)
    IN(print_safe("\t%i\n", *p3);)
  )
)