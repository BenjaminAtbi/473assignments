
#pragma once

#include <stdint.h>


namespace shapes {


  // A simple boilerplate for strong aliases to protect the 
  // boundaries of the API.
  template<typename Value, typename Tag>
  class StrongAlias {
  public:
    explicit StrongAlias(Value value)
      : value{value}
        { }

    operator Value() const { return value; }

  private:
    const Value value;
  };

  
  using Side = StrongAlias<int, struct SideTag>;
  using Angle = StrongAlias<double, struct AngleTag>;


  class Parallelogram {
  public:
    enum class Kind : uint8_t {
      PARALLELOGRAM, // A quadrilateral with equal opposing sides
      RECTANGLE,     // A parallelogram with all angles equal
      RHOMBUS,       // A parallelogram with all sides equal
      SQUARE,        // A parallelogram with both equal angles and equal sides
    };

    // Constructs a new parallelogram from the side lengths and angle passed in.
    // The interior angle must be less than 180 degrees by contract.
    Parallelogram(Side side1, Side side2, Angle interior);

    // Return the sum of all sides of the parallelogram
    int getPerimeter() const;

    // Return the area of the parallelogram
    double getArea() const;

    // Return the most specific kind or classification of the parallelogram
    // as determined by its sides and angle.
    Kind getKind() const;

    // Return true if this parallelogram is a rectangle.
    bool isRectangle() const;

    // Return true if this parallelogram is a rhombus.
    bool isRhombus() const;

    // Return true if this parallelogram is a square.
    bool isSquare() const;

  private:
    const int side1;
    const int side2;
    const double interior;
  };


}


