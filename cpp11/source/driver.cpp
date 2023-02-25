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
#include <unordered_map>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>


void hang_till_newline()
{
  std::cout << "...press enter to continue..." << std::ends;
  constexpr uint32_t buffer_size = LINE_WIDTH;
  char buffer[buffer_size] = { 0 };
  fgets(buffer, buffer_size, stdin);
}

uint32_t get_user_input(std::unordered_map<uint32_t, std::string> &index_to_option)
{
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
}

std::unordered_map<uint32_t, std::string>
get_category_options()
{
  std::unordered_map<uint32_t, std::string> index_to_feature;
  
  {
    uint32_t index = 1;
    index_to_feature[index++] = registrar::language;
    index_to_feature[index++] = registrar::library;
  }

  return index_to_feature;
}

// return feature options.
std::unordered_map<uint32_t, std::string>
get_options(bool language)
{
  std::unordered_map<uint32_t, std::string> index_to_feature;
  auto& repo = language? registrar::s_tests : registrar::s_library_tests;
  
  {
    uint32_t index = 1;
    for (auto& feature_pair : repo)
      index_to_feature[index++] = feature_pair.first;
  }

  return index_to_feature;
}

// return test options for a specific feature.
std::unordered_map<uint32_t, std::string>
get_options(
  bool language, 
  const std::string& feature)
{
  std::unordered_map<uint32_t, std::string> index_to_tests;

  {
    uint32_t index = 1;
    for (auto& test : registrar::get_tests(feature, language))
      index_to_tests[index++] = test;
  }

  return index_to_tests;
}

// return section options for a specific test within a feature.
std::unordered_map<uint32_t, std::string>
get_options(
  bool language, 
  const std::string& feature, 
  const std::string& test)
{
  std::unordered_map<uint32_t, std::string> index_to_sections;
  {
    uint32_t index = 1;
    for (auto& section : registrar::get_test_sections(feature, test, language))
      index_to_sections[index++] = section;
  }

  return index_to_sections;
}

int32_t main()
{
  std::unordered_map<uint32_t, std::string> index_to_options;
  std::vector<std::string> options;
  std::string title;
  constexpr uint32_t option_length = 73;
  constexpr const char* suffix = "...";

  std::cout << std::endl;

  while (1) {
    index_to_options.clear();

    switch (options.size()) {
    case 0: // language or library feature.
      index_to_options = get_category_options();
      title = "please select a category of features: ";
      break;
    case 1: // get feature
      index_to_options = get_options(
        options[0] == registrar::language);
      title = "please select a feature to review:";
      break;
    case 2: // get tests
      index_to_options = get_options(
        options[0] == registrar::language, 
        options[1]);
      title = "please select a test:";
      break;
    case 3: // get sections
      index_to_options = get_options(
        options[0] == registrar::language, 
        options[1], 
        options[2]);
      title = "please select a test section:";
      break;
    default:
      assert(false);
      break;
    }

    // print all the options.
    std::cout << std::string(LINE_WIDTH, '/') << std::endl;
    std::cout << "// " << title << std::endl;
    std::cout << std::string(LINE_WIDTH, '/') << std::endl;
    for (uint32_t i = 0, count = (uint32_t)index_to_options.size(); i < count; ++i) {
      std::string trimmed = index_to_options[i + 1];
      
      std::replace(std::begin(trimmed), std::end(trimmed), '\n', ' ');

      if (trimmed.length() > option_length)
        trimmed = trimmed.substr(0, option_length - strlen(suffix)) + suffix;
        
      std::cout << "[" << (i + 1) << "] " << trimmed << std::endl;
    }
    
    switch (options.size()) {
    case 0:
      std::cout << "[0] quit program" << std::endl;
      break;
    default:
      std::cout << "[0] go back" << std::endl;
      break;
    }

    if (auto entry = get_user_input(index_to_options)) {
      auto& option = index_to_options[entry];

      if (
        // run the test if there is only one section
        options.size() == 2 &&
        get_options(
          options[0] == registrar::language, 
          options[1], 
          option).size() == 1) {
          registrar::run_test(
            options[1], 
            option, 
            get_options(options[0] == registrar::language, options[1], option)[1], 
            options[0] == registrar::language);
          hang_till_newline();
      }
      else if (options.size() == 3) {
        registrar::run_test( 
          options[1], 
          options[2], 
          option,
          options[0] == registrar::language);
        hang_till_newline();
      }
      else
        options.push_back(option);
    }
    else {
      if (options.size())
        options.pop_back();
      else
        break;
    }

    std::cout << std::endl;
  }

  return 0;
}