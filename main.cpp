#include <iostream>
#include <mpi.h>
#include "utils/Guess.h"
#include "utils/Result.h"
#include "players/Challenger.h"
#include "players/GameMaster.h"


int main(int argc, char** argv) {
    int tot_proc, rank;
    bool done(false);
    Guess *playersGuesses(nullptr);
    bool *status(nullptr);

    srand(static_cast<unsigned int>(time(nullptr)));

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &tot_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (tot_proc <= 1) {
        std::cout << "Master can't play alone!" << std::endl << "At least 2 processes must be specified" << std::endl;
        MPI_Finalize();
        return 0;
    }

    if (!rank) {
        GameMaster master;
        master.printSol();
        playersGuesses = new Guess[tot_proc];
        status = new bool[tot_proc];
        std::vector<Guess> guesses(0);
        guesses.reserve(static_cast<size_t>(tot_proc - 1));
        while (!master.isGameFinished()) {
            guesses.clear();
            MPI_Gather(playersGuesses, sizeof(Guess), MPI_BYTE,
                       playersGuesses, sizeof(Guess), MPI_BYTE,
                       0, MPI_COMM_WORLD);
            MPI_Gather(status, 1, MPI_CXX_BOOL,
                       status, 1, MPI_CXX_BOOL,
                       0, MPI_COMM_WORLD);
            for (size_t i(1); i<tot_proc; ++i)
                if (status[i])
                    guesses.push_back(playersGuesses[i]);
            Result res(master.manageGuesses(guesses));
            MPI_Bcast(&res, sizeof(Result),
                      MPI_BYTE, 0, MPI_COMM_WORLD);
        }
        std::cout<<"game finished"<<std::endl;
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
        Challenger challenger(begin, end);
        bool running(true);
        while (not challenger.empty() && ! done) {
            Guess guess(challenger.getGuess());
            Result res;
            std::cout<< "Challenger "<<rank<<" sending guess!" << std::endl;
            MPI_Gather(&guess, sizeof(Guess), MPI_BYTE,
                       playersGuesses, sizeof(Guess) , MPI_BYTE,
                       0, MPI_COMM_WORLD);
            MPI_Gather(&running, 1, MPI_CXX_BOOL,
                       status, 1, MPI_CXX_BOOL,
                       0, MPI_COMM_WORLD);
            MPI_Bcast(&res, sizeof(Result),
                      MPI_BYTE, 0, MPI_COMM_WORLD);
            done = res.getPerfect() == GUESS_SIZE() ;
            challenger.updatePlausibleGuesses(res);
        }
        std::cout<<"challenger "<<rank<<" out"<<std::endl;
        running = false;
        while (!done) {
            Guess guess;
            Result res;
            MPI_Gather(&guess, sizeof(Guess), MPI_BYTE,
                       playersGuesses, sizeof(Guess) , MPI_BYTE,
                       0, MPI_COMM_WORLD);
            MPI_Gather(&running, sizeof(bool), MPI_CXX_BOOL,
                       status, sizeof(bool), MPI_CXX_BOOL,
                       0, MPI_COMM_WORLD);
            MPI_Bcast(&res, sizeof(Result),
                      MPI_BYTE, 0, MPI_COMM_WORLD);
            done = res.getPerfect() == GUESS_SIZE() ;
        }

    }
    MPI_Finalize();
}
