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
    std::cout << description; \
    std::cout << std::endl << std::endl; \
  } \
  __VA_ARGS__ \
  assert(sections.second.size() != 0 && "Please wrap your code in a section!!!"); \
  if (name != nullptr && sections.second.find(section) != sections.second.end()) \
  { \
    std::cout << section << std::endl; \
    auto length = section.find_first_of('\n', 0); \
    length = length == std::string::npos ? section.length() : length; \
    std::cout << std::string(length, '-') << std::endl; \
    sections.second[section]();  \
    std::cout << std::endl; \
  } \
  return sections; \
} \
static registrar test##testname(get_directory_name(__FILE__), get_short_name(__FILE__), testname, #testname);

#define REFERENCES(description) TEST(references, description, ;)
#define QUESTIONS(description) TEST(questions, description, ;)
#define EXERCISES(description) TEST(exercises, description, ;)
#define TODO(description) TEST(todos, description, ;)