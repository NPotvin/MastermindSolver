#ifndef MASTERMINDSOLVER_COLOR_H
#define MASTERMINDSOLVER_COLOR_H

#include <vector>

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

    static unsigned _colorNum;
    static std::vector<unsigned> _masks;

    static unsigned tmpMask;

public:

    static void computeColorMasks(const size_t& playerNum);

    static unsigned const& getColorMask(const size_t& i) {
        /*
        if (_masks.empty())
            ;// TODO throw error, masks have not been generated
        return _masks.at(i);
        // TODO replace at() by [] (sligthly faster but no bound check)
         */
        return tmpMask;
    }

    static void setColorNum(const unsigned &number) {
        _colorNum = number;
    }

    static const unsigned& getColorNum() {return _colorNum;}
};

unsigned Color::_colorNum = 10;
unsigned Color::tmpMask = 0x00000000;


#endif //MASTERMINDSOLVER_COLOR_H
