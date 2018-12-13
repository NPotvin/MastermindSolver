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
        while (!master->isGameFinished()) {
            MPI_Gather(playersGuesses, sizeof(Guess), MPI_BYTE, playersGuesses, sizeof(Guess), MPI_BYTE, 0, MPI_COMM_WORLD);
            Result res(master->manageGuesses(&(playersGuesses[1]), static_cast<const size_t &>(tot_proc - 1)));
            MPI_Bcast(&res, sizeof(Result),
                      MPI_BYTE, 0, MPI_COMM_WORLD);

        }
    }
    else {
        auto begin(static_cast<size_t>(rank-1)*(GUESS_NUM())/(tot_proc-1));
        auto end(static_cast<size_t>(rank)*(GUESS_NUM())/(tot_proc-1));
        if (rank-1 < GUESS_NUM()%(tot_proc-1)) {
            begin += rank-1;
            end += rank;
        }
        else {
            begin += GUESS_NUM()%(tot_proc-1);
            end += end == GUESS_NUM() ? 0 : GUESS_NUM()%(tot_proc-1);
        }
        challenger = new Challenger(begin, end);
        while (not challenger->empty()) {
            Guess guess(challenger->getGuess());
            Result res;
            std::cout<< "Challenger "<<rank<<" sending guess!" << std::endl;
            MPI_Gather(&guess, sizeof(Guess), MPI_BYTE,
                       playersGuesses, sizeof(Guess) , MPI_BYTE,
                       0, MPI_COMM_WORLD);
            MPI_Bcast(&res, sizeof(Result),
                      MPI_BYTE, 0, MPI_COMM_WORLD);
            challenger->updatePlausibleGuesses(res);
        }
    }
    MPI_Finalize();


/*
    while (!done) {
      if(rank) {
        playersGuesses[rank] = challenger->getGuess();
      }
      if (!rank) std::cout<< "Collecting guesses!" << std::endl;
      MPI_Gather(playersGuesses, sizeof(Guess), MPI_BYTE,
                 (void*) playersGuesses, sizeof(Guess) , MPI_BYTE,
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
     /**/
}
