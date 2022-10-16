/**
 * @file noexcept_specifier.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <stdexcept>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#noexcept-specifier")

namespace {
void func1() noexcept {}        // does not throw
void func2() noexcept(true) {}  // does not throw
void func3() throw() {}         // does not throw
void func4() noexcept(false)    // may throw, and indeed it does.
{
  throw std::runtime_error("Random error!");
}

void func5() noexcept
{
  try
  {
    func4();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}

void func6() noexcept
{
  func4();
}
}

TEST(
  noexcept_specifier,
  "The noexcept specifier specifies whether a function could throw exceptions.\n" 
  "It is an improved version of throw().\n"
  "Non-throwing functions are permitted to call potentially-throwing functions.\n" 
  "Whenever an exception is thrown and the search for a handler encounters the\n" 
  "outermost block of a non-throwing function, the function std::terminate() is\n" 
  "called.",
  SECTION(
    "basic example",
    std::cout << GIVEN[0] << std::endl;
    IN(func5());
    IN_ERROR(func6(), "this will call std::terminate()!");
  )
)

