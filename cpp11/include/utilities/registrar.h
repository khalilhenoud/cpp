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
#include <set>
#include <iostream>
#include <functional>
#include <cassert>
#include <utility>


using test_section = std::unordered_map<std::string, std::function<void()>>;
using test_sections_map = std::pair<std::vector<std::string>, test_section>;
using test_function = test_sections_map(*)(const char*, std::string section);
using feature_tests_map = std::unordered_map<std::string, test_function>;

struct hierarchy_entry {
  std::string current;
  std::set<std::string> children;
};

using hierarchy_tree = std::unordered_map<std::string, hierarchy_entry>;

struct registrar {
  static std::unordered_map<std::string, feature_tests_map> s_tests;
  static hierarchy_tree directory_tree;
  static constexpr const char* source = "source";
  
  registrar(
    std::vector<std::string> directory_path,
    const std::string& feature, 
    test_function func, 
    const std::string& test_name);

  static bool
  is_file(const std::string& entry_key);

  static void
  update_directory_tree(const std::vector<std::string>& directory_path);

  static std::string
  get_key(const std::vector<std::string>& directory_path, int32_t to_index = -1);

  static std::vector<std::string> 
  get_tests(const std::string& feature);

  static std::vector<std::string> 
  get_test_sections(
    const std::string& feature, 
    const std::string& test);

  static void
  print_test_description(
      const std::string& feature_key,
      const std::string& test);

  static void 
  run_test(
    const std::string& feature_key, 
    const std::string& test, 
    const std::string& section,
    bool with_description = false);
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
static test_sections_map testname(const char* name, std::string section) \
{ \
  static test_sections_map sections; \
  if (name != nullptr && section.length() == 0) \
  { \
    std::string title = name; \
    std::replace(std::begin(title), std::end(title), '_', ' '); \
    std::cout << title << ":" << std::endl;  \
    std::cout << std::string(strlen(name) + 1, '-') << std::endl; \
    std::cout << trim_surrounding_spaces(description) << std::endl; \
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
  } \
  return sections; \
} \
static registrar test##testname(get_directory_hierarchy(__FILE__, registrar::source), get_short_name(__FILE__), testname, #testname);

#define REFERENCES(description) TEST(references, description, RESERVED_SECTION)
#define QUESTIONS(description) TEST(questions, description, RESERVED_SECTION)
#define NOTES(description) TEST(notes, description, RESERVED_SECTION)
#define EXERCISES(description) TEST(exercises, description, RESERVED_SECTION)
#define TODO(description) TEST(todos, description, RESERVED_SECTION)