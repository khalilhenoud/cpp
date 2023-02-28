/**
 * @file char32_t_and_char16_t.cpp
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


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#char32_t-and-char16_t
)--"
  )

TEST(
  char32_and_char16,
R"--(
Provides standard types for representing UTF-8 strings.
)--",
  SECTION(
    "basic example",
    IN(char32_t utf8_str32[] = U"\u0123";)
    IN(print_safe("\t%u\n", utf8_str32);)
    IN(char16_t utf8_str16[] = u"\u0123";)
    IN(print_safe("\t%u\n", utf8_str16);)
  )
)

