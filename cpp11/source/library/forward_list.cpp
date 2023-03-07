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

#include <forward_list>


REFERENCES("https://en.cppreference.com/w/cpp/container/forward_list")

namespace {
void print(std::forward_list<int32_t>& data)
{
  print_safe("\t");
  for (auto& entry : data)
    print_safe("%i ", entry);
  print_safe("\n");
}
}

TEST(
  forward_list,
R"--(
std::forward_list is a container that supports fast insertion and removal of
elements from anywhere in the container. Fast random access is not supported.
It is implemented as a singly-linked list. Compared to std::list this container
provides more space efficient storage when bidirectional iteration is not 
needed.
)--",
  SECTION(
    "basic example",
    print_safe("%s\n", GIVEN[0].c_str());
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