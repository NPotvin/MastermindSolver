#ifndef MASTERMINDSOLVER_GUESS_H
#define MASTERMINDSOLVER_GUESS_H

#include <cstddef>
#include "Color.h"
#include "constants.h"
#include <vector>
#define MIN(X,Y)  ((X) < (Y) ? (X) : (Y))


typedef struct Similarity {
  const unsigned perfect;
  const unsigned colorOnly;
} Similarity;

class Guess {
private:

    std::vector<Color> _guess;
    std::vector<unsigned> _colorCount;

public:

    Guess() : _guess(GUESS_SIZE, 0), _colorCount(N_COLORS, 0) {}

    explicit Guess(std::vector<Color> vec) : _guess(std::move(vec)), _colorCount(N_COLORS, 0) {
      if (_guess.size() != GUESS_SIZE)
        ;// throw error
      else {
        for (unsigned i = 0 ; i < N_COLORS ; ++i) {
          ++(_colorCount[vec[i].getColorID()]);
        }
      }
    }

    explicit Guess(const Guess& other) : _guess(std::move(other._guess)), _colorCount(std::move(other._colorCount)) {}

    const Color& operator[](const size_t& i) const {
        return _guess[i % _guess.size()];
    }


    const unsigned getColorCount(Color color) {
      return _colorCount[color.getColorID()] ;
    }

    const Similarity computeDistanceTo(const Guess& other) const ;


};


#endif //MASTERMINDSOLVER_GUESS_H
