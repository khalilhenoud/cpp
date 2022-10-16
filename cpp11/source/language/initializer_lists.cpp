/**
 * @file initializer_lists.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <type_traits>
#include <numeric>
#include <initializer_list>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#initializer-lists\n"
  "https://en.cppreference.com/w/cpp/utility/initializer_list")

namespace {
template<class T,
  typename std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
T sum(const std::initializer_list<T>& list)
{
  return std::accumulate(list.begin(), list.end(), static_cast<T>(0));
}
}

TEST(
  initializer_list_basics,
  "A lightweight array-like container of elements created using a \"braced list\"\n"
  "syntax. For example, { 1, 2, 3 } creates a sequences of integers, that has \n"
  "type std::initializer_list<int>. Useful as a replacement to passing a vector\n"
  "of objects to a function.",
  SECTION(
    "All entries in the intializer list must be of the same type!",
    std::cout << GIVEN[0] << std::endl;
    IN(PROTECT(auto list = {1, 2, 3};))
    IN(PROTECT(auto listfloats = {1.1f, 1.2f, 1.3f};))
    IN_ERROR(PROTECT(auto listerror = {1.0f, 2.0, 3};), "error C3535: cannot deduce type for 'auto' from 'initializer list'")
    IN(sum(list);)
    IN(sum(listfloats);)
    IN(sum({1, 2, 3});)
    IN_ERROR(sum({});, "error C2783: 'T sum(const std::initializer_list<_Elem> &)': could not deduce template argument for 'T'")
  )
)

