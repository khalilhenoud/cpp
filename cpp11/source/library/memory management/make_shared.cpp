/**
 * @file make_shared.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"
#include "utilities\classes\named.h"

#include <memory>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#stdmake_shared")

TEST(
  make_shared,
R"--(
std::make_shared is the recommended way to create instances of std::shared_ptrs
due to the following reasons:
  - Avoid having to use the 'new' operator.
  - Prevents code repetition when specifying the underlying type the pointer 
    shall hold.
  - It provides exception-safety. Suppose we were calling a function foo like 
    so:
      foo(std::shared_ptr<T>{new T{}}, 
          function_that_throws(), 
          std::shared_ptr<T>{new T{}});
    The compiler is free to call new T{}, then function_that_throws(), and so 
    on... Since we have allocated data on the heap in the first construction of 
    a T, we have introduced a leak here. With std::make_shared, we are given 
    exception-safety:
      foo(std::make_shared<T>(), 
          function_that_throws(),
          std::make_shared<T>());
    Prevents having to do two allocations. When calling
    std::shared_ptr{new T{}}, we have to allocate memory for T, then in the
    shared pointer we have to allocate memory for the control block within the
    pointer.
)--",
  SECTION(
    "example",
    IN(std::shared_ptr<named<true>> peter = std::make_shared<named<true>>("peter", false);)
    IN(peter->print_data();)
  )
)