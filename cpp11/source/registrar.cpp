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


std::unordered_map<std::string, feature_tests> registrar::s_tests;

registrar::registrar(
  const std::string& feature, 
  test_function func, 
  const std::string& test_name)
{
  if (std::find_if(s_tests[feature].begin(), s_tests[feature].end(), 
    [=](const auto& pair)
    { 
      return pair.second == func;
    }) == s_tests[feature].end())
    s_tests[feature][test_name] = func;
}

void 
registrar::run_all_tests()
{
  std::cout << "Tests to run: " << s_tests.size() << std::endl;
  for (auto& feature_tests : s_tests) {
    for (auto& test : feature_tests.second)
    {
      // prints the description and returns the section map.
      auto sections = test.second(test.first.c_str(), "");
      for (auto& section : sections)
        test.second(test.first.c_str(), section.first);
    }
  }
  
  s_tests.clear();
}

std::vector<std::string> 
registrar::get_tests(const std::string& feature)
{
  std::vector<std::string> tests;

  if (s_tests.find(feature) != s_tests.end()) {
    for (auto& test : s_tests[feature]) {
      tests.push_back(test.first);
    }
  }

  return tests;
}

std::vector<std::string> 
registrar::get_test_sections(const std::string& feature, const std::string& test)
{
  std::vector<std::string> sections;

  std::vector<std::string> tests = get_tests(feature);
  auto iter = std::find_if(
    tests.begin(), 
    tests.end(), 
    [=](const auto name) {
      return !strcmp(name.c_str(), test.c_str());
    });

  if (iter != tests.end()) {
    auto func_iter = std::find_if(
      s_tests[feature].begin(), 
      s_tests[feature].end(), 
      [=](const auto& pair){
        return !strcmp(pair.first.c_str(), test.c_str());
      });

    assert(func_iter != s_tests[feature].end());

    auto test_sections = func_iter->second(nullptr, "");
    for (auto& section : test_sections)
      sections.push_back(section.first);
  }

  return sections;
}

void 
registrar::run_test(
  const std::string& feature, 
  const std::string& test, 
  const std::string& section) 
{
  if (s_tests.find(feature) != s_tests.end()) {
    auto& tests = s_tests[feature];
    auto test_iter = std::find_if(
      tests.begin(), 
      tests.end(), 
      [=](const auto& pair){
        return !strcmp(test.c_str(), pair.first.c_str());
      });
    
    if (test_iter != tests.end())
    {
      auto test_sections = test_iter->second(test_iter->first.c_str(), "");
      if (test_sections.find(section) != test_sections.end())
        test_iter->second(test_iter->first.c_str(), section.c_str());
    }
  }
}