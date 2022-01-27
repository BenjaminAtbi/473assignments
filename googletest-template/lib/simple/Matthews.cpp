
#include "Matthews.h"

using sequence::checkMatthewsOutcome;
using sequence::MatthewsOutcome;


// We can wrap the modulus operator to make it behave nicely
// over the negative numbers. This simply translates the negative
// modulus into its smallest positive representative.
int64_t
modHelper(int64_t dividend, int64_t divisor) {
  return ((dividend % divisor) + divisor) % divisor;
}


// Matthews cycles capture a relationship to the Collatz sequence:
// https://mathworld.wolfram.com/CollatzProblem.html
// You do not need to know or care about them to test this code.
// Ask yourself: How many tests do you need?
//               How many would you need to test it well?
//
MatthewsOutcome
sequence::checkMatthewsOutcome(int64_t number) {
  while (true) {
    const auto remainder = modHelper(number, 3);

    // First consider the termination conditions.
    if (0 == remainder) {
      return MatthewsOutcome::ZERO;
    } else if (-1 == number) {
      return MatthewsOutcome::MINUS_ONE_CYCLE;
    } else if (-2 == number || -4 == number) {
      return MatthewsOutcome::MINUS_TWO_CYCLE;
    }

    // Then consider the continuation conditions.
    if (0 == remainder) {
      number = 7 * number + 3;
    } else if (1 == remainder) {
      number = (7 * number + 2) / 3;
    } else {
      number = (number - 2) / 3;
    }
  }
}

