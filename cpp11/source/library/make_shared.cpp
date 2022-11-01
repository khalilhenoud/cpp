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

#include <iostream>
#include <memory>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#stdmake_shared")

TEST(
  make_shared,
  "std::make_shared is the recommended way to create instances of\n" 
  "std::shared_ptrs due to the following reasons:\n"
  "    - Avoid having to use the 'new' operator.\n"
  "    - Prevents code repetition when specifying the underlying type the\n" 
  "      pointer shall hold.\n"
  "    - It provides exception-safety. Suppose we were calling a function foo\n" 
  "      like so:\n"
  "foo(std::shared_ptr<T>{new T{}}, function_that_throws(), std::shared_ptr<T>{new T{}});\n"
  "      The compiler is free to call new T{}, then function_that_throws(), and\n" 
  "      so on... Since we have allocated data on the heap in the first\n" 
  "      construction of a T, we have introduced a leak here. With\n" 
  "      std::make_shared, we are given exception-safety:\n"
  "foo(std::make_shared<T>(), function_that_throws(), std::make_shared<T>());\n"
  "    - Prevents having to do two allocations. When calling\n" 
  "      std::shared_ptr{ new T{} }, we have to allocate memory for T, then in\n" 
  "      the shared pointer we have to allocate memory for the control block\n" 
  "      within the pointer.",
  SECTION(
    "example",
    IN(std::shared_ptr<named<true>> peter = std::make_shared<named<true>>("peter", false);)
    IN(peter->print_data();)
  )
)