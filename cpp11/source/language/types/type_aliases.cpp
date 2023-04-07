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
R"--(
Semantically similar to using a typedef however, type aliases with using are
easier to read and are compatible with templates.
)--",
  SECTION(
    "basics",
    print_safe("%s\n", GIVEN[0].c_str());
    IN_ERROR(template<class T> using myvec = std::vector<T>;, "error C2951: template declarations are only permitted at global, namespace, or class scope.")
    IN_DESC(using myu32vec = std::vector<uint32_t>;, "this is fine though.");
    IN(PROTECT(myu32vec uvec = {1, 2, 3};))
    IN(print_safe("\t%u %u %u\n", uvec[0], uvec[1], uvec[2]);)
    IN(PROTECT(myvec<int32_t> vec = { 15, 25, 38 };))
    IN(print_safe("\t%i %i %i\n", vec[0], vec[1], vec[2]);)
    IN(PROTECT(mylist<int32_t> list = { 111, 222, 333 };))
    IN(print_safe("\t%i %i %i\n", *std::next(list.begin(), 0), *std::next(list.begin(), 1), *std::next(list.begin(), 2));)
    IN(mystring str = "example";)
    IN(print_safe("\t%s\n", str.c_str());)
    print_safe("\n");
    IN(PROTECT(mytuple<int, float, double> mt = std::make_tuple(1, 0.5f, 0.9221223);))
    IN(print_safe("\t%i\n", std::get<0>(mt));)
    IN(print_safe("\t%f\n", std::get<1>(mt));)
    IN(print_safe("\t%f\n", std::get<2>(mt));)
  )
)

