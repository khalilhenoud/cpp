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


REFERENCES(
R"--(
https://en.wikipedia.org/wiki/C%2B%2B11#Control_and_query_object_alignment
https://en.cppreference.com/w/cpp/language/alignas
https://stackoverflow.com/questions/36217004/query-the-alignment-of-a-specific-variable
)--"
)

namespace {
bool is_aligned(const volatile void*p, std::size_t n)
{
  return reinterpret_cast<std::uintptr_t>(p) % n == 0;
}
}

TEST(
  alignas_alignof,
R"--(
C++11 allows variable alignment to be queried and controlled with alignof and  
alignas.
The alignof operator takes the type and returns the power of 2 byte boundary on 
which the type instances must be allocated (as a std::size_t). When given a 
reference type alignof returns the referenced type's alignment; for arrays it 
returns the element type's alignment.
The alignas specifier controls the memory alignment for a variable. The
specifier takes a constant or a type; when supplied a type alignas(T) is
shorthand for alignas(alignof(T)).
)--",
  SECTION(
    "properly align a unsigned char array to hold a double",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(alignas(double) unsigned char c[sizeof(double)];)
    IN(unsigned char d[4];)
    IN(print_safe("\t%llu\n", (uint64_t(&c) % alignof(double)) );)
    IN(print_safe("\t%llu\n", is_aligned(&c, alignof(double)) );)
    DESC_IN(
    "alignof/as cannot be used on variables, just types and constants in the case of alignas", 
    print_safe("\t%llu\n", is_aligned(&d, alignof(double)));)
  )
  SECTION(
    "alignof with basic types, references and arrays",
    IN(print_safe("\t%llu\n", alignof(char));)
    IN(print_safe("\t%llu\n", alignof(unsigned char));)
    IN(print_safe("\t%llu\n", alignof(int32_t));)
    IN(print_safe("\t%llu\n", alignof(uint32_t));)
    IN(print_safe("\t%llu\n", alignof(int64_t));)
    IN(print_safe("\t%llu\n", alignof(uint64_t));)
    IN(print_safe("\t%llu\n", alignof(int16_t));)
    IN(print_safe("\t%llu\n", alignof(uint16_t));)
    IN(print_safe("\t%llu\n", alignof(long long int));)
    IN(print_safe("\t%llu\n", alignof(float));)
    IN(print_safe("\t%llu\n", alignof(double));)
    DESC_IN("reference types devolves to alignof of the underlying types", 
    print_safe("\t%llu\n", alignof(int16_t&));)
    IN(print_safe("\t%llu\n", alignof(double&));)
    IN(print_safe("\t%llu\n", alignof(float&));)
    DESC_IN("array types devolves to alignof of the array element type",
    print_safe("\t%llu\n", alignof(int16_t[]));)
    IN(print_safe("\t%llu\n", alignof(double[]));)
    IN(print_safe("\t%llu\n", alignof(float[]));)
    DESC_IN("pointer types alignment",
    print_safe("\t%llu\n", alignof(int16_t*));)
    IN(print_safe("\t%llu\n", alignof(double*));)
    IN(print_safe("\t%llu\n", alignof(float*));)
  )
)