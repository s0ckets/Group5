#include "onevoter.h"
/****************************************************************
 * Implementation for the 'OneVoter' class.
 * This class represents a single voter from a certain precinct. The constructor
 * is used to get: the arrival time inseconds, the voter's sequence out of 
 * 2700, and a randomized duration seconds used to decide how long that voter 
 * takes to vote. 
 * 
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Date: 6 October 2016
 * Used and Modified by: Adrian Brooks
 *                       Russell Burckhalter
 *                       Donald Landrum Jr
 *                       Matthew McGee
 *                       Marc Ochsner
 *
 * Date last modified: December 1 2016
 *
**/


static const string kTag = "ONEVOTER: ";

/****************************************************************
 * Constructor.
 **/
OneVoter::OneVoter() {
}

/****************************************************************
 * Parameterized Constructor
 **/
OneVoter::OneVoter(int sequence, int arrival_seconds, int duration_seconds) {
  sequence_ = sequence;
  time_arrival_seconds_ = arrival_seconds;
  time_start_voting_seconds_ = 0;
  time_vote_duration_seconds_ = duration_seconds;
  which_station_ = -1;
}

/****************************************************************
 * Destructor
 **/
OneVoter::~OneVoter() {
}

/****************************************************************
* Accessors and mutators.
**/
/****************************************************************
**/
int OneVoter::GetTimeArrival() const {
  return time_arrival_seconds_;
}

/****************************************************************
**/
int OneVoter::GetTimeWaiting() const {
  return time_waiting_seconds_;
}

/****************************************************************
**/
int OneVoter::GetStationNumber() const {
  return which_station_;
}

/****************************************************************
* General functions.
**/

/****************************************************************
 * Function 'AssignStation'
 * This assigns a given station number to the voter represented by this class.
 * 
 * Parameters:
 *  - station_number - the number representing a voting station
 *  - start_time_seconds - the 
 *
**/
void OneVoter::AssignStation(int station_number, int start_time_seconds) {
  which_station_ = station_number;
  time_start_voting_seconds_ = start_time_seconds;
  time_done_voting_seconds_ = time_start_voting_seconds_ 
                            + time_vote_duration_seconds_;

  time_waiting_seconds_ = time_start_voting_seconds_
                            - time_arrival_seconds_;
}

/****************************************************************
 * Function 'GetTimeDoneVoting'
 * This function returns the time (seconds) for a person to finish voting
**/
int OneVoter::GetTimeDoneVoting() const {
  return time_start_voting_seconds_ + time_vote_duration_seconds_;
}

/****************************************************************
 * Function 'GetTimeInQ'
 * This function returns the time (seconds) a person waits in line
**/
int OneVoter::GetTimeInQ() const {
  return time_start_voting_seconds_ - time_arrival_seconds_;
}

/****************************************************************
 * Function 'GetTOD'
 * This returns a string formatted as "Time Of Day" from seconds
 * Uses function:
 *  - ConvertTime (int time_in_seconds)
**/
string OneVoter::GetTOD(int time_in_seconds) const {
  int offset_hours = 0;
  string s = "";
  
  return this->ConvertTime(time_in_seconds + offset_hours*3600);
}

/****************************************************************
 * Function 'ConvertTime'
 * This function returns a String formatted time of day.
 * 
 * Returns:
 *
**/
string OneVoter::ConvertTime(int time_in_seconds) const {
  int hours = 0;
  int minutes = 0;
  int seconds = 0;
  string s = "";

  hours = time_in_seconds / 3600;
  minutes = (time_in_seconds - 3600*hours) / 60;
  seconds = (time_in_seconds - 3600*hours - 60*minutes);

  s += Utils::Format(time_in_seconds, 6);

  if (hours < 0)
    s += " 00";
  else if (hours < 10)
    s += " 0" + Utils::Format(hours, 1);
  else
    s += " " + Utils::Format(hours, 2);

  if (minutes < 0)
    s += ":00";
  else if (minutes < 10)
    s += ":0" + Utils::Format(minutes, 1);
  else
    s += ":" + Utils::Format(minutes, 2);

  if (seconds < 0)
    s += ":00";
  else if (seconds < 10)
    s += ":0" + Utils::Format(seconds, 1);
  else
    s += ":" + Utils::Format(seconds, 2);

  return s;
} // string OneVoter::ConvertTime(int time_in_seconds) const

/****************************************************************
 * Function 'ToString'
 * This function returns a String of voter's data annd times, 
 * retrieved through this->function calls for efficiency.
 *
 * Returns: String s (contains):
 *     - voter's sequence in precinct (of 2700)
 *     - Time-formatted arrival time
 *     - Time-formatted start voting time
 *     - Time-formatted voting duration time
 *     - Time-formatted end voting time
 *     - Time-formatted total time in Queue
 *     - Station Number
**/
string OneVoter::ToString() {
  string s = kTag;

  s += Utils::Format(sequence_, 7);
  s += ": ";
  s += Utils::Format(this->GetTOD(time_arrival_seconds_));
  s += " ";
  s += Utils::Format(this->GetTOD(time_start_voting_seconds_));
  s += " ";
  s += Utils::Format(this->ConvertTime(time_vote_duration_seconds_));
  s += " ";
  s += Utils::Format(this->GetTOD(time_start_voting_seconds_ 
    + time_vote_duration_seconds_));
  s += " ";
  s += Utils::Format(this->ConvertTime(GetTimeInQ()));
  s += ": ";
  s += Utils::Format(which_station_, 4);

  return s;
} // string OneVoter::toString()

/****************************************************************
 * Function 'ToStringHeader'
 * This function returns a String formatted as a header for data in ToString()
 * 
 * Returns: String (represents)
 *     - Sequence, Arrival time, Start Time, Vote Duration, End Time, Wait Time,
 *       Station Number
**/
string OneVoter::ToStringHeader() {
  string s = kTag;
  s += "    Seq        Arr           Start             Dur";
  s += "             End            Wait         Stn";
  return s;
}

