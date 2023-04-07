/**
 * @file driver.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <algorithm>
#include <array>
#include <unordered_map>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>


void hang_till_newline()
{
  std::cout << std::endl << "...press enter to continue..." << std::ends;
  constexpr uint32_t buffer_size = LINE_WIDTH;
  char buffer[buffer_size] = { 0 };
  fgets(buffer, buffer_size, stdin);
}

uint32_t get_user_input(std::unordered_map<uint32_t, std::string> &index_to_option)
{
  uint32_t result = [&]() -> uint32_t {
    constexpr uint32_t buffer_size = LINE_WIDTH;
    char buffer[buffer_size] = { 0 };
    uint32_t entry = 0;

    uint32_t count = (uint32_t)index_to_option.size();

    bool waiting_for_input = true;
    while (waiting_for_input) {
      waiting_for_input = false;

      std::cout << std::endl;
      std::cout << "enter the option number: " << std::endl;

      while (
        NULL == fgets(buffer, buffer_size, stdin) ||
        1 != sscanf(buffer, "%u", &entry)) {
        if (feof(stdin))
          return 0;
        else {
          memset(buffer, 0, buffer_size);
          waiting_for_input = true;
          break;
        }
      }

      if (waiting_for_input) {
        std::cout << "invalid input!! simply type the number followed by newline." << std::endl;
        continue;
      }

      // quit the program.
      if (entry == 0)
        return 0;

      if (entry > count) {
        waiting_for_input = true;
        std::cout << "no option associated with that number, try again!" << std::endl;
        continue;
      }

      return entry;
    }

    return 0;
  }();

  // print a blank line between the user input and the net print.
  std::cout << std::endl;
  return result;
}

size_t
get_options(
  std::vector<std::string>& path, 
  std::unordered_map<uint32_t, std::string>& index_to_feature)
{
  index_to_feature.clear();
  size_t file_start = 0;
  auto key = registrar::get_key(path);

  {
    uint32_t index = 1;
    for (auto& option : registrar::directory_tree[key].children) {
      auto new_path = path;
      new_path.push_back(option);
      if (!registrar::is_file(registrar::get_key(new_path))) 
        index_to_feature[index++] = option;
    }

    file_start = index_to_feature.size();
    
    for (auto& option : registrar::directory_tree[key].children) {
      auto new_path = path;
      new_path.push_back(option);
      if (registrar::is_file(registrar::get_key(new_path)))
        index_to_feature[index++] = option;
    }
  }


  return file_start;
}

/* references, questions, notes, exercises, todos. */

// return test options for a specific feature.
int32_t
get_feature_tests_options(
  const std::string& feature_key,
  std::unordered_map<uint32_t, std::string>& index_to_tests)
{
  index_to_tests.clear();

  std::array<std::string, 5> reserved = { 
    "references", 
    "questions", 
    "notes", 
    "exercises", 
    "todos" };

  {
    uint32_t index = 1;

    // ensure ordering.
    for (size_t i = 0, count = reserved.size(); i < count; ++i) {
      for (auto& test : registrar::get_tests(feature_key)) {
        if (test == reserved[i])
          index_to_tests[index++] = test;
      }
    }

    // then add the remaining tests.
    for (auto& test : registrar::get_tests(feature_key)) {
      if (std::find(std::begin(reserved), std::end(reserved), test) == reserved.end())
        index_to_tests[index++] = test;
    }
  }

  return 0;
}

// return section options for a specific test within a feature.
int32_t
get_feature_test_sections_options(
  const std::string& feature_key, 
  const std::string& test,
  std::unordered_map<uint32_t, std::string>& index_to_sections)
{
  index_to_sections.clear();

  {
    uint32_t index = 1;
    for (auto& section : registrar::get_test_sections(feature_key, test))
      index_to_sections[index++] = section;
  }

  return 0;
}

void 
clear_screen()
{
  system("cls");
}

int32_t main()
{
  std::unordered_map<uint32_t, std::string> index_to_options;
  std::vector<std::string> path = { registrar::source };
  std::string test = "";
  std::string title = "please select from the following:";
  constexpr uint32_t option_length = 73;
  constexpr const char* suffix = "...";

  std::cout << std::endl;

  while (1) {
    if (path.empty())
      break;

    clear_screen();

    size_t non_dir_start = 0;
    auto key = registrar::get_key(path);
    if (registrar::is_file(key)) {
      if (!test.empty())
        non_dir_start = get_feature_test_sections_options(key, test, index_to_options);
      else
        non_dir_start = get_feature_tests_options(key, index_to_options);
    } else
      non_dir_start = get_options(path, index_to_options);

    // print all the options.
    if (registrar::is_file(key) && !test.empty()) {
      registrar::print_test_description(key, test);
      std::cout << std::endl;
    }

    std::cout << title << std::endl;
    std::cout << std::string(title.length(), '-') << std::endl;
    for (size_t i = 0, count = index_to_options.size(); i < count; ++i) {
      bool dir = i < non_dir_start;
      std::string trimmed = index_to_options[i + 1];
      trimmed = trim_surrounding_spaces(trimmed.c_str());
      std::replace(std::begin(trimmed), std::end(trimmed), '\n', ' ');

      if (trimmed.length() > option_length)
        trimmed = trimmed.substr(0, option_length - strlen(suffix)) + suffix;
      
      std::cout << (dir ? '[' : '<') << (i + 1) << (dir ? ']' : '>') << " " << trimmed << std::endl;
    }
    
    switch (path.size()) {
    case 1:
      std::cout << "[0] quit program" << std::endl;
      break;
    default:
      std::cout << "[0] go back" << std::endl;
      break;
    }

    if (auto entry = get_user_input(index_to_options)) {
      auto& option = index_to_options[entry];

      if (registrar::is_file(key))
      {
        if (!test.empty()) {
          registrar::run_test(key, test, option, false);
          hang_till_newline();
        } else {
          // unless the test has only one section.
          std::unordered_map<uint32_t, std::string> tmp;
          get_feature_test_sections_options(key, option, tmp);
          if (tmp.size() == 1) {
            registrar::run_test(key, option, tmp[1], true);
            hang_till_newline();
          } else
            test = option;
        }
      }
      else 
        path.push_back(option);
    }
    else {
      if (!test.empty())
        test.clear();
      else if (path.size())
        path.pop_back();
      else
        break;
    }
  }

  return 0;
}