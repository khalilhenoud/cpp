/**
 * @file registrar.h
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "utilities\utils.h"

#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <cassert>
#include <utility>


using section_map = std::pair<std::vector<std::string>, std::unordered_map<std::string, std::function<void()>>>;
using test_function = section_map(*)(const char*, std::string section);
using feature_tests = std::unordered_map<std::string, test_function>;

struct registrar {
  static const std::string library;
  static const std::string language;

  static std::unordered_map<std::string, feature_tests> s_tests;
  static std::unordered_map<std::string, feature_tests> s_library_tests;
  
  registrar(
    const std::string& directory,
    const std::string& feature, 
    test_function func, 
    const std::string& test_name);

  static void 
  run_all_tests();

  static std::vector<std::string> 
  get_tests(
    const std::string& feature, 
    bool language = true);

  static std::vector<std::string> 
  get_test_sections(
    const std::string& feature, 
    const std::string& test,
    bool language = true);

  static void 
  run_test(
    const std::string& feature, 
    const std::string& test, 
    const std::string& section,
    bool language = true);
};

inline void add_unique(std::vector<std::string>& sections, std::string section)
{
  if (std::find(sections.begin(), sections.end(), section) == sections.end())
      sections.push_back(section);
}

#define SECTION(sectionname, code) \
{ \
  add_unique(sections.first, sectionname); \
  sections.second[sectionname] = [=](){ \
    code \
  }; \
}

#define RESERVED_NAME "_?!reserved"
#define RESERVED_SECTION SECTION(RESERVED_NAME, {;})

inline
std::string 
trim_surrounding_spaces(const char* str)
{
  assert(str != nullptr);
  std::string toprocess = str;
  while (std::isspace(toprocess.front()))
    toprocess.erase(0, 1);

  while (std::isspace(*toprocess.rbegin()))
    toprocess.erase(std::next(toprocess.rbegin()).base());

  return toprocess;
}

#define TEST(testname, description, ...)  \
static section_map testname(const char* name, std::string section) \
{ \
  static section_map sections; \
  if (name != nullptr && section.length() == 0) \
  { \
    std::cout << std::endl; \
    std::cout << std::string(80, '=') << std::endl; \
    std::string title = name; \
    std::replace(std::begin(title), std::end(title), '_', ' '); \
    std::cout << title << ":" << std::endl;  \
    std::cout << std::string(strlen(name) + 1, '-') << std::endl; \
    std::cout << trim_surrounding_spaces(description) << std::endl; \
    std::cout << std::endl; \
  } \
  __VA_ARGS__ \
  assert(sections.second.size() != 0 && "Please wrap your code in a section!!!"); \
  if (name != nullptr && section != RESERVED_NAME && sections.second.find(section) != sections.second.end()) \
  { \
    std::string trimmed_section = trim_surrounding_spaces(section.c_str()); \
    std::cout << trimmed_section << std::endl; \
    auto length = trimmed_section.find_first_of('\n', 0); \
    length = length == std::string::npos ? trimmed_section.length() : length; \
    std::cout << std::string(length, '-') << std::endl; \
    sections.second[section]();  \
    std::cout << std::endl; \
  } \
  return sections; \
} \
static registrar test##testname(get_directory_name(__FILE__), get_short_name(__FILE__), testname, #testname);

#define REFERENCES(description) TEST(references, description, RESERVED_SECTION)
#define QUESTIONS(description) TEST(questions, description, RESERVED_SECTION)
#define NOTES(description) TEST(notes, description, RESERVED_SECTION)
#define EXERCISES(description) TEST(exercises, description, RESERVED_SECTION)
#define TODO(description) TEST(todos, description, RESERVED_SECTION)