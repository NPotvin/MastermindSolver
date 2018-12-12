#ifndef MASTERMINDSOLVER_GUESS_H
#define MASTERMINDSOLVER_GUESS_H

#include <cstddef>
#include "Color.h"
#include "constants.h"
#include <vector>


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

    Guess() : _guess(GUESS_SIZE), _colorCount(N_COLORS) {}

    explicit Guess(std::vector<Color> vec) : _guess(std::move(vec)), _colorCount(N_COLORS) {
        if (_guess.size() != GUESS_SIZE)
            ;// throw error
        else {
            for (unsigned i = 0 ; i < N_COLORS ; ++i) {
                ++(_colorCount[vec[i].getColorID()]);
            }
        }
    }

    Guess(const Guess& other) = default;

    bool operator==(const Guess& other) const {return (_guess == other._guess);}
    const Color& operator[](const size_t& i) const {return _guess[i % _guess.size()];}
    const unsigned getColorCount(Color color) const {return _colorCount[color.getColorID()];}
    const Similarity computeDistanceTo(const Guess& other) const ;


};


#endif //MASTERMINDSOLVER_GUESS_H
