/**
 * @file registrar.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\registrar.h"
#include <cassert>


std::unordered_map<std::string, feature_tests_map> registrar::s_tests;
hierarchy_tree registrar::directory_tree;

registrar::registrar(
  std::vector<std::string> directory_path,
  const std::string& feature, 
  test_function func, 
  const std::string& test_name)
{
  update_directory_tree(directory_path);

  auto feature_key = get_key(directory_path);
  if (std::find_if(
        s_tests[feature_key].begin(),
        s_tests[feature_key].end(),
        [=](const auto& pair)
        { 
          return pair.second == func;
        }) == s_tests[feature_key].end())
    s_tests[feature_key][test_name] = func;
}

bool
registrar::is_file(const std::string& entry_key)
{
  assert(directory_tree.find(entry_key) != directory_tree.end());
  return directory_tree[entry_key].children.size() == 0;
}

void
registrar::update_directory_tree(const std::vector<std::string>& directory_path)
{
  std::vector<std::string> current_path;
  std::string parent_key = registrar::source;
  for (const auto& directory : directory_path) {
    current_path.push_back(directory);
    auto key = get_key(current_path);
    if (directory_tree.find(key) == directory_tree.end()) {
      directory_tree[key] = { directory };
      if (parent_key != key)
        directory_tree[parent_key].children.insert(directory);
    } 
    
    parent_key = key;
  }
}

std::string
registrar::get_key(const std::vector<std::string>& directory_path, int32_t to_index)
{
  std::string key = "";
  size_t count = to_index == -1 ? directory_path.size() : (size_t)to_index;
  for (size_t i = 0; i < count; ++i)
    key += directory_path[i];
  return key;
}

std::vector<std::string> 
registrar::get_tests(const std::string& feature_key)
{
  std::vector<std::string> tests;
  if (s_tests.find(feature_key) != s_tests.end()) {
    for (auto& test : s_tests[feature_key]) {
      tests.push_back(test.first);
    }
  }

  return tests;
}

std::vector<std::string> 
registrar::get_test_sections(
  const std::string& feature_key, 
  const std::string& test)
{
  std::vector<std::string> sections;
  std::vector<std::string> tests = get_tests(feature_key);
  auto iter = std::find_if(
    tests.begin(), 
    tests.end(), 
    [=](const auto name) {
      return !strcmp(name.c_str(), test.c_str());
    });

  if (iter != tests.end()) {
    auto func_iter = std::find_if(
      s_tests[feature_key].begin(),
      s_tests[feature_key].end(),
      [=](const auto& pair){
        return !strcmp(pair.first.c_str(), test.c_str());
      });

    assert(func_iter != s_tests[feature_key].end());
    sections = func_iter->second(nullptr, "").first;
  }

  return sections;
}

void
registrar::print_test_description(
  const std::string& feature_key,
  const std::string& test)
{
  if (s_tests.find(feature_key) != s_tests.end()) {
    auto& tests = s_tests[feature_key];
    auto test_iter = std::find_if(
      tests.begin(),
      tests.end(),
      [=](const auto& pair) {
        return !strcmp(test.c_str(), pair.first.c_str());
      });

    if (test_iter != tests.end())
      test_iter->second(test_iter->first.c_str(), "").second;
  }
}

void
registrar::run_test(
  const std::string& feature_key,
  const std::string& test,
  const std::string& section,
  bool with_description)
{
  if (s_tests.find(feature_key) != s_tests.end()) {
    auto& tests = s_tests[feature_key];
    auto test_iter = std::find_if(
      tests.begin(),
      tests.end(),
      [=](const auto& pair) {
        return !strcmp(test.c_str(), pair.first.c_str());
      });

    if (test_iter != tests.end())
    {
      test_section test_sections;
      if (with_description) {
        test_sections = test_iter->second(test_iter->first.c_str(), "").second;
        
        // Make space between the description and the code. This is only
        // neccessary if there is code associated with the section (non reserved
        // section).
        if (section != RESERVED_NAME)
          std::cout << std::endl;
      } else
        test_sections = test_iter->second(nullptr, "").second;
      if (test_sections.find(section) != test_sections.end())
        test_iter->second(test_iter->first.c_str(), section.c_str());
    }
  }
}