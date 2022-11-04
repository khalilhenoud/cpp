/**
 * @file unrestricted_unions.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <new>


REFERENCES("https://en.wikipedia.org/wiki/C%2B%2B11#Unrestricted_unions")

namespace {
// code taken from reference.
struct Point {
    Point() {}
    Point(int x, int y): x_(x), y_(y) {} 
    int x_, y_;
};

union U {
    int z;
    double w;
    Point p; // Invalid in C++03; valid in C++11.
    U() {} // Due to the Point member, a constructor definition is now needed.
    U(const Point& pt) : p(pt) {} // Construct Point object using initializer list.
    U& operator=(const Point& pt) { new(&p) Point(pt); return *this; } // Assign Point object using placement 'new'.
};
}

TEST(
  unrestricted_unions,
  "In C++03, there are restrictions on what types of objects can be members of a\n" 
  "union. For example, unions cannot contain any objects that define a\n" 
  "non-trivial constructor or destructor. C++11 lifts some of these\n" 
  "restrictions.\n"
  "If a union member has a non trivial special member function, the compiler\n" 
  "will not generate the equivalent member function for the union and it must be\n" 
  "manually defined.\n"
  "The changes will not break any existing code since they only relax current\n" 
  "rules.",
  SECTION(
    "example",
    std::cout << GIVEN[0] << std::endl;
    IN(U u(Point(1, 2));)
    IN(std::cout << '\t' << u.p.x_ << std::endl;)
  )
)