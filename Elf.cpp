/**
 * My version of the Naive Solution from 
 * https://github.com/noahvanhoucke/HelpingSantasHelpers
 * 
 * Written by Rick Bischoff
 * but I claim no license or copyright.
 * https://github.com/rdbisch/Santa2014
**/
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <tuple>
#include <utility>
#include <vector>
#include <algorithm>
#include <time.h>
#include <string.h>
using namespace std;

#define MID (60*24)

struct tm startTime;
time_t startTime_t;

void init_startTime() {
    memset(&startTime, 0, sizeof(struct tm));
    startTime.tm_year = 2014 - 1900;
    startTime.tm_mon = 0;
    startTime.tm_mday = 1;
    startTime.tm_hour = 0;
    startTime.tm_min = 0;
    startTime_t = timegm(&startTime);
}

/**
 * Poorly named function that converts the YY MM DD HH mm integers
 * into an integer number of minutes after 2004/1/1 12:00
 */
int stringToTime(int year, int month, int day, int hour, int minute) {
    struct tm nowtime;
    memset(&nowtime, 0, sizeof(struct tm));
    nowtime.tm_year = year - 1900;
    nowtime.tm_mon = month - 1;
    nowtime.tm_mday = day;
    nowtime.tm_hour = hour;
    nowtime.tm_min = minute;

    time_t nowtime_t = timegm(&nowtime);
    return (nowtime_t - startTime_t) / 60;
}

/** 
 * The inverse of the above...if they above actually
 * operated on strings that is.
 * 
 * Converts integer number of minutes past start time into
 * the YY MM DD HH mm format.
 */
string timeToString(int time) {
    time_t afterTime = timegm(&startTime) + time*60ULL;
    struct tm *after = gmtime(&afterTime);
    char output[17];
    strftime(output, sizeof(output), "%Y %-m %-d %-H %-M", after);
    return string(output);
}

/**
 * Returns true if "minute" is in the sanctioned time frame.
 */
bool isSanctionedTime(int minute) {
    return ((minute - 540) % MID) < 600;
}

/**
 * Increments the time to the next "fence" of sanctioned/vs. unsanctioned
 */
int incrementToNextFence(int minute) {

    int day = (minute / (MID));
    int dayM = day * (MID);

    if (minute > (dayM + 60*18 + 59))        
        return dayM + (MID) + 60*9;
    else if (minute < (dayM + 60*9))
        return dayM + 60*9;
    else
        return dayM + 60*19 ;
}

/**
 * Returns a pair of numbers that represent the sanctioned vs. 
 * unsanctioned breakdown of time.
 *
 * TODO: Optimize this--carbon copy of python code right now.
 */
std::tuple<int, int> getSanctionedBreakdown(int startMinute, int duration) {
    int S = 0;
    int U = 0;

    int full_days = duration / MID;
    S = full_days * (10*60);
    U = full_days * (14*60);
    int remainder = startMinute + full_days * MID;
    for (int i = remainder; i < (startMinute+duration); ++i) {
        if (isSanctionedTime(i)) S += 1;
        else U += 1;
    }
    return std::tuple<int, int>(S, U);
}

/**
 * Applies the resting period to the current time
 * with special caveats for new rules
 */
int applyRestingPeriod(int current, int unsanctioned) {
    int loop = 0;

    if ( unsanctioned == 0 ) {
        if ((current % MID) == 1140) return incrementToNextFence(current);
        else return current;
    }

    do { 
        ++loop;
        /* If current is not sanctioned, move to next sanction time */
        if ( ! isSanctionedTime(current) ) {
            current = incrementToNextFence(current);
            ++loop;
        }

        /* We are now in sanctioned time..  Use rest of time
         * in current working day */
        int stopTime = incrementToNextFence(current);
        int restMinutes = min( stopTime - current, unsanctioned ); 

        current += restMinutes;
        unsanctioned -= restMinutes;
    } while (unsanctioned > 0);

    // Some edge cases can land right on 19:00
    if ( (current % MID) == 1140 ) return incrementToNextFence(current);

    return current;
}

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
};

class Elf {
public:
    int id;
    double rating;
    int next_available_time;
public:
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

    string toString() const {
        stringstream out;
        out << "(id: " << id << " rating: " << rating << " next: " << timeToString(next_available_time) << ")";
        return out.str();
    }

    friend bool operator<(Elf e, Elf f) ;
};

/**
 * Used to make the priority_queue work as first-avaialble
 */
bool operator<(Elf e, Elf f) {
    if ( e.next_available_time < f.next_available_time ) return false;
    else if ( e.next_available_time == f.next_available_time ) return e.id > f.id;
    else return true;
}


/**
 * Really more of a Elf Manager
 */
class Elves {
    priority_queue<Elf> elves;

public:
    Elves(int n, string toyFile) {
        for (int i = 0; i < n; ++i) elves.push(Elf(i+1));

        ifstream inToys(toyFile);
        string line;
       
        cout << "ToyId,ElfId,StartTime,Duration" << endl;
        std::getline(inToys, line);     //skip header

        while (std::getline(inToys, line)) {
            Toy T(line);

            Elf E = elves.top();
            elves.pop();

            int time = std::max(T.arrivalTime, E.next_available_time);
            double rating = E.rating;
            int actual_duration = E.update_elf(time, T.duration);

            cout << T.id << "," << E.id << "," << timeToString(time) << "," << actual_duration << endl;
            elves.push(E);
        }
    }
};

int main(int argc, char** argv) {
    init_startTime();

    if ( argc < 3 ) {
        cerr << "Usage:\n\ta.out [n] [toys]\n\n\t[n]\tinteger number of elves\n"
            << "\t[toys]\tPath to list of toys.\n";
        std::exit(1);
    }

    Elves e = Elves( atoi(argv[1]), string(argv[2]) );
}

