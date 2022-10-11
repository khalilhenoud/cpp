/**
 * @file printer.h
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "utilities\shared.h"

#include <iostream>
#include <type_traits>


struct printer {

  template<class T, bool annouce_prototype = false>
  static std::enable_if_t<std::is_rvalue_reference_v<T&&>> print(T&& value) 
  {
    ANNOUNCE(annouce_prototype);
    std::cout << "\t[] rvalue is: " << value << std::endl;
  }

  template<class T, bool annouce_prototype = false>
  static std::enable_if_t<!std::is_rvalue_reference_v<T&&>> print(T&& value) 
  {
    ANNOUNCE(annouce_prototype);
    std::cout << "\t[] lvalue is: " << value << std::endl;
  }
};
