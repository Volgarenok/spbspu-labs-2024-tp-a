#include "dataStruct.hpp"

bool babinov::DataStruct::operator>(const DataStruct& right) const {};
bool babinov::DataStruct::operator<(const DataStruct& right) const {};
bool babinov::DataStruct::operator>=(const DataStruct& right) const {};
bool babinov::DataStruct::operator<=(const DataStruct& right) const {};
bool babinov::DataStruct::operator==(const DataStruct& right) const {};
bool babinov::DataStruct::operator!=(const DataStruct& right) const {};

std::istream& babinov::operator>>(std::istream& in, DataStruct& data) {};
std::ostream& babinov::operator<<(std::ostream& in, const DataStruct& data) {};
