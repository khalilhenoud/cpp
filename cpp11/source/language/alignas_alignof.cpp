/**
 * @file alignas_alignof.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>


REFERENCES(
  "https://en.wikipedia.org/wiki/C%2B%2B11#Control_and_query_object_alignment\n"
  "https://en.cppreference.com/w/cpp/language/alignas\n"
  "https://stackoverflow.com/questions/36217004/query-the-alignment-of-a-specific-variable")

namespace {
bool is_aligned(const volatile void*p, std::size_t n)
{
  return reinterpret_cast<std::uintptr_t>(p) % n == 0;
}
}

TEST(
  alignas_alignof,
  "C++11 allows variable alignment to be queried and controlled with alignof and\n" 
  "alignas.\n"
  "The alignof operator takes the type and returns the power of 2 byte boundary\n" 
  "on which the type instances must be allocated (as a std::size_t). When given\n" 
  "a reference type alignof returns the referenced type's alignment; for arrays\n" 
  "it returns the element type's alignment.\n"
  "The alignas specifier controls the memory alignment for a variable. The\n" 
  "specifier takes a constant or a type; when supplied a type alignas(T) is\n" 
  "shorthand for alignas(alignof(T)).",
  SECTION(
    "properly align a unsigned char array to hold a double",
    std::cout << GIVEN[0] << std::endl;
    IN(alignas(double) unsigned char c[sizeof(double)];)
    IN(unsigned char d[4];)
    IN(std::cout << '\t' << (uint64_t(&c) % alignof(double)) << std::endl;)
    IN(std::cout << '\t' << is_aligned(&c, alignof(double)) << std::endl;)
    DESC_IN("alignof/as cannot be used on variables, just types and constants in the case of alignas", std::cout << '\t' << is_aligned(&d, alignof(double)) << std::endl;)
  )
  SECTION(
    "alignof with basic types, references and arrays",
    IN(std::cout << '\t' << alignof(char) << std::endl;)
    IN(std::cout << '\t' << alignof(unsigned char) << std::endl;)
    IN(std::cout << '\t' << alignof(int32_t) << std::endl;)
    IN(std::cout << '\t' << alignof(uint32_t) << std::endl;)
    IN(std::cout << '\t' << alignof(int64_t) << std::endl;)
    IN(std::cout << '\t' << alignof(uint64_t) << std::endl;)
    IN(std::cout << '\t' << alignof(int16_t) << std::endl;)
    IN(std::cout << '\t' << alignof(uint16_t) << std::endl;)
    IN(std::cout << '\t' << alignof(long long int) << std::endl;)
    IN(std::cout << '\t' << alignof(float) << std::endl;)
    IN(std::cout << '\t' << alignof(double) << std::endl;)
    DESC_IN("reference types devolves to alignof of the underlying types", 
    std::cout << '\t' << alignof(int16_t&) << std::endl;)
    IN(std::cout << '\t' << alignof(double&) << std::endl;)
    IN(std::cout << '\t' << alignof(float&) << std::endl;)
    DESC_IN("array types devolves to alignof of the array element type",
    std::cout << '\t' << alignof(int16_t[]) << std::endl;)
    IN(std::cout << '\t' << alignof(double[]) << std::endl;)
    IN(std::cout << '\t' << alignof(float[]) << std::endl;)
    DESC_IN("pointer types alignment",
    std::cout << '\t' << alignof(int16_t*) << std::endl;)
    IN(std::cout << '\t' << alignof(double*) << std::endl;)
    IN(std::cout << '\t' << alignof(float*) << std::endl;)
  )
)