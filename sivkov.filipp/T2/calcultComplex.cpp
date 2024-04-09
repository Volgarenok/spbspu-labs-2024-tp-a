#include "calcultComplex.hpp"
#include <cmath>

double calcultComplex(double real, double imag)
{
  return std::sqrt(std::pow(2, imag) + std::pow(2, real));
}
