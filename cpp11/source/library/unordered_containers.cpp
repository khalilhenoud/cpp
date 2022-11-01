/**
 * @file unordered_containers.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#unordered-containers")

TEST(
  unordered_containers,
  "These containers maintain average constant-time complexity for search,\n" 
  "insert, and remove operations. In order to achieve constant-time complexity,\n" 
  "sacrifices order for speed by hashing elements into buckets. There are four\n" 
  "unordered containers:",
  SECTION(
    "unordered_map, unordered_multimap",
    IN(PROTECT(std::unordered_map<std::string, int32_t> data_map;))
    IN(data_map["john"] = 1;)
    IN(data_map["mathew"] = 2;)
    IN(data_map["micheal"] = 3;)
    IN(data_map["john"] = 4;)
    IN(for(auto& pair : data_map) std::cout << '\t' << pair.first << ": " << pair.second << std::endl;)
    std::cout << std::endl;
    IN(PROTECT(std::unordered_multimap<std::string, int32_t> data_mmap;))
    IN(PROTECT(data_mmap.insert({{"john", 1}, {"mathew", 2}, {"micheal", 3}, {"john", 4}});))
    IN(for(auto& pair : data_mmap) std::cout << '\t' << pair.first << ": " << pair.second << std::endl;)
  )
  SECTION(
    "unordered_set, unordered_multiset",
    IN(std::unordered_set<std::string> data_set;)
    IN(data_set.insert("john");)
    IN(data_set.insert("mathew");)
    IN(data_set.insert("micheal");)
    IN(data_set.insert("john");)
    IN(for(auto& entry : data_set) std::cout << '\t' << entry << std::endl;)
    std::cout << std::endl;
    IN(std::unordered_multiset<std::string> data_mset;)
    IN(data_mset.insert("john");)
    IN(data_mset.insert("mathew");)
    IN(data_mset.insert("micheal");)
    IN(data_mset.insert("john");)
    IN(for(auto& entry : data_mset) std::cout << '\t' << entry << std::endl;)
  )
)