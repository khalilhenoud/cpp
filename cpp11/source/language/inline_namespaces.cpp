/**
 * @file inline_namespaces.cpp
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

#include <iostream>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#inline-namespaces\n"
  "https://en.cppreference.com/w/cpp/language/namespace")

namespace {
namespace Program {
namespace Version1 {
int getVersion() { return 1; }
bool isFirstVersion() { return true; }
}
inline namespace Version2 {
int getVersion() { return 2; }
}
inline namespace Info {
const char* getInfo() { return "inline namespaces!!"; }
}
}
}

TEST(
  inline_namespaces,
  "All members of an inline namespace are treated as if they were part of its\n" 
  "parent namespace, allowing specialization of functions and easing the\n" 
  "process of versioning. This is a transitive property, if A contains B,\n" 
  "which in turn contains C and both B and C are inline namespaces, C's members\n" 
  "can be used as if they were on A.",
  SECTION(
    "basic examples",
    std::cout << GIVEN[0] << std::endl;
    IN(using namespace Program;)
    IN(std::cout << getVersion() << std::endl;)
    IN(std::cout << getInfo() << std::endl;)
  )
)

