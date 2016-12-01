#include "configuration.h"
/*******************************************************************************
 * Implementation for the 'Configuration' class.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Date: 6 October 2016
 *
 * Used and Modified by: Adrian Brooks
 *                       Russell Burckhalter
 *                       Donald Landrum Jr
 *                       Matthew McGee
 *                       Marc Ochsner
 *
 * Date last modified: December 1 2016
 *
 * This class contains three important functions: an accessor, a ToString, and 
 * a ReadConfiguration. The accessor returns the last index of the vector 
 * actual_service_times_ and is used internally. The ToString returns a string 
 * represenation of the data contained in this class. Finaly, the 
 * ReadConfiguration takes in a Scanner and uses it to populate the public 
 * variables defined in the header file for a certain instance of configuration.
**/

static const string kTag = "CONFIG: ";

/*******************************************************************************
 * Constructor.
**/
Configuration::Configuration() {
}

/*******************************************************************************
 * Destructor.
**/
Configuration::~Configuration() {
}

/*******************************************************************************
 * Accessors and mutators.
**/
/*******************************************************************************
 * Function 'GetMaxServiceSubscript'.
 * This function returns an integer corresponding to the maximum service 
 * subscript.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   the last index of the vector 'actual_service_times_'
**/
int Configuration::GetMaxServiceSubscript() const {
  return static_cast<int>(actual_service_times_.size()) - 1;
}

/*******************************************************************************
 * General functions.
**/
/******************************************************************************* * Function 'ReadConfiguration'.
 * This function reads two lines from the instream Scanner and populates each
 * public variable declared in the header file with this data except for the 
 * vector 'actual_service_times_', which is populated with data from the file 
 * "dataallsorted.txt". 
 *
 * Parameters:
 *   instream - a pointer to the scanner from which we are reading the data
 * 
 * Returns:
 *   None
**/
void Configuration::ReadConfiguration(Scanner& instream) {
  string line;
  ScanLine scanline;

  line = instream.NextLine();
  scanline.OpenString(line);
  seed_ = scanline.NextInt();
  election_day_length_hours_ = scanline.NextInt();
  election_day_length_seconds_ = election_day_length_hours_ * 3600;
  time_to_vote_mean_seconds_ = scanline.NextInt();
  min_expected_to_simulate_ = scanline.NextInt();
  max_expected_to_simulate_ = scanline.NextInt();
  wait_time_minutes_that_is_too_long_ = scanline.NextInt();
  number_of_iterations_ = scanline.NextInt();

  line = instream.NextLine();
  scanline.OpenString(line);
  arrival_zero_ = scanline.NextDouble();
  for (int sub = 0; sub < election_day_length_hours_; ++sub) {
    double input = scanline.NextDouble();
    arrival_fractions_.push_back(input);
  }

  Scanner service_times_file;
  service_times_file.OpenFile("dataallsorted.txt");
  while (service_times_file.HasNext()) {
    int thetime = service_times_file.NextInt();
    actual_service_times_.push_back(thetime);
  }
}

/*******************************************************************************
 * Function 'ToString'.
 * This function creates a string that contains all of the labeled data within
 * the configuration class with the exception of the 'actual_service_times_' 
 * vector. This function also makes liberal use of the 'Utils::Format' function
 * in order to make the data easily readable.
 * 
 * Parameters:
 *   None
 *
 * Returns:
 *   s - a string representation of the configuration
**/
string Configuration::ToString() {
  string s = "\n";
  s += kTag;
  s += "RN seed:              ";
  s += Utils::Format(seed_, 8) + "\n";
  s += kTag;
  s += "Election Day length:  ";
  s += Utils::Format(election_day_length_seconds_, 8) + " =";
  s += Utils::Format(election_day_length_seconds_/3600.0, 8, 2) + " (";
  s += Utils::Format(election_day_length_hours_, 8, 2) + ") hours\n";
  s += kTag;
  s += "Time to vote mean:    ";
  s += Utils::Format(time_to_vote_mean_seconds_, 8) + " =";
  s += Utils::Format(time_to_vote_mean_seconds_/60.0, 8, 2) + " minutes\n";
  s += kTag;
  s += "Min and max expected voters for this simulation:     ";
  s += Utils::Format(min_expected_to_simulate_, 8);
  s += Utils::Format(max_expected_to_simulate_, 8) + "\n";
  s += "Wait time (minutes) that is 'too long': ";
  s += Utils::Format(wait_time_minutes_that_is_too_long_, 8) + "\n";
  s += "Number of iterations to perform: ";
  s += Utils::Format(number_of_iterations_, 4) + "\n";
  s += "Max service time subscript: ";
  s += Utils::Format(GetMaxServiceSubscript(), 6) + "\n";
  int offset = 6;
  s += kTag;
  s += Utils::Format(0, 2) + "-" + Utils::Format(0, 2);
  s += " : " + Utils::Format(arrival_zero_, 7, 2) + "\n";
  for (UINT sub = 0; sub < arrival_fractions_.size(); ++sub) {
    s += kTag;
    s += Utils::Format(offset+sub, 2) + "-" + Utils::Format(offset+sub+1, 2);
    s += " : " + Utils::Format(arrival_fractions_.at(sub), 7, 2) + "\n";
  }  
  s += "\n";
  return s;
}

