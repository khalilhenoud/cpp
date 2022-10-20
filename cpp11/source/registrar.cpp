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
std::unordered_map<std::string, feature_tests> registrar::s_library_tests;

const std::string registrar::library = "library";
const std::string registrar::language = "language";

registrar::registrar(
  const std::string& directory,
  const std::string& feature, 
  test_function func, 
  const std::string& test_name)
{
  if (directory == library) {
    if (std::find_if(
          s_library_tests[feature].begin(), 
          s_library_tests[feature].end(), 
          [=](const auto& pair)
          { 
            return pair.second == func;
          }) == s_library_tests[feature].end())
            s_library_tests[feature][test_name] = func;
  } else if (directory == language) {
    if (std::find_if(
          s_tests[feature].begin(), 
          s_tests[feature].end(), 
          [=](const auto& pair)
          { 
            return pair.second == func;
          }) == s_tests[feature].end())
            s_tests[feature][test_name] = func;
  } else
    assert(false);
}

void 
registrar::run_all_tests()
{
  std::cout << "Tests to run: " << s_tests.size() << std::endl;
  for (auto& feature_tests : s_tests) {
    for (auto& test : feature_tests.second)
    {
      // prints the description and returns the section map.
      auto sections = test.second(test.first.c_str(), "").second;
      for (auto& section : sections)
        test.second(test.first.c_str(), section.first);
    }
  }
  
  s_tests.clear();
}

std::vector<std::string> 
registrar::get_tests(
  const std::string& feature, 
  bool language)
{
  std::vector<std::string> tests;

  if (language) {
    if (s_tests.find(feature) != s_tests.end()) {
      for (auto& test : s_tests[feature]) {
        tests.push_back(test.first);
      }
    }
  } else {
    if (s_library_tests.find(feature) != s_library_tests.end()) {
      for (auto& test : s_library_tests[feature]) {
        tests.push_back(test.first);
      }
    }
  }

  return tests;
}

std::vector<std::string> 
registrar::get_test_sections(
  const std::string& feature, 
  const std::string& test,
  bool language)
{
  std::vector<std::string> sections;

  std::vector<std::string> tests = get_tests(feature, language);
  auto& repo = language ? s_tests : s_library_tests;
  auto iter = std::find_if(
    tests.begin(), 
    tests.end(), 
    [=](const auto name) {
      return !strcmp(name.c_str(), test.c_str());
    });

  if (iter != tests.end()) {
    auto func_iter = std::find_if(
      repo[feature].begin(), 
      repo[feature].end(), 
      [=](const auto& pair){
        return !strcmp(pair.first.c_str(), test.c_str());
      });

    assert(func_iter != repo[feature].end());
    sections = func_iter->second(nullptr, "").first;
  }

  return sections;
}

void 
registrar::run_test(
  const std::string& feature, 
  const std::string& test, 
  const std::string& section,
  bool language) 
{
  auto& repo = language ? s_tests : s_library_tests;
  if (repo.find(feature) != repo.end()) {
    auto& tests = repo[feature];
    auto test_iter = std::find_if(
      tests.begin(), 
      tests.end(), 
      [=](const auto& pair){
        return !strcmp(test.c_str(), pair.first.c_str());
      });
    
    if (test_iter != tests.end())
    {
      auto test_sections = test_iter->second(test_iter->first.c_str(), "").second;
      if (test_sections.find(section) != test_sections.end())
        test_iter->second(test_iter->first.c_str(), section.c_str());
    }
  }
}