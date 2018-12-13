#include <iostream>
#include <mpi.h>
#include "utils/Guess.h"
#include "utils/Result.h"
#include "players/Challenger.h"
#include "players/GameMaster.h"


int main(int argc, char** argv) {
    int guess_count, tot_proc, rank;
    bool done = false;
    Guess *playersGuesses = nullptr;
    Result evaluated_guess;
    GameMaster *master=nullptr;
    Challenger *challenger=nullptr;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &tot_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (tot_proc <= 1) {
      std::cout << "Master can't play alone!" << std::endl << "At least 2 processes must be specified" << std::endl;
      MPI_Finalize();
      return 0;
    }

    if (!rank) {
      master = new GameMaster;
      playersGuesses = new Guess[tot_proc];
    }
    else{
      challenger = new Challenger;
      playersGuesses = new Guess;
    }

    while (!done) {
      if(rank) {
        playersGuesses[0] = challenger->getGuess();
      }
      if (!rank) std::cout<< "Collecting guesses!" << std::endl;
      MPI_Gather((void*) playersGuesses, sizeof(Guess), MPI_BYTE,
                 (void*) playersGuesses, sizeof(Guess)*(tot_proc) , MPI_BYTE,
                 0, MPI_COMM_WORLD);
      ++guess_count;
      if(!rank) {
        std::cout << "Evaluating random guess: " << std::endl ;
        evaluated_guess = master->manageGuesses(&(playersGuesses[1]), static_cast<const size_t>(tot_proc - 1));
        done = master->isGameFinished();
      }
      MPI_Bcast((void*) &evaluated_guess, sizeof(Result),
                MPI_BYTE, 0, MPI_COMM_WORLD);
      challenger->updatePlausibleGuesses(evaluated_guess);
      done = evaluated_guess.getPerfect() == GUESS_SIZE() ;
     }
}
