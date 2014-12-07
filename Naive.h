/**
 * My version of the Naive Solution from 
 * https://github.com/noahvanhoucke/HelpingSantasHelpers
 * 
 * Written by Rick Bischoff
 * but I claim no license or copyright.
 * https://github.com/rdbisch/Santa2014
**/

#ifndef _NAIVE_H
#define _NAIVE_H

#include "Elf.h"
#include "Toy.h"
#include "Hours.h"

#include <algorithm>
#include <queue>
#include <iostream>
#include <fstream>
using std::ifstream;
using std::cout;
using std::endl;
using std::priority_queue;

class NaiveSolution {
    priority_queue<Elf> elves;

public:
    NaiveSolution(int n, string toyFile) {
        for (int i = 0; i < n; ++i) elves.push(Elf(i+1));

        ifstream inToys(toyFile);
        string line;
       
        cout << "ToyId,ElfId,StartTime,Duration" << endl;
        getline(inToys, line);     //skip header

        while (std::getline(inToys, line)) {
            Toy T(line);

            Elf E = elves.top();
            elves.pop();

            int time = std::max(T.arrivalTime, E.next_available_time);
            int actual_duration = E.update_elf(time, T.duration);

            cout << T.id << "," << E.id << "," << timeToString(time) << "," << actual_duration << endl;
            elves.push(E);
        }
    }
};

#endif
