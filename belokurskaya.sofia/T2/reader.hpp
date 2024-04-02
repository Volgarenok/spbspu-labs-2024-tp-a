#ifndef READER_H
#define READER_H

#include "dataStruct.hpp"


struct DelimiterI
{
  char exp;
};

struct CharI
{
  char& ref;
};

struct StringI
{
  std::string& ref;
};

struct StringKeyI
{
  std::string& ref;
};

struct LabelI
{
  std::string exp;
};

struct LongLongI
{
  long long& num;
};

struct UnsignedLongLongI
{
  unsigned long long& num;
};

std::istream& operator>>(std::istream& in, DataStruct& dest);
std::istream& operator>>(std::istream& in, DelimiterI&& dest);
std::istream& operator>>(std::istream& in, CharI&& dest);
std::istream& operator>>(std::istream& in, StringI&& dest);
std::istream& operator>>(std::istream& in, StringKeyI&& dest);
std::istream& operator>>(std::istream& in, LabelI&& dest);
std::istream& operator>>(std::istream& in, LongLongI&& dest);
std::istream& operator>>(std::istream& in, UnsignedLongLongI&& dest);

#endif
