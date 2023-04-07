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


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#non-static-data-member-initializers")

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

TEST(
  non_static_data_member_initializers,
R"--(
Allows non-static data members to be initialized where they are declared,
potentially cleaning up constructors of default initializations.
)--",
  SECTION(
    "basic example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(cpp03::human baby;)
    IN(print_safe("\t%i\n", baby.m_age);)
    IN(cpp11::human teenager;)
    IN(print_safe("\t%i\n", teenager.m_age);)
  )
)

