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

#include <unordered_map>
#include <unordered_set>
#include <string>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#unordered-containers")

TEST(
  unordered_containers,
R"--(
These containers maintain average constant-time complexity for search, insert, 
and remove operations. In order to achieve constant-time complexity, sacrifices
order for speed by hashing elements into buckets. There are four unordered 
containers:
)--",
  SECTION(
    "unordered_map, unordered_multimap",
    IN(PROTECT(std::unordered_map<std::string, int32_t> data_map;))
    IN(data_map["john"] = 1;)
    IN(data_map["mathew"] = 2;)
    IN(data_map["micheal"] = 3;)
    IN(data_map["john"] = 4;)
    IN(for(auto& pair : data_map) print_safe("\t%s: %i\n", pair.first.c_str(), pair.second);)
    print_safe("\n");
    IN(PROTECT(std::unordered_multimap<std::string, int32_t> data_mmap;))
    IN(PROTECT(data_mmap.insert({{"john", 1}, {"mathew", 2}, {"micheal", 3}, {"john", 4}});))
    IN(for(auto& pair : data_mmap) print_safe("\t%s: %i\n", pair.first.c_str(), pair.second);)
  )
  SECTION(
    "unordered_set, unordered_multiset",
    IN(std::unordered_set<std::string> data_set;)
    IN(data_set.insert("john");)
    IN(data_set.insert("mathew");)
    IN(data_set.insert("micheal");)
    IN(data_set.insert("john");)
    IN(for(auto& entry : data_set) print_safe("\t%s\n", entry.c_str());)
    print_safe("\n");
    IN(std::unordered_multiset<std::string> data_mset;)
    IN(data_mset.insert("john");)
    IN(data_mset.insert("mathew");)
    IN(data_mset.insert("micheal");)
    IN(data_mset.insert("john");)
    IN(for(auto& entry : data_mset) print_safe("\t%s\n", entry.c_str());)
  )
)