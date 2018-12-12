#ifndef MASTERMINDSOLVER_GUESS_H
#define MASTERMINDSOLVER_GUESS_H

#include <cstddef>
#include "Color.h"
#include "constants.h"
#include <vector>
#include "Similarity.h"

class Guess {
private:

    std::vector<Color> _guess;
    std::vector<unsigned> _colorCount;

    const unsigned& getColorCount(const size_t& i) const {return _colorCount[i];}

public:

    Guess() : _guess(0), _colorCount(0) {}

    explicit Guess(const size_t& number) : _guess(0), _colorCount(N_COLORS()) {
        _guess.reserve(GUESS_SIZE());
        for (auto num(static_cast<unsigned>(number)); _guess.size() < GUESS_SIZE(); num /= N_COLORS())
            _guess.emplace_back(Color(num%N_COLORS()));
    }

    explicit Guess(std::vector<Color> vec) : _guess(std::move(vec)), _colorCount(N_COLORS()) {
        if (_guess.size() != GUESS_SIZE())
            ;// throw error
        else {
            for (size_t i(0); i < N_COLORS(); ++i) {
                ++(_colorCount[vec[i].getColorID()]);
            }
        }
    }

    Guess(const Guess& other) = default;

    const bool operator==(const Guess& other) const {return (_guess == other._guess);}
    const Color& operator[](const size_t& i) const {return _guess[i % _guess.size()];}
    const unsigned& getColorCount(const Color& color) const {return _colorCount[color.getColorID()];}
    const Similarity computeDistanceTo(const Guess& other) const;
};


#endif //MASTERMINDSOLVER_GUESS_H
