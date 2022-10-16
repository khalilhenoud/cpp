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

#include <iostream>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#raw-string-literals")

TEST(
  raw_string_literals,
  "C++11 introduces a new way to declare string literals as \"raw string literals\".\n" 
  "Characters issued from an escape sequence (tabs, line feeds, single\n" 
  "backslashes, etc.) can be inputted raw while preserving formatting. This is\n" 
  "useful, for example, to write literary text, which might contain a lot of\n" 
  "quotes or special formatting. This can make your string literals easier\n" 
  "to read and maintain.\n"
  "A raw string literal is declared using the following syntax:\n"
  "\tR\"delimiter(raw_characters)delimiter\"\n"
  "where:\n"
  "- 'delimiter' is an optional sequence of characters made of any source\n" 
  "character except parentheses, backslashes and spaces.\n"
  "- 'raw_characters' is any raw character sequence; must not contain the\n" 
  "closing sequence \")delimiter\".",
  SECTION(
    "example:",
    IN(const char* msg1 = "\nHello,\n\tworld!\n";)
    IN(const char* msg2 = R"(
Hello,
        world!
    )";)
    IN(std::cout << msg1 << std::endl;)
    IN(std::cout << msg2 << std::endl;)
  )
)

