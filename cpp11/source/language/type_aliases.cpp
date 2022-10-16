/**
 * @file type_aliases.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <iterator>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#type-aliases")

namespace {
template<typename T>
using myvec = std::vector<T>;

template<typename T>
using mylist = std::list<T>;

using mystring = std::string;

template<typename... T>
using mytuple = std::tuple<T...>;
}

TEST(
  type_aliases,
  "Semantically similar to using a typedef however, type aliases with using are\n" 
  "easier to read and are compatible with templates.",
  SECTION(
    "basics",
    std::cout << GIVEN[0] << std::endl;
    IN_ERROR(template<class T> using myvec = std::vector<T>;, "error C2951: template declarations are only permitted at global, namespace, or class scope.")
    IN_DESC(using myu32vec = std::vector<uint32_t>;, "this is fine though.");
    IN(PROTECT(myu32vec uvec = {1, 2, 3};))
    IN(std::cout << '\t' << uvec[0] << std::ends << uvec[1] << std::ends << uvec[2] << std::endl;)
    IN(PROTECT(myvec<int32_t> vec = { 15, 25, 38 };))
    IN(std::cout << '\t' << vec[0] << std::ends << vec[1] << std::ends << vec[2] << std::endl;)
    IN(PROTECT(mylist<int32_t> list = { 111, 222, 333 };))
    IN(std::cout << '\t' << *std::next(list.begin(), 0) << std::ends << *std::next(list.begin(), 1) << std::ends << *std::next(list.begin(), 2) << std::endl;)
    IN(mystring str = "example";)
    IN(std::cout << '\t' << str << std::endl;)
    std::cout << std::endl;
    IN(PROTECT(mytuple<int, float, double> mt = std::make_tuple(1, 0.5f, 0.9221223);))
    IN(std::cout << '\t' << std::get<0>(mt) << std::endl;)
    IN(std::cout << '\t' << std::get<1>(mt) << std::endl;)
    IN(std::cout << '\t' << std::get<2>(mt) << std::endl;)
  )
)

