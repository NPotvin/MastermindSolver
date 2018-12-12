#ifndef MASTERMINDSOLVER_GUESS_H
#define MASTERMINDSOLVER_GUESS_H

#include <cstddef>
#include "Color.h"

class Guess {
private:

    // colors are encoded on 8 bits, since a guess is 4 colors, we need 32 bits
    // (it is explicit in order to avoid platform dependent size to mess up things)
    const unsigned _guess : 32;
    static Color _color;

public:

    Guess() : _guess(0) {}
    Guess(const unsigned char& color1, const unsigned char& color2,
            const unsigned char& color3, const unsigned char& color4) :
            _guess(color1|color2<<8|color3<<16|color4<<24) {
        if (color1> Color::getColorNum() ||
            color2> Color::getColorNum() ||
            color3> Color::getColorNum() ||
            color4> Color::getColorNum())
            ;// TODO throw error, we received a non existing color
    }

    static void setColor(const Color& color) {_color = color;}

    const unsigned char operator[](const size_t& i) const {
        if (i<0 || i>3)
            ;// TODO throw error out of bounds
        return static_cast<const unsigned char>(0x000000ff&(_guess>>i*8));
    }


};


#endif //MASTERMINDSOLVER_GUESS_H
