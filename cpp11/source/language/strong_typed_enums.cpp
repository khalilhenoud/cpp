/**
 * @file strong_typed_enums.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#strongly-typed-enums
https://stackoverflow.com/questions/12581064/enum-vs-strongly-typed-enum
)--"
)

namespace {
// Specifying underlying type as `unsigned int`
enum class Color : unsigned int { Red = 0xff0000, Green = 0x00ff00, Blue = 0x0000ff };
// `Red`/`Green` in `Alert` don't conflict with `Color`
enum class Alert : bool { Red, Green };
}

TEST(
  strong_typed_enums,
R"--(
Type-safe enums that solve a variety of problems with C-style enums including:
implicit conversions, inability to specify the underlying type, scope pollution.
)--",
  SECTION(
    "examples",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(Color c = Color::Red;)
    IN(Alert red = Alert::Red;)
    IN_ERROR(bool b = red;, "error C2440: 'initializing': cannot convert from 'Alert' to 'bool', even if the underlaying type is the same!")
    IN_DESC(bool b = (bool)red;, "explicit casts are needed in this case!")
    IN(print_safe("\t%i\n", b);)
    print_safe("\n");
    IN_ERROR(print_safe("\t%i\n", (Alert::Red != Color::Red));, "error C2676: binary '!=': 'Alert' does not define this operator or a conversion to a type acceptable to the predefined operator")
    IN(print_safe("\t%llu\n", sizeof(c));)
    IN(print_safe("\t%u\n", uint32_t(c));)
    IN(print_safe("\t%llu\n", sizeof(red));)
    IN(print_safe("\t%u\n", uint32_t(red));)
  )
)

