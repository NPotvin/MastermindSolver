#ifndef MASTERMIND_CONSTANTS
#define MASTERMIND_CONSTANTS

#include <cmath>

//constexpr unsigned GUESS_SIZE(){return 4;}
//constexpr unsigned N_COLORS(){return 10;}
constexpr unsigned GUESS_SIZE(){return 2;}
constexpr unsigned N_COLORS(){return 3;}
constexpr unsigned GUESS_NUM(){return static_cast<unsigned>(std::pow(N_COLORS(), GUESS_SIZE()));}

#endif
