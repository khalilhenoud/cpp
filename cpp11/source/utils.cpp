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