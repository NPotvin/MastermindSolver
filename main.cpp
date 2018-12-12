#include <iostream>
#include <mpi.h>
#include "utils/Guess.h"
#include "players/Challenger.h"
#include "players/GameMaster.h"


int main(int argc, char** argv) {
    MPI_UNSIGNED rank, tot_proc ;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMMON_WORLD, &ntot_proc)
    MPI_Comm_rank(MPI_COMMON_WORLD, &rank)


    if (tot_proc <= 1) {
      std::cout << "Master can't play alone!" << std::endl;
      MPI_Abort(MPI_COMMON_WORLD, 1);
    }
    else {
      if (!rank) {
        GameMaster master;
        // select a random solution
        // receives each turn the guesses of nodes, evaluates them and answers to origin
        // if guess is correct, 
      }
      else{
        Challenger challenger;
        // initialize guesses according to ID
        // makes guess each turn, and sends result to other nodes
        // update lsit of guesses accordingly
      }
    }

    Guess test(1,2,3,4);
    std::cout << (unsigned)test[0] << (unsigned)test[1] << (unsigned)test[2] << (unsigned)test[3] << std::endl;
    return 0;
}
