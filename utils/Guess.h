#ifndef MASTERMINDSOLVER_GUESS_H
#define MASTERMINDSOLVER_GUESS_H

#include <cstddef>
#include "Color.h"
#include "constants.h"
#include <vector>
#define MIN(X,Y)  ((X) < (Y) ? (X) : (Y))


struct Similarity {
  const unsigned perfect;
  const unsigned colorOnly;

  explicit Similarity() : perfect(0), colorOnly(0) {};
  explicit Similarity(unsigned p, unsigned co) : perfect(p), colorOnly(co) {}
  explicit Similarity(const Similarity& other) : perfect(other.perfect), colorOnly(other.colorOnly) {}
};

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


    bool operator==(const Guess& other) const {
      return (_guess == other._guess);
    }
    const Color& operator[](const size_t& i) const {
        return _guess[i % _guess.size()];
    }


    const unsigned getColorCount(Color color) {
      return _colorCount[color.getColorID()] ;
    }

    const Similarity computeDistanceTo(const Guess& other) const ;


};


#endif //MASTERMINDSOLVER_GUESS_H
