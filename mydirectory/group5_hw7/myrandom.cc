#include "myrandom.h"

#include <map>

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'MyRandom' for random number generation.
 *
 * Author: Duncan A. Buell
 * Date last modified: 23 May 2016
 *
 * Used and Modified by: Adrian Brooks
 *                       Russell Burckhalter
 *                       Donald Landrum Jr
 *                       Matthew McGee
 *                       Marc Ochsner
 *
 * Date last modified: December 1 2016
 *
 * This class contains functions that will generate a random integer based on 
 * a uniform or exponential distribution or a random double based on a uniform 
 * or normal distribution.
 * In this particular program, only the random uniform integer and random 
 * exponential integer are used.
**/

/******************************************************************************
 * Constructor
**/
MyRandom::MyRandom() {
  seed_ = 1;
  generator_.seed(seed_);
}

/******************************************************************************
 * Constructor
**/
MyRandom::MyRandom(unsigned seed) {
  seed_ = seed;
  generator_.seed(seed_);
}

/******************************************************************************
 * Destructor
**/
MyRandom::~MyRandom() {
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'RandomExponentialInt'.
 * This generates 'double' random numbers exponentially distributed with
 * parameter 'lambda'. It uses an assert statement for parameter checking.
 *
 * PDF is lambda * exp(-lambda * t)
 *
 * Parameters:
 *   lambda - the lambda of the exponentially distributed RNs
 *
 * Returns:
 *   the random number as an 'int' rounded from the 'double'
**/
int MyRandom::RandomExponentialInt(double lambda) {
  assert(lambda >= 0.0);
  std::exponential_distribution<double> distribution(lambda);
  int r = round(distribution(generator_));
  return r;
}

/******************************************************************************
 * Function 'RandomNormal'.
 * This generates 'double' random numbers normally distributed with
 * mean 'mean' and standard deviation 'dev'. It also uses an assert for
 * initial parameter checking.
 * This function is not used in this particular assignment.
 *
 * Parameters:
 *   mean - the mean of the normally distributed RNs
 *   dev - the standard deviation of the normally distributed RNs
 *
 * Returns:
 *   the random number as a 'double'
**/
double MyRandom::RandomNormal(double mean, double dev) {
  assert(dev >= 0.0);
  std::normal_distribution<double> distribution(mean, dev);
  double r = distribution(generator_);
  return r;
}

/******************************************************************************
 * Function 'RandomUniformDouble'.
 * This generates 'double' random numbers uniformly distributed from
 * 'lower' to 'upper' inclusive. It also uses an assert for parameter checking.
 * This function is not used in this particular assignment.
 *
 * Parameters:
 *   lower - the smallest value of the RNs
 *   upper - the largest value of the RNs
 *
 * Returns:
 *   the random number as a 'double'
**/
double MyRandom::RandomUniformDouble(double lower, double upper) {
  assert(lower <= upper);
  std::uniform_real_distribution<double> distribution(lower, upper);
  double r = distribution(generator_);
  return r;
}

/******************************************************************************
 * Function 'RandomUniformInt'.
 * This generates 'int' random numbers uniformly distributed from
 * 'lower' to 'upper' inclusive. It also uses an assert for parameter checking.
 *
 * Parameters:
 *   lower - the smallest value of the RNs
 *   upper - the largest value of the RNs
 *
 * Returns:
 *   the random number as an 'int'
**/
int MyRandom::RandomUniformInt(int lower, int upper) {
  assert(lower <= upper);
  std::uniform_int_distribution<int> distribution(lower, upper);
  int r = distribution(generator_);
  return r;
}
