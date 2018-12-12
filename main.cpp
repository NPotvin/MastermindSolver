#include <iostream>
#include "utils/Guess.h"

int main() {
    Guess test(1,2,3,4);
    std::cout << (unsigned)test[0] << (unsigned)test[1] << (unsigned)test[2] << (unsigned)test[3] << std::endl;
    return 0;
}