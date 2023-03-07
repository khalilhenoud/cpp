/**
 * @file atomic.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <atomic>
#include <mutex>
#include <thread>

/**
REFERENCES("https://en.cppreference.com/w/cpp/atomic/atomic")

namespace {
using func_ptr = void(*)();
std::atomic<func_ptr> print_ptr = nullptr;
std::mutex print_mutex;
std::atomic<uint32_t> c0 = 0;
std::atomic<uint32_t> c1 = 0;

void print_pong()
{
  std::lock_guard<std::mutex> lk(print_mutex);
  std::cout << "\t...pong" << std::endl;
}

void print_ping()
{
  std::lock_guard<std::mutex> lk(print_mutex);
  std::cout << "\t...ping" << std::endl;
}

void ping()
{

}

void pong()
{
  func_ptr ptr = nullptr, ptr_target = print_pong;
  ptr = print_ptr.load();
  while (ptr != nullptr) {
    
  }
}
}

TEST(
  atomic,
  "As defined in atomic.h:\n"
  "     (1) template<class T> \n"
  "         struct atomic;    \n"
  "     (2) template<class U> \n"
  "         struct atomic<U*>;\n"
  "Each instantiation and full specialization of the std::atomic template\n" 
  "defines an atomic type. If one thread writes to an atomic object while\n" 
  "another thread reads from it, the behavior is well-defined (see memory model\n" 
  "for details on data races).\n"
  "In addition, accesses to atomic objects may establish inter-thread\n" 
  "synchronization and order non-atomic memory accesses as specified by\n" 
  "std::memory_order.\n"
  "std::atomic is neither copyable nor movable.\n"
  "\n"
  "Specializations:\n"
  "----------------\n"
  "Primary template: \n"
  "The primary std::atomic template may be instantiated with any type T\n" 
  "satisfying the following, note that the program is ill-formed otherwise:\n" 
  " - std::is_trivially_copyable<T>::value\n"
  " - std::is_copy_constructible<T>::value\n"
  " - std::is_move_constructible<T>::value\n"
  " - std::is_copy_assignable<T>::value\n"
  " - std::is_move_assignable<T>::value\n"
  "std::atomic<bool> uses the primary template. It is guaranteed to be a\n" 
  "standard layout struct.\n"
  "\n"
  "Partial Specializations:\n"
  "------------------------\n"
  "The standard library provides partial specializations of the std::atomic\n" 
  "template for the following types with additional properties that the primary\n" 
  "template does not have:\n"
  "(2) Partial specializations std::atomic<U*> for all pointer types. These\n" 
  "specializations have standard layout, trivial default constructors,\n" 
  "(until C++20) and trivial destructors. Besides the operations provided for\n" 
  "all atomic types, these specializations additionally support atomic\n" 
  "arithmetic operations appropriate to pointer types, such as fetch_add,\n" 
  "fetch_sub.\n"
  "Specializations for integral types:\n"
  "-----------------------------------\n"
  "When instantiated with one of the integral types defined in <cstdint>,\n" 
  "std::atomic provides additional atomic operations appropriate to integral\n" 
  "types such as fetch_add, fetch_sub, fetch_and, fetch_or, fetch_xor.\n"
  "\n"
  "Type aliases:\n"
  "-------------\n"
  "Type aliases are provided for bool and all integral types listed above, as\n" 
  "follows:\n"
  "atomic_bool        ->      std::atomic<bool>\n"
  "atomic_char        ->      std::atomic<char>\n"
  "atomic_short       ->      std::atomic<short>\n"
  "atomic_ushort      ->      std::atomic<unsigned short>\n"
  "       ...\n"
  "       ...\n"
  "atomic_ullong      ->      std::atomic<unsigned long long>\n"
  "       ...\n"
  "atomic_size_t      ->      std::atomic<std::size_t>\n"
  "atomic_ptrdiff_t   ->      std::atomic<std::ptrdiff_t>\n"
  "atomic_intmax_t    ->      std::atomic<std::intmax_t>\n"
  "atomic_uintmax_t   ->      std::atomic<std::uintmax_t>\n"
  "Note: std::atomic_intN_t, std::atomic_uintN_t, std::atomic_intptr_t,\n" 
  "and atomic_uintptr_t are defined if and only if std::intN_t, std::uintN_t,\n" 
  "std::intptr_t, and std::uintptr_t are defined, respectively.",
  SECTION(
    "example",
    std::cout << GIVEN[0] << std::endl;
  )
)
*/