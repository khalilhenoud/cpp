/**
 * @file data.h
 * @author khalilhenoud@gmail.com
 * @brief A simple data interface class.
 * @version 0.1
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once


struct data {
  virtual void print_data() const = 0;
  virtual void clear_data() = 0;
  virtual uint32_t size() const = 0;
};