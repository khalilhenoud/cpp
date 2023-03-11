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

#include <regex>


REFERENCES(
R"--(
https://en.wikipedia.org/wiki/C%2B%2B11#Regular_expressions
https://en.cppreference.com/w/cpp/regex
https://regexr.com/
)--"
)

TEST(
  regular_expressions,
R"--(
The new library, defined in the new header <regex>, is made of a couple of new
classes:
  - regular expressions are represented by instance of the template class
    std::regex.
  - occurrences are represented by instance of the template class
    std::match_results.
The function std::regex_search is used for searching, while for 'search and
replace' the function std::regex_replace is used which returns a new string.

The algorithms std::regex_search and std::regex_replace take a regular
expression and a string and write the occurrences found in the struct
std::match_results.
)--",
  SECTION(
    "std::match_results example",
    IN(PROTECT(const char *reg_esp = "test";))
    IN(std::regex rgx(reg_esp);)
    IN(std::cmatch match;)
    IN(PROTECT(
      if (std::regex_search("this is a test", match, rgx))
        print_safe("\tFound '%s' at position %llu\n", match[0].str().c_str(), match.prefix().length());
    ))
  )
)