/**
 * My version of the Naive Solution from 
 * https://github.com/noahvanhoucke/HelpingSantasHelpers
 * 
 * Written by Rick Bischoff
 * but I claim no license or copyright.
 * https://github.com/rdbisch/Santa2014
**/

#ifndef _TOY_H
#define _TOY_H

#include <string>
#include <sstream>
#include <algorithm>

#include "Hours.h"

using std::string;
using std::stringstream;

/**
 * This object is just a handy
 * container for Toys and doesn't 
 * really do anything else.
 */
class Toy {
public:
    int id;
    int arrivalTime;
    int duration;

public:
    // default constructor for containers
    Toy() : id(-1), arrivalTime(-1), duration(-1) { }

    Toy(std::string line) {
        int year, month, day, hour, minute;
        std::replace( line.begin(), line.end(), ',', ' ');
        std::stringstream ss(line);
        ss >> id >> year >> month >> day >> hour >> minute >> duration;
        arrivalTime = stringToTime(year, month, day, hour, minute);
    }

    string toString() const {
        stringstream out;
        out << "(toy " << id << " arrival " << timeToString(arrivalTime) << " duration " << duration << ")";
        return out.str();
    }

    bool operator<(const Toy& t) const {
        return id < t.id;
    }
};

#endif
