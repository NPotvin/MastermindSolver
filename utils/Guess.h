#ifndef MASTERMINDSOLVER_GUESS_H
#define MASTERMINDSOLVER_GUESS_H

#include <cstddef>
#include "Color.h"
#include "constants.h"
#include <vector>

class Guess {
private:

    // colors are encoded on 8 bits, since a guess is 4 colors, we need 32 bits
    // (it is explicit in order to avoid platform dependent size to mess up things)
    std::vector<Color> _guess;

public:

    Guess() : _guess(GUESS_SIZE, 0) {}
    Guess(const std::vector<Color>& vec){
      if (vec.size() == GUESS_SIZE) _guess(vec)
      else {
        // throw error
      }
    }

    const Color& operator[](const size_t& i) const {
        return _guess[i % _guess.size()];
    }


};


#endif //MASTERMINDSOLVER_GUESS_H
