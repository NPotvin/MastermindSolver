#include "Guess.h"


const Similarity Guess::computeDistanceTo(const Guess& other) const {
  unsigned perfect = 0, colorOnly = 0;

  for (int i = 0 ; i < N_COLORS ; ++i) {
    colorOnly += MIN(_colorCount[i], other.getColorCount(i));
  }
  for (int i = 0 ; i < GUESS_SIZE ; ++i){
    if (_guess[i] == other[i]) {
      ++perfect;
      --colorOnly;
    }
  }
  Similarity res = {
    perfect,
    colorOnly,
  }
  return res;
}
