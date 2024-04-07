#include "delimiters.hpp"
#include "streamGuard.hpp"
#include <iostream>

std::istream& chernov::operator>>(std::istream& in, UnsignedLongLongIO&& exp)
{}

std::istream& chernov::operator>>(std::istream& in, CharIO&& exp)
{}

std::istream& chernov::operator>>(std::istream& in, DoubleIO&& exp)
{}

std::istream& chernov::operator>>(std::istream& in, StringIO&& exp)
{}

std::string chernov::convertDoubleToCalcDouble(double number)
{}
