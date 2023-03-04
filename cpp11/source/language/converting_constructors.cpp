/**
 * @file converting_constructors.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <initializer_list>
#include <cassert>


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#converting-constructors
https://stackoverflow.com/questions/15077466/what-is-a-converting-constructor-in-c-what-is-it-for
)--"
)

namespace {
struct A {
  A(int32_t _i, int32_t _j, int32_t _k)
    : i(_i), j(_j), k(_k)
  {
    ANNOUNCE(true);
  }

  int32_t i = 0, j = 0, k = 0;
};
}

namespace {
struct B {
  B(int32_t _i, int32_t _j, int32_t _k)
  {
    i[0] = _i;
    i[1] = _j;
    i[2] = _k;
    ANNOUNCE(true);
  }

  B(std::initializer_list<int32_t> data)
  {
    ANNOUNCE(true);
    assert(data.size() == 3);
    int32_t index = 0;
    for (auto item : data)
      i[index++] = item;
  }

  int32_t i[3] = { 0 };
};
}

#pragma warning(push)
#pragma warning(disable:4244)

TEST(
  converting_constructors,
R"--(
Converting constructors will convert values of braced list syntax into 
constructor arguments. Note that the braced list syntax does not allow 
narrowing.
)--",
  SECTION(
    "basic example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(A a{1, 2, 3};))
    IN_DESC(PROTECT(A b(2.f, 3.f, 4.f);), "warning C4244: 'argument': conversion from 'float' to 'int32_t', possible loss of data")
    IN_ERROR(PROTECT(A c{1.f, 2, 4};), "error C2398: Element '1': conversion from 'float' to 'int32_t' requires a narrowing conversion")
  )
  SECTION(
R"--(
Note that if a constructor accepts a std::initializer_list, it will be called 
instead.
)--",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(PROTECT(B b(1, 2, 3);))
    IN(PROTECT(B c{1, 2, 3};))
    IN_ERROR(PROTECT(B d{1, 2.f, 3};), "error C2398: Element '2': conversion from 'float' to 'int32_t' requires a narrowing conversion")
  )
)

#pragma warning(pop)