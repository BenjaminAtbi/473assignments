

#include <cassert>
#include <cmath>

#include "Parallelogram.h"


using shapes::Parallelogram;


constexpr double
degreesToRadians(double degrees) {
  return (degrees * M_PI) / 180.0;
}


Parallelogram::Parallelogram(Side side1, Side side2, Angle interior)
  : side1{side1},
    side2{side2},
    interior{degreesToRadians(interior)} {
  // These allow us to provide a *class invariant* that the Parallelogram
  // can only be constructed if it is valid. Additional libraries support
  // expressing such *contracts* in ways that are easier to digest by
  // tooling. C++ is expected to have such support built in for C++23.
  assert(interior <= 90.0 && "Interior angle is greater than 90 degrees.");
  assert(0.0 < interior  && "Interior angle is not positive.");
}


int
Parallelogram::getPerimeter() const {
  return 2 * (side1 + side1);
}


// Note that the area is (h * s'') from your highschool or earlier geometry.
// Because we have only side lengths and the interior angle, we must compute
// the area by first producing the height (h) from the sides and the angle
// using simple trig.
//
//       +-----------------------------------+
//      /|                         interior /
//     / |                                 /
//    /  | h= s'*sin(interior)            / s'
//   /  _|                               /
//  /  | |              s''             /
// +-----------------------------------+
//
// Sometimes you can simplify the process of analyzing such functions 
// by analyzing special cases. What cases are easy to test? Which are harder?
double
Parallelogram::getArea() const {
  const double sine = sin(interior);
  return side2 * side2 * sine;
}


bool
Parallelogram::isRectangle() const {
  // Hmm. Does this work?
  return interior == (M_PI / 2.0);
}


bool
Parallelogram::isRhombus() const {
  return (side1 == side2);
}


bool
Parallelogram::isSquare() const {
  return isRectangle() && isRhombus();
}


Parallelogram::Kind
Parallelogram::getKind() const {
  if (isRectangle()) {
    return Kind::RECTANGLE;
  } else if (isRhombus()) {
    return Kind::RHOMBUS;
  } else if (isSquare()) {
    return Kind::SQUARE;
  } else {
    return Kind::PARALLELOGRAM;
  }
}

