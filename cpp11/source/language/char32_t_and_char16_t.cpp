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

#include <iostream>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#char32_t-and-char16_t\n")

TEST(
  char32_and_char16,
  "Provides standard types for representing UTF-8 strings.",
  SECTION(
    "basic example",
    IN(char32_t utf8_str32[] = U"\u0123";)
    IN(std::cout << '\t' << utf8_str32 << std::endl;)
    IN(char16_t utf8_str16[] = u"\u0123";)
    IN(std::cout << '\t' << utf8_str16 << std::endl;)
  )
)

