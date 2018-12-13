#include <iostream>
#include <mpi.h>
#include "utils/Guess.h"
#include "utils/Result.h"
#include "players/Challenger.h"
#include "players/GameMaster.h"


int main(int argc, char** argv) {
    /*
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
*/
    const size_t numPlayers(4);
    GameMaster master;
    std::vector<Challenger> challengers(0);
    challengers.reserve(numPlayers);
    for (size_t i(0), j(0); i < numPlayers; ++i) {
        const size_t begin(i*(GUESS_NUM()/numPlayers)+j);
        if (j<GUESS_NUM()%numPlayers) j++;
        const size_t end((i+1)*(GUESS_NUM()/numPlayers)+j);
        challengers.emplace_back(begin, end);
    }
    size_t TESTTMP(0);
    do {
        std::vector<Guess> guesses;
        guesses.reserve(challengers.size());
        for (const Challenger& challenger : challengers)
            if (!challenger.empty())
                guesses.emplace_back(challenger.getGuess());
        Result res(master.manageGuesses(guesses));
        for (Challenger& challenger : challengers)
            challenger.updatePlausibleGuesses(res);
        TESTTMP++;
        std::cout<<"_____________________________________________________________________________________"<<std::endl;
        std::cout<<"_____________________________________________________________________________________"<<std::endl;
    //} while (TESTTMP<3);
    } while (!master.isGameFinished());
}
