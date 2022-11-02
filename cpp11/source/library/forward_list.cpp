/**
 * @file forward_list.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <forward_list>


REFERENCES("https://en.cppreference.com/w/cpp/container/forward_list")

namespace {
void print(std::forward_list<int32_t>& data)
{
  std::cout << "\t";
  for (auto& entry : data)
    std::cout << entry << std::ends;
  std::cout << std::endl;
}
}

TEST(
  forward_list,
  "std::forward_list is a container that supports fast insertion and removal of\n" 
  "elements from anywhere in the container. Fast random access is not supported.\n" 
  "It is implemented as a singly-linked list. Compared to std::list this\n" 
  "container provides more space efficient storage when bidirectional iteration\n" 
  "is not needed.",
  SECTION(
    "basic example",
    std::cout << GIVEN[0] << std::endl;
    IN(std::forward_list<int32_t> data;)
    IN(data.push_front(1);)
    IN(data.push_front(2);)
    IN(data.push_front(3);)
    IN(data.push_front(4);)
    IN(data.push_front(5);)
    IN(data.push_front(6);)
    IN(print(data);)
  )
)