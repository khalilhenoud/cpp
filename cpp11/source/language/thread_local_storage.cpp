/**
 * @file thread_local_storage.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>


REFERENCES(
  "https://en.wikipedia.org/wiki/C%2B%2B11#Thread-local_storage\n"
  "https://en.cppreference.com/w/cpp/language/storage_duration\n"
  "https://stackoverflow.com/questions/3734512/how-does-a-c-compiler-implement-thread-local-storage-in-c0x")

namespace {
std::unordered_map<const char*, int32_t> g_entries;
std::mutex g_entries_lock;
thread_local int32_t total = 0;
void multiply_by_4(const char* name, int32_t value)
{
  total = 4 * value;
  std::lock_guard<std::mutex> guard(g_entries_lock);
  g_entries[name] = total;
}

void print_values()
{
  for (auto& entry : g_entries)
    std::cout << '\t' << "entry[" << entry.first << "] = " << entry.second << std::endl;
}
}

TEST(
  thread_local_storage,
  "A new thread-local storage duration (in addition to the existing static,\n" 
  "dynamic and automatic) is indicated by the storage specifier thread_local.\n"
  "Any object which could have static storage duration (i.e., lifetime spanning\n" 
  "the entire execution of the program) may be given thread-local duration\n" 
  "instead. The intent is that like any other static-duration variable, a\n" 
  "thread-local object can be initialized using a constructor and destroyed\n" 
  "using a destructor.\n"
  "The storage for the object is allocated when the thread begins and\n" 
  "deallocated when the thread ends",
  SECTION(
    "example",
    std::cout << GIVEN[0] << std::endl;
    IN(std::vector<std::thread> thread_vector;)
    IN(PROTECT(thread_vector.emplace_back(multiply_by_4, "john", 1);))
    IN(PROTECT(thread_vector.emplace_back(multiply_by_4, "peter", 2);))
    IN(PROTECT(thread_vector.emplace_back(multiply_by_4, "micheal", 3);))
    IN(PROTECT(thread_vector.emplace_back(multiply_by_4, "noah", 4);))
    IN(for (auto& thread : thread_vector) thread.join();)
    IN(print_values();)
  )
)