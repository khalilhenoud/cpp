/**
 * @file raw_string_literals.cpp
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


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#raw-string-literals")

TEST(
  raw_string_literals,
R"--(
C++11 introduces a new way to declare string literals as "raw string literals".
Characters issued from an escape sequence (tabs, line feeds, single backslashes,
etc.) can be inputted raw while preserving formatting. This is useful, for 
example, to write literary text, which might contain a lot of quotes or special
formatting. This can make your string literals easier to read and maintain.

A raw string literal is declared using the following syntax:
  R"delimiter(raw_characters)delimiter"
where:
  - 'delimiter' is an optional sequence of characters made of any source
    character except parentheses, backslashes and spaces.
  - 'raw_characters' is any raw character sequence; must not contain the closing
    sequence ")delimiter".
)--",
  SECTION(
    "example:",
    IN(const char* msg1 = "\nHello,\n\tworld!\n";)
    IN(const char* msg2 = R"(
Hello,
        world!
    )";)
    IN(print_safe("%s\n", msg1);)
    IN(print_safe("%s\n", msg2);)
  )
)

