/**
 * My version of the Naive Solution from 
 * https://github.com/noahvanhoucke/HelpingSantasHelpers
 * 
 * Written by Rick Bischoff
 * but I claim no license or copyright.
 * https://github.com/rdbisch/Santa2014
**/
#include "Score.h"
#include "Naive.h"

#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;

int main(int argc, char** argv) {
    init_startTime();

    if ( argc < 3 ) {
usage_message:
        cerr << "Usage:\n\ta.out (--score) [n] [toys]\n\n"
            << "\t--score\tIf present will score the submission on stdin.  If not will produce naive solution.\n"
            << "\t[n]\tinteger number of elves\n"
            << "\t[toys]\tPath to list of toys.\n";
        std::exit(1);
    }

    if ( strcmp(argv[1], "--score") == 0 ) {
        if (argc < 4) goto usage_message;
        int n = atoi(argv[2]);
        string toys = string(argv[3]);
        cout << std::setprecision(15) << score( n, toys ) << endl;
    } else {
        NaiveSolution e( atoi(argv[1]), string(argv[2]) );
    }
    return 0;
}

