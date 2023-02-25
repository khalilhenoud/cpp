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

#include <string>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <mutex>
#include <cstdio>
#include <regex>


#define LINE_WIDTH  80

// use it to escape ',' in undesired macro sequences.
#define PROTECT(...) __VA_ARGS__ 

#define STRINGIFY(x) #x

// thread-safe wrapper around printf.
static std::recursive_mutex s_printf_mutex;

template<typename... Args>
int32_t 
print_safe(const char* format, Args... args)
{
  std::lock_guard<std::recursive_mutex> lk(s_printf_mutex);
  return printf(format, args...);
}

inline
int32_t 
print_safe(const char* str)
{
  std::lock_guard<std::recursive_mutex> lk(s_printf_mutex);
  return printf("%s", str);
}

#define IN(x) \
  print_safe("%s\n", STRINGIFY(x)); \
  x;

inline
void
decomp_print(const char* desc, size_t width = LINE_WIDTH, const char* prefix = "// ")
{
  assert(width > strlen(prefix));

  size_t line_width = width - strlen(prefix);
  size_t length = strlen(desc);
  size_t lines = length / line_width;
  
  char comment[2048];
  memset(comment, 0, sizeof(comment));
  memcpy(comment, desc, length);

  std::string to_print;
  char* p = NULL;
  p = strtok(comment, " ");
  do {
    if (strlen(p) + to_print.length() > line_width) {
      printf("%s%s\n", prefix, to_print.c_str());
      to_print = "";
    }

    to_print += p;
    to_print += " ";
    p = strtok(NULL, " ");
  } while (p);

  if (to_print.length())
    printf("%s%s\n", prefix, to_print.c_str());
}

#define DESC_IN(desc, x) \
  { \
    std::lock_guard<std::recursive_mutex> lk(s_printf_mutex); \
    decomp_print(desc); \
    print_safe("%s\n", STRINGIFY(x)); \
  } \
  x;

#define IN_DESC(x, desc) \
  print_safe("%s // %s\n", STRINGIFY(x), desc); \
  x;

#define IN_ERROR(x, message) \
  print_safe("%s // %s\n", STRINGIFY(x), message);


static std::chrono::high_resolution_clock::time_point g_timepoints[2];
static std::chrono::microseconds g_delta;

#define IN_TIMED(x) \
  print_safe("%s\n", STRINGIFY(x)); \
  g_timepoints[0] = std::chrono::high_resolution_clock::now();\
  x; \
  g_timepoints[1] = std::chrono::high_resolution_clock::now(); \
  g_delta = std::chrono::duration_cast<std::chrono::microseconds>(g_timepoints[1] - g_timepoints[0]);  \
  print_safe(" > operation finished in: %lld microsecs\n", g_delta.count());


////////////////////////////////////////////////////////////////////////////////
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
   print_safe("\t[] function: %s\n", str.c_str()); \
  }

////////////////////////////////////////////////////////////////////////////////
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

// TODO: strip the leading whitespaces, use it in attributes.cpp.
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