#ifndef PARSE_FUNCTIONS_HPP
#define PARSE_FUNCTIONS_HPP

#include <istream>
#include <string>
#include <complex>

void parseSignedLL(std::istream& in, long long& value);
void parseComplex(std::istream& in, std::complex< double >& value);

#endif