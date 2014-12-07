/**
 * My version of the Naive Solution from 
 * https://github.com/noahvanhoucke/HelpingSantasHelpers
 * 
 * Written by Rick Bischoff
 * but I claim no license or copyright.
 * https://github.com/rdbisch/Santa2014
**/

#ifndef _HOURS_H
#define _hOURS_H

#include <string>
#include <tuple>

using std::string;
using std::tuple;

#define MID (60*24)

void init_startTime() ;

/**
 * Poorly named function that converts the YY MM DD HH mm integers
 * into an integer number of minutes after 2004/1/1 12:00
 */
int stringToTime(int year, int month, int day, int hour, int minute) ;

/** 
 * The inverse of the above...if they above actually
 * operated on strings that is.
 * 
 * Converts integer number of minutes past start time into
 * the YY MM DD HH mm format.
 */
string timeToString(int time) ;

/**
 * Returns true if "minute" is in the sanctioned time frame.
 */
bool isSanctionedTime(int minute) ;

/**
 * Increments the time to the next "fence" of sanctioned/vs. unsanctioned
 */
int incrementToNextFence(int minute) ;

/**
 * Returns a pair of numbers that represent the sanctioned vs. 
 * unsanctioned breakdown of time.
 *
 * TODO: Optimize this--carbon copy of python code right now.
 */
tuple<int, int> getSanctionedBreakdown(int startMinute, int duration) ;

int applyRestingPeriod(int current, int unsanctioned) ;

#endif
