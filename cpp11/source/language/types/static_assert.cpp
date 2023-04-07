/**
 * @file static_assert.cpp
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


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#static-assertions
https://en.cppreference.com/w/cpp/language/static_assert
)--"
)

namespace {
template<class...Args>
struct arity {
  constexpr static int value = sizeof...(Args);
};
}

namespace {
template<class T>
void swap(T& a, T& b)
{
  static_assert(
    std::is_copy_constructible<T>::value,
    "Requires copying.");
  static_assert(
    std::is_nothrow_copy_constructible<T>::value && 
    std::is_nothrow_copy_assignable<T>::value,
    "Requires no throw copy/assign.");

  auto c = b;
  b = a;
  a = c;
}

template<class T>
struct data_structure {
  static_assert(std::is_default_constructible<T>::value, "Requires default construtibility.");
  T data;
};

struct no_default {
  no_default() = delete;
};

struct copyable {
  copyable() = default;
  copyable(const copyable& b) noexcept = default;
  copyable& operator=(const copyable& b) noexcept = default;
  int32_t i = -1;
};
}

TEST(
  static_assertions,
  "Assertions that are evaluated at compile-time.",
  SECTION(
    "Basic example.",
    IN(constexpr int x = 0;)
    IN(constexpr int y = 1;)
    IN_ERROR(static_assert(x == y, "x != y");, "error C2338: static_assert failed: 'x != y'")
  )
  SECTION(
    "Usage with a simple variadic template.",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(static_assert(arity<float, bool, char>::value == 3, "correct");)
    IN(static_assert(arity<float, float>::value == 2, "correct");)
    IN(static_assert(arity<>::value == 0, "correct");)
    IN_ERROR(static_assert(arity<float>::value == 5, "compile time error!");, "error C2338: static_assert failed: 'compile time error!'")
  )
  SECTION(
    "A more advanced example.",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(data_structure<copyable> data_b1;)
    IN(data_b1.data.i = 1;)
    IN(data_structure<copyable> data_b2;)
    IN(data_b2.data.i = 2;)
    IN(print_safe("data_b1.data.i = %i\n", data_b1.data.i);)
    IN(print_safe("data_b2.data.i = %i\n", data_b2.data.i);)
    IN(swap(data_b1, data_b2);)
    IN(print_safe("data_b1.data.i = %i\n", data_b1.data.i);)
    IN(print_safe("data_b2.data.i = %i\n", data_b2.data.i);)
    IN_ERROR(data_structure<no_default> data_a;, "error C2280: 'data_structure<no_default>::data_structure(void)': attempting to reference a deleted function")
  )
)

