#ifndef MASTERMINDSOLVER_COLOR_H
#define MASTERMINDSOLVER_COLOR_H

#include <vector>
#include "constants.h"

class Color {
private:

    static const unsigned _nColors = N_COLORS();
    unsigned _colorId;

public:

    Color() : _colorId(0) {}
    explicit Color(unsigned id) : _colorId(id % _nColors) {}

    const unsigned& getColorID() const {return _colorId;}
    const bool operator== (const Color& other) const {return (_colorId == other.getColorID());}
};


#endif //MASTERMINDSOLVER_COLOR_H
