/**
 * My version of the Naive Solution from 
 * https://github.com/noahvanhoucke/HelpingSantasHelpers
 * 
 * Written by Rick Bischoff
 * but I claim no license or copyright.
 * https://github.com/rdbisch/Santa2014
**/

#include "Score.h"
#include "Elf.h"
#include "Toy.h"
#include "Hours.h"

#include <fstream>
#include <map>
#include <iostream>
using std::ifstream;
using std::map;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

double score(int num_elves, string toysPath) {
    map<int, Toy> toys_todo;
    string line;
    ifstream inToys(toysPath);
    std::getline(inToys, line);
    while (std::getline(inToys, line)) {
        Toy t(line);
        toys_todo[t.id] = t;
    }

    map<int, Elf> elves;
    std::getline(cin, line);
    int maxTime = 0;
    while (std::getline(cin, line)) {
        int toyId, elfId, year, month, day, hour, minute, duration;
        std::replace( line.begin(), line.end(), ',', ' ');
        std::stringstream ss(line);
        ss >> toyId >> elfId >> year >> month >> day >> hour >> minute >> duration;

        auto toyIt = toys_todo.find(toyId);

        if (toyIt == toys_todo.end()) {
            cerr << "Request to build toy ID " << toyId << " which does not exist "
                << "in the database.";
            std::exit(1);
        }

        auto elfIt = elves.find(elfId);
        if ( elfIt == elves.end() ) {
            elves[elfId] = Elf(elfId);
            elfIt = elves.find(elfId);
        }

        Elf& E = elfIt->second;
        Toy& T = toyIt->second;
        
        int time = stringToTime(year, month, day, hour, minute);

        if ( E.next_available_time > time ) {
            cerr << "Request for Elf id " << E.id << " at time " << timeToString(time)
                << " but he is not available until " << timeToString(E.next_available_time)
                << ". This error occured during toy " << toyId << endl;
            std::exit(1);
        }

        if ( duration < E.expectedDuration(T)) {
            cerr << "Duration (" << duration << ") supplied for Toy " << T.toString()
                << " for Elf(" << E.toString() << ") is less than the elf "
                << "is expected to need (" << E.expectedDuration(T) << ")."
                << endl;
            std::exit(1);
        }

        maxTime = max(maxTime, time + E.expectedDuration(T));
        E.update_elf(time, T.duration);
        toys_todo.erase(toyIt);
    }

    if (toys_todo.size() > 0) {
        cerr << "Not all toys have been completed.  There are " << toys_todo.size()
            << " toys remaining, the first of which is " << (toys_todo.begin()->second.toString())
            << endl;
        std::exit(1);
    }

    if ((int)elves.size() > num_elves) {
        cerr << "Program was ran with a max number of elves of " << num_elves
            << " but you used " << elves.size() << "." << endl;
        std::exit(1);
    }

    return maxTime * log(1.0 + elves.size());
}

