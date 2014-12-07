/**
 * My version of the Naive Solution from 
 * https://github.com/noahvanhoucke/HelpingSantasHelpers
 * 
 * Written by Rick Bischoff
 * but I claim no license or copyright.
 * https://github.com/rdbisch/Santa2014
**/
#ifndef _ELF_H
#define _ELF_H

#include <algorithm>
using std::max;
using std::min;

#include "Toy.h"

class Elf {
public:
    int id;
    double rating;
    int next_available_time;
public:
    // default constructor for containers
    Elf() : id(-1), rating(0.0), next_available_time(-1) { }

    Elf(int ID) : id(ID), rating(1.0), next_available_time(540) { }

    /** 
     * Update the elf's next_available_time and productivity ratings
     */
    int update_elf(int start_minute, int duration) {
        int real_duration = (int)ceil(duration / rating);
        int end_minute = start_minute + real_duration;

        tuple<int, int> res = getSanctionedBreakdown(start_minute, real_duration);

        next_available_time = applyRestingPeriod(end_minute, std::get<1>(res));
        rating = max(0.25, min(4.0, rating * pow(1.02, std::get<0>(res) / 60.0) * pow(0.90, std::get<1>(res) / 60.0)));

        return real_duration;
    }

    int expectedDuration(const Toy& T) const {
        return (int)ceil(T.duration / rating);
    }

    string toString() const {
        stringstream out;
        out << "(id: " << id << " rating: " << rating << " next: " << timeToString(next_available_time) << ")";
        return out.str();
    }

    bool operator<(const Elf& f) const {
        if ( next_available_time < f.next_available_time ) return false;
        else if ( next_available_time == f.next_available_time ) return id > f.id;
        else return true;
    }
};

#endif
