/**
 * @file non_static_data_member_initializers.cpp
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


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#non-static-data-member-initializers")

//<<
namespace {
namespace cpp03 {
struct human {
  human(int32_t age = 5)
    : m_age(age)
  {}

  int32_t m_age;
};
}

// Note how the constructor becomes redundant.
namespace cpp11 {
struct human {
  int32_t m_age = 15;
};
}
}
//>>

TEST(
  non_static_data_member_initializers,
  "Allows non-static data members to be initialized where they are declared,\n" 
  "potentially cleaning up constructors of default initializations.\n",
  SECTION(
    "basic example",
    std::cout << GIVEN[0] << std::endl;
    IN(cpp03::human baby;)
    IN(std::cout << '\t' << baby.m_age << std::endl;)
    IN(cpp11::human teenager;)
    IN(std::cout << '\t' << teenager.m_age << std::endl;)
  )
)

