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

    // initializing variables
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &totProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // checking the number of processes
    if (totProc <= 1) {
        std::cout << "Master can't play alone!" << std::endl << "At least 2 processes must be specified" << std::endl;
        MPI_Finalize();
        return 0;
    }

    if (!rank) {
        // Here is the Game master code
        unsigned guessCount(0);
        GameMaster master;
        master.printSol();
        playersGuesses = new Guess[totProc];
        status = new bool[totProc];
        std::vector<Guess> guesses(static_cast<size_t>(totProc - 1));
        while (!master.isGameFinished()) {
            guessCount++;
            guesses.clear();
            std::cout << "Round " << guessCount << " :" << std::endl;
            std::cout << "\tCollecting players' guesses..." << std::endl;
            MPI_Gather(playersGuesses, sizeof(Guess), MPI_BYTE,
                       playersGuesses, sizeof(Guess), MPI_BYTE, 0, MPI_COMM_WORLD);
            MPI_Gather(status, 1, MPI_CXX_BOOL, status, 1, MPI_CXX_BOOL, 0, MPI_COMM_WORLD);
            // We collect only the guesses of challengers still in the game
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
            // the result is broadcast to all challengers
            MPI_Bcast(&res, sizeof(Result), MPI_BYTE, 0, MPI_COMM_WORLD);
            std::cout<<std::endl;
        }
        delete[] playersGuesses;
        delete[] status;
        status = nullptr;
        playersGuesses = nullptr;
        std::cout << "Players found the solution in " << guessCount << " rounds" << std::endl;
    }
    else {
        // Here is the challenger code
        // begin and end are computed such that each guess list has at most one guess more or less than any other
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
        // with these two values, a challenger knows the guesses it should generate
        Challenger challenger(begin, end);
        // running is true if the challenger can still play
        // done is true if the game is finished (the solution has been found)
        bool running(true), done(false);
        while (!done) {
            Guess guess;
            Result res;
            if (running) {
                guess = challenger.getGuess();
            }
            // sending the challenger guess, or the default guess
            MPI_Gather(&guess, sizeof(Guess), MPI_BYTE,
                       playersGuesses, sizeof(Guess) , MPI_BYTE, 0, MPI_COMM_WORLD);
            // sending the challenger status (playing or not)
            MPI_Gather(&running, 1, MPI_CXX_BOOL, status, 1, MPI_CXX_BOOL, 0, MPI_COMM_WORLD);
            // receiving the result of this turn
            MPI_Bcast(&res, sizeof(Result), MPI_BYTE, 0, MPI_COMM_WORLD);
            // use res to update the challenger, its status and the state of the game
            if (running) {
                challenger.updatePlausibleGuesses(res);
                running = !challenger.empty();
            }
            done = res.getPerfect() == GUESS_SIZE();
        }
    }
    MPI_Finalize();
}
