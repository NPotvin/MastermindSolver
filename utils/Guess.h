#ifndef MASTERMINDSOLVER_GUESS_H
#define MASTERMINDSOLVER_GUESS_H

#include "Color.h"
#include "constants.h"
#include "Similarity.h"

#include <iostream>


class Guess {
private:

    Color _guess[GUESS_SIZE()];
    unsigned _colorCount[N_COLORS()];

    const unsigned& getColorCount(const size_t& i) const {return _colorCount[i];}

public:

    Guess() : _guess{Color()}, _colorCount{0} {}

    /**
     * This constructor initialize a Guess from a number.
     * The Guess is considered as a number in base equal to
     * the number of possible colors while the given number is
     * a base ten number.
     *
     * @param number : the equivalent base ten number of this guess
     */
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

    const bool operator==(const Guess& other) const {
        for (size_t i(0); i<GUESS_SIZE(); ++i)
            if (_guess[i] != other._guess[i])
                return false;
        return true;
    }
    const Color& operator[](const size_t& i) const {return _guess[i % GUESS_SIZE()];}

    /**
     * This method computes the similarity between this Guess and another.
     *
     * @param other : a reference to a Guess object
     * @return a Similarity object
     */
    const Similarity computeDistanceTo(const Guess& other) const;

    void print() const {
        for (const Color& guess : _guess)
            std::cout << guess.getColorID() << " ";
        std::cout << std::endl;
    }
};


#endif //MASTERMINDSOLVER_GUESS_H
