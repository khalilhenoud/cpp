/**
 * @file utils.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\utils.h"
#include <cstdio>
#include <cstring>


std::string get_short_name(const char* file)
{ 
  std::string str = file; 
  size_t start = 0;
  size_t found = str.find_last_of("/\\");
  if (found == std::string::npos)
    return "";
  str = str.substr(found + 1);  
  start = str.find(".cpp"); 
  if (start != std::string::npos) {  
  size_t end = str.find(" ", start);  
  str.erase(start, end - start + 1);  
  }  
  start = str.find(".h"); 
  if (start != std::string::npos) {  
  size_t end = str.find(" ", start);  
  str.erase(start, end - start + 1);  
  }  
  return str; 
}

std::string get_directory_name(const char* file)
{
  std::string str = file;
  size_t start = 0;
  size_t found = str.find_last_of("/\\");
  if (found == std::string::npos)
    return "";
  str = str.substr(0, found);
  found = str.find_last_of("/\\");
  if (found == std::string::npos)
    return "";
  return str.substr(found + 1); 
}

std::vector<std::string> 
get_directory_hierarchy(
  const char* file, 
  const char* relative_to)
{
  std::vector<std::string> hierarchy;

  char data[1024] = { 0 };
  memset(data, 0, sizeof(data));
  memcpy(data, file, strlen(file));
  
  char* token = strtok(data, "/\\");
  bool start = false;
  while (token) {
    start = start || !strcmp(token, relative_to);
    if (start)
        hierarchy.push_back(token);
    token = strtok(NULL, "/\\");
  }

  hierarchy.back() = get_short_name(file);
  return hierarchy;
}