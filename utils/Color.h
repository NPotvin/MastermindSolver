#ifndef MASTERMINDSOLVER_COLOR_H
#define MASTERMINDSOLVER_COLOR_H

#include <vector>
#include "constants.h"

class Color {
    /* TODO :
     * We need to have a discussion about the number of player we are going to use (and if that number is fixed
     * or variable). It will determine how we split the work between the challengers and the number of masks
     * we are going to generate. Ideally, the number of challengers should be a multiple of the number of colors
     *
     * for now the mask used allows any combination
     *
     * we should probably rename this class too, since it is not strictly speaking a color
     */
private:

    static const unsigned _nColors;
    unsigned _colorId;

public:

    Color() : _colorId(0) {}
    explicit Color(unsigned id) : _colorId(id % _nColors) {}

    const unsigned& getColorID() const {return _colorId;}
    bool operator== (const Color& other) const {return (_colorId == other.getColorID());}
};

const unsigned Color::_nColors = N_COLORS();

#endif //MASTERMINDSOLVER_COLOR_H
