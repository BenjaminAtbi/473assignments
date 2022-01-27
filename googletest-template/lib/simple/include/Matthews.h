
#pragma  once

#include <cstdint>


namespace sequence {


enum class MatthewsOutcome {
  ZERO,
  MINUS_ONE_CYCLE,
  MINUS_TWO_CYCLE,
};


MatthewsOutcome
checkMatthewsOutcome(int64_t startingNumber);


}


