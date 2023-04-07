/**
 * @file utils.h
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <string>
#include <vector>


std::string get_short_name(const char* file);

std::string get_directory_name(const char* file);

std::vector<std::string> get_directory_hierarchy(const char* file, const char* relative_to);