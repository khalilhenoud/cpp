/**
 * @file regex.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <regex>


REFERENCES(
  "https://en.wikipedia.org/wiki/C%2B%2B11#Regular_expressions\n"
  "https://en.cppreference.com/w/cpp/regex\n"
  "https://regexr.com/")

TEST(
  regular_expressions,
  "The new library, defined in the new header <regex>, is made of a couple of\n" 
  "new classes:\n"
  " - regular expressions are represented by instance of the template class\n" 
  "   std::regex.\n"
  " - occurrences are represented by instance of the template class\n" 
  "   std::match_results.\n"
  "The function std::regex_search is used for searching, while for 'search and\n" 
  "replace' the function std::regex_replace is used which returns a new string.\n" 
  "The algorithms std::regex_search and std::regex_replace take a regular\n" 
  "expression and a string and write the occurrences found in the struct\n" 
  "std::match_results.",
  SECTION(
    "std::match_results example",
    IN(PROTECT(const char *reg_esp = "test";))
    IN(std::regex rgx(reg_esp);)
    IN(std::cmatch match;)
    IN(PROTECT(
      if (std::regex_search("this is a test", match, rgx))
        std::cout << "\tFound '" << match[0] << "' at position " << match.prefix().length() << std::endl;
    ))
  )
)