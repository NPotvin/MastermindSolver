#ifndef MASTERMINDSOLVER_GUESS_H
#define MASTERMINDSOLVER_GUESS_H

#include "Color.h"
#include "constants.h"
#include "Similarity.h"

#include <cstddef>
#include <vector>
#include <iostream>
#include <stdlib.h>

class Guess {
private:

    Color _guess[GUESS_SIZE()];
    unsigned _colorCount[N_COLORS()];

    const unsigned& getColorCount(const size_t& i) const {return _colorCount[i];}

public:

    Guess() : _guess{Color()}, _colorCount{0} {
        unsigned color;
        for (size_t i(0); i < GUESS_SIZE(); ++i) {
          color = rand() % N_COLORS() ;
          _guess[i] = Color(color);
          ++(_colorCount[color]);
        }
    }

    explicit Guess(const size_t& number) : _guess{Color()}, _colorCount{0} {
        auto num(static_cast<unsigned>(number));
        unsigned color;
        for (size_t i(0); i < GUESS_SIZE(); ++i, num /= N_COLORS()) {
          color = num % N_COLORS();
          _guess[i] = Color(color);
          ++(_colorCount[color]);
        }
    }

    Guess(const Guess& other) = default;

    const bool operator==(const Guess& other) const {return (_guess == other._guess);}
    const Color& operator[](const size_t& i) const {return _guess[i % GUESS_SIZE()];}
    const unsigned& getColorCount(const Color& color) const {return _colorCount[color.getColorID()];}
    const Similarity computeDistanceTo(const Guess& other) const;
};


#endif //MASTERMINDSOLVER_GUESS_H
