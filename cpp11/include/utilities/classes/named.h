/**
 * @file named.h
 * @author khalilhenoud@gmail.com
 * @brief A class with a 'm_name' variable.
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "interfaces\data.h"
#include "utilities\shared.h"

#include <algorithm>
#include <iostream>
#include <type_traits>
#include <cstring>


template <bool announce_prototype = false>
struct named : data {
  virtual ~named()
  {
    ANNOUNCE(announce_prototype);
  }

  named()
  {
    ANNOUNCE(announce_prototype);
  }

  named(const char* _name, bool print = true)
    : m_name{ _name }
  {
    ANNOUNCE(announce_prototype);
    if (print)
      print_data();
  }

  named(const named& other)
    : m_name{ other.m_name }
  {
    ANNOUNCE(announce_prototype);
  }

  named(named&& other) noexcept
  {
    ANNOUNCE(announce_prototype);

    m_name = other.m_name;
    other.m_name = nullptr;
  }

  named& operator=(const named& rhs)
  {
    ANNOUNCE(announce_prototype);

    m_name = rhs.m_name;
    return *this;
  }

  named& operator=(named&& rhs) noexcept
  {
    ANNOUNCE(announce_prototype);

    std::swap(m_name, rhs.m_name);
    return *this;
  }

  void print_data() const override
  {
    ANNOUNCE(announce_prototype);
    std::cout << ">> ";

    if (m_name)
      std::cout << "m_name is: " << m_name << std::endl;
    else
      std::cout << "no m_name assigned" << std::endl;
  }

  void clear_data() override
  {
    ANNOUNCE(announce_prototype);

    m_name = nullptr;
  }

  uint32_t size() const override
  {
    return (uint32_t)strlen(m_name);
  }

private:
  const char* m_name = nullptr;
};