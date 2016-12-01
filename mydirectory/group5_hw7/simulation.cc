#include "simulation.h"
/****************************************************************
 * Implementation for the 'Simulation' class.
 *
 * Author/copyright:  Duncan Buell
 * Date: 19 July 2016
 *
 * Used and Modified by: Adrian Brooks
 *                       Russell Burckhalter
 *                       Donald Landrum Jr
 *                       Matthew McGee
 *                       Marc Ochsner
 *
 * Date last modified: December 1 2016
 *
 * The simulation class is used to set up the pcts_ vector and
 * call RunSimulationPct for each OnePct after doing bounds
 * checking. In short, it sets up the program and begins
 * execution.
**/

static const string kTag = "SIM: ";

/****************************************************************
* Constructor.
**/
Simulation::Simulation(){
}

/****************************************************************
* Destructor.
**/
Simulation::~Simulation(){
}

/****************************************************************
* Accessors and mutators.
**/

/****************************************************************
* General functions.
**/

/****************************************************************
* ReadPrecincts
*
* We iterate through infile and create a new OnePct each
* iteration.  ReadData is then called for each OnePct, which
* takes in the infile. Lastly, each OnePct is added to pcts_.
*
* Parameters: 
*   - Scanner infile
* Returns: nothing
**/
void Simulation::ReadPrecincts(Scanner& infile) {
  while (infile.HasNext()) {
    
    OnePct new_pct;
    new_pct.ReadData(infile);
    pcts_[new_pct.GetPctNumber()] = new_pct;
  } // while (infile.HasNext()) {
} // void Simulation::ReadPrecincts(Scanner& infile) {

/****************************************************************
* RunSimulation
*
* We use a for loop to iterate through all of pcts_.  Eahc 
* iteration is bounds-checked and, if in the bounds, output.
* Each iteration then has RunSimulationPct called, passing in
* config, random and out_stream. After the loop, the total
* collection of precincts is output along with the number of 
* precincts.
*
* Parameters:
*  - Configuration config
*  - MyRandom random
*  - ofstream out_stream
* Returns: nothing
**/
void Simulation::RunSimulation(const Configuration& config,
                   MyRandom& random, ofstream& out_stream){
  string outstring = "XX";
  int pct_count_this_batch = 0;
  for(auto iterPct = pcts_.begin(); iterPct != pcts_.end();
      ++iterPct){

    OnePct pct = iterPct->second;
    int expected_voters = pct.GetExpectedVoters();
    if ((expected_voters <= config.min_expected_to_simulate_) ||
        (expected_voters > config.max_expected_to_simulate_)){
    
      continue;
    }

    outstring = kTag + "RunSimulation for pct " + "\n";
    outstring += kTag + pct.ToString() + "\n";
    Utils::Output(outstring, out_stream, Utils::log_stream);

    ++pct_count_this_batch;
    pct.RunSimulationPct(config, random, out_stream);

    //    break; // we only run one pct right now
  } // for(auto iterPct = pcts_.begin(); iterPct != pcts_.end(); ++iterPct)

  outstring = kTag + "PRECINCT COUNT THIS BATCH "
  + Utils::Format(pct_count_this_batch, 4) + "\n";
  Utils::Output(outstring, out_stream, Utils::log_stream);

} // void Simulation::RunSimulation()

/****************************************************************
*'ToString'.
*
* Iterates through each OnePct in pcts_ and adds its ToString to
* a return string which is returned at the end.
* (Not currently called anywhere, but left for future usage)
* 
* Parameters - none
* Returns : s
**/
string Simulation::ToString(){

  string s = "";

  for(auto iterPct = pcts_.begin(); iterPct != pcts_.end(); 
         ++iterPct){

    s += kTag + (iterPct->second).ToString() + "\n";
  }

  return s;
} // string Simulation::ToString()

