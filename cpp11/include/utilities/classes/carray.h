/**
 * @file carray.h
 * @author khalilhenoud@gmail.com
 * @brief A simple array class container.
 * @version 0.1
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "interfaces\data.h"
#include "utilities\shared.h"

#include <iostream>
#include <algorithm>
#include <new>
#include <type_traits>
#include <cassert>


template<class T,
bool announce_prototype = false,
typename std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
struct carray : data {
  virtual ~carray()
  {
    ANNOUNCE(announce_prototype);

    clear_data();
  }

  carray(uint32_t count, T startvalue)
  {
    ANNOUNCE(announce_prototype);

    assert(count != 0);
    m_count = count;
    m_data = new T[m_count];
    for (uint32_t i = 0; i < m_count; ++i)
      m_data[i] = startvalue++;
  }

  carray(const carray& other)
  {
    ANNOUNCE(announce_prototype);

    clear_data();

    m_count = other.m_count;
    m_data = new T[m_count];
    for (uint32_t i = 0; i < m_count; ++i)
      m_data[i] = other.m_data[i];
  }

  carray(carray&& other) noexcept
  {
    ANNOUNCE(announce_prototype);

    std::swap(m_count, other.m_count);
    std::swap(m_data, other.m_data);
  }

  carray& operator=(const carray& rhs)
  {
    ANNOUNCE(announce_prototype);

    clear_data();

    // deep copy.
    m_count = rhs.m_count;
    m_data = new T[m_count];
    for (uint32_t i = 0; i < m_count; ++i)
      m_data[i] = rhs.m_data[i];

    return *this;
  }

  carray& operator=(carray&& rhs) noexcept
  {
    ANNOUNCE(announce_prototype);

    std::swap(m_count, rhs.m_count);
    std::swap(m_data, rhs.m_data);
    return *this;
  }

  void print_data() const override
  {
    ANNOUNCE(announce_prototype);

    std::cout << ">> ";
    std::cout << "Data in carray: ";

    for (uint32_t i = 0; i < m_count; ++i)
      std::cout << m_data[i] << ((i == m_count - 1) ? '.' : ',') << std::ends;
    std::cout << std::endl;
  }

  void clear_data() override
  {
    ANNOUNCE(announce_prototype);

    if (m_data)
      delete[] m_data;
    m_data = nullptr;
    m_count = 0;
  }

  uint32_t size() const override
  {
    return m_count;
  }

private:
  T* m_data = nullptr;
  uint32_t m_count = 0;
};
