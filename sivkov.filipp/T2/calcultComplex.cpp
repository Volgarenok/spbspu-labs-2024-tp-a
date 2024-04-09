#include "calcultComplex.hpp"
#include <cmath>

double calcultComplex(double real, double imag)
{
  return sqrt(pow(2, imag) + pow(2, real));
}
