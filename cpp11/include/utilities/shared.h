/**
 * @file shared.h
 * @author khalilhenoud@gmail.com
 * @brief shared macros and the likes
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "config.h"

#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>


#define ANNOUNCE(announce) \
  if (announce) \
  { \
   std::string str = __FUNCSIG__; \
   size_t start = 0;  \
   start = str.find("__"); \
   if (start != std::string::npos) {  \
    size_t end = str.find(" ", start);  \
    str.erase(start, end - start + 1);  \
   }  \
   start = str.find("struct"); \
   while (start != std::string::npos) { \
    size_t end = str.find(" ", start);  \
    str.erase(start, end - start + 1);  \
    start = str.find("struct"); \
   }  \
   start = str.find("`anonymous-namespace'::"); \
   while (start != std::string::npos) { \
    size_t end = start + strlen("`anonymous-namespace'::");  \
    str.erase(start, end - start);  \
    start = str.find("`anonymous-namespace'::"); \
   }  \
   std::cout << "\t[] function: " << str << std::endl;\
  }

#define GIVEN \
  []() \
  { \
    std::vector<std::string> sections; \
  \
    std::ifstream codefile(__FILE__); \
    std::stringstream buffer; \
    buffer << codefile.rdbuf(); \
  \
    std::string code = buffer.str(); \
    std::string delimiters[] = {"namespace {"}; \
    std::string scope_delimiters = "{}"; \
    int32_t value[] = { 1, -1}; \
  \
    size_t start = 0, end = 0; \
    int32_t counter; \
    while ( \
      (start = code.find(delimiters[0], start)) != std::string::npos && \
      code.at(start + delimiters[0].length()) != '"') { \
      start = start + delimiters[0].length(); \
      end = start; \
      counter = 1; \
      while (counter) { \
        end = code.find_first_of(scope_delimiters, end + 1); \
        assert(end != std::string::npos); \
        counter += value[code.at(end) == scope_delimiters.at(0) ? 0 : 1]; \
      } \
      \
      start = code.find_first_of('\n', start) + 1; \
      sections.push_back(code.substr(start, end - start)); \
      start = end; \
    } \
  \
    return sections; \
  }()

#define BLOCK_GIVEN \
  []() \
  { \
    std::vector<std::string> sections; \
  \
    std::ifstream codefile(__FILE__); \
    std::stringstream buffer; \
    buffer << codefile.rdbuf(); \
  \
    std::string code = buffer.str(); \
    std::string delimiters[] = {"//<<", "//>>"}; \
  \
    size_t start = 0, end = 0; \
    while ( \
      (start = code.find(delimiters[0], start)) != std::string::npos && \
      code.at(start + delimiters[0].length()) != '"') { \
      start = code.find_first_of('\n', start) + 1; \
      end = code.find(delimiters[1], start); \
      sections.push_back(code.substr(start, end - start)); \
      start = end; \
    } \
  \
    return sections; \
  }()


// use it to escape ',' in undesired macro sequences.
#define PROTECT(...) __VA_ARGS__ 

#define PRINTIFY(x, ...) std::cout << #x << __VA_ARGS__;
#define IN(x) \
  PRINTIFY(x, std::endl) \
  x;

#define DESC_IN(desc, x) \
  std::cout << "// " << desc << std::endl; \
  PRINTIFY(x, std::endl) \
  x;

#define IN_DESC(x, desc) \
  PRINTIFY(x, " // " << desc << std::endl) \
  x;

#define IN_ERROR(x, message) \
  PRINTIFY(x, " // " << message << std::endl)

static std::chrono::high_resolution_clock::time_point g_timepoints[2];
static std::chrono::microseconds g_delta;

#define IN_TIMED(x) \
  PRINTIFY(x, std::endl) \
  g_timepoints[0] = std::chrono::high_resolution_clock::now();\
  x; \
  g_timepoints[1] = std::chrono::high_resolution_clock::now(); \
  g_delta = std::chrono::duration_cast<std::chrono::microseconds>(g_timepoints[1] - g_timepoints[0]);  \
  std::cout << " > operation finished in: " << g_delta.count() << " microsecs"<< std::endl;