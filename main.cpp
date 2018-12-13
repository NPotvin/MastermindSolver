#include <iostream>
#include <mpi.h>
#include "utils/Guess.h"
#include "utils/Result.h"
#include "players/Challenger.h"
#include "players/GameMaster.h"


int main(int argc, char** argv) {
    int totProc, rank;
    Guess *playersGuesses(nullptr);
    bool *status(nullptr);

    srand(static_cast<unsigned int>(time(nullptr)));

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &totProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (totProc <= 1) {
        std::cout << "Master can't play alone!" << std::endl << "At least 2 processes must be specified" << std::endl;
        MPI_Finalize();
        return 0;
    }

    if (!rank) {
        unsigned guessCount(0);
        GameMaster master;
        master.printSol();
        playersGuesses = new Guess[totProc];
        status = new bool[totProc];
        std::vector<Guess> guesses(0);
        guesses.reserve(static_cast<size_t>(totProc - 1));
        while (!master.isGameFinished()) {
            guessCount++;
            guesses.clear();
            std::cout << "Round " << guessCount << " :" << std::endl;
            std::cout << "\tCollecting players' guesses..." << std::endl;
            MPI_Gather(playersGuesses, sizeof(Guess), MPI_BYTE,
                       playersGuesses, sizeof(Guess), MPI_BYTE,
                       0, MPI_COMM_WORLD);
            MPI_Gather(status, 1, MPI_CXX_BOOL,
                       status, 1, MPI_CXX_BOOL,
                       0, MPI_COMM_WORLD);
            for (size_t i(1); i<totProc; ++i)
                if (status[i])
                    guesses.push_back(playersGuesses[i]);
                else
                    std::cout<<"\t\tChallenger "<<i<<" is out of guesses"<<std::endl;
            Result res(master.manageGuesses(guesses));
            std::cout << "\tGuess to be evaluated is : ";
            res.getGuess().print();
            std::cout << "\tIt has " << res.getPerfect()
                      << " dots in both correct color and position, and "
                      << res.getColorOnly() << " correct colors only" << std::endl;
            MPI_Bcast(&res, sizeof(Result),
                      MPI_BYTE, 0, MPI_COMM_WORLD);
            std::cout<<std::endl;
        }
        std::cout << "Players found the solution in " << guessCount << " rounds" << std::endl;
    }
    else {
        auto begin(static_cast<size_t>(rank-1)*(GUESS_NUM())/(totProc-1));
        auto end(static_cast<size_t>(rank)*(GUESS_NUM())/(totProc-1));
        if (rank-1 < GUESS_NUM()%(totProc-1)) {
            begin += rank-1;
            end += rank;
        }
        else {
            begin += GUESS_NUM()%(totProc-1);
            end += end == GUESS_NUM() ? 0 : GUESS_NUM()%(totProc-1);
        }
        Challenger challenger(begin, end);
        bool running(true), done(false);
        while (!done) {
            Guess guess;
            Result res;
            if (running) {
                guess = challenger.getGuess();
            }
            MPI_Gather(&guess, sizeof(Guess), MPI_BYTE,
                       playersGuesses, sizeof(Guess) , MPI_BYTE,
                       0, MPI_COMM_WORLD);
            MPI_Gather(&running, 1, MPI_CXX_BOOL,
                       status, 1, MPI_CXX_BOOL,
                       0, MPI_COMM_WORLD);
            MPI_Bcast(&res, sizeof(Result),
                      MPI_BYTE, 0, MPI_COMM_WORLD);
            if (running) {
                challenger.updatePlausibleGuesses(res);
                running = !challenger.empty();
            }
            done = res.getPerfect() == GUESS_SIZE();
        }
    }
    MPI_Finalize();
}
