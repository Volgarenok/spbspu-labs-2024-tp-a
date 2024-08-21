<<<<<<< HEAD
#include "dataStruct.hpp"
#include <iostream>
#include <complex>
#include <cmath>
#include "delimeter.hpp"

bool isaychev::DataStruct::operator<(const DataStruct & other) const
{
  if (key1 == other.key1)
  {
    if (std::abs(key2) == std::abs(other.key2))
    {
      return (key3.size() < other.key3.size());
    }
    return (std::abs(key2) < std::abs(other.key2));
  }
  return (key1 < other.key1);
}

std::istream & isaychev::operator>>(std::istream & in, DataStruct & obj)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> std::noskipws;

  using dc = DelimChI;
  using ds = DelimStrI;

  DataStruct input;
  char c = 0;

  in >> ds{"(:"};
  for (int i = 0; i < 3; ++i)
  {
    in >> ds{"key"} >> c;

    if (c == '1')
    {
      in >> dc{' '} >> LongLongI{input.key1};
    }
    else if (c == '2')
    {
      in >> dc{' '} >> ComplexI{input.key2};
    }
    else if (c == '3')
    {
      in >> dc{' '} >> StringI{input.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> dc{':'};
  }
  in >> dc{')'};

  if (in)
  {
    obj = input;
  }

  in >> std::skipws;
  return in;
}

std::ostream & isaychev::operator<<(std::ostream & out, const DataStruct & obj)
{
  out << "(:key1 " << obj.key1 << "ll";
  out << ":key2 #c(" << obj.key2.real() << " " << obj.key2.imag() << ")";
  out << ":key3 \"" << obj.key3 << "\":)";
  return out;
}
||||||| f3aec558
=======
#include "dataStruct.hpp"
#include <iostream>
#include <complex>
#include <cmath>
#include <delimeter.hpp>

bool isaychev::DataStruct::operator<(const DataStruct & other) const
{
  if (key1 == other.key1)
  {
    if (std::abs(key2) == std::abs(other.key2))
    {
      return (key3.size() < other.key3.size());
    }
    return (std::abs(key2) < std::abs(other.key2));
  }
  return (key1 < other.key1);
}

std::istream & isaychev::operator>>(std::istream & in, DataStruct & obj)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> std::noskipws;

  using dc = DelimChI;
  using ds = DelimStrI;

  DataStruct input;
  char c = 0;

  in >> ds{"(:"};
  for (int i = 0; i < 3; ++i)
  {
    in >> ds{"key"} >> c;

    if (c == '1')
    {
      in >> dc{' '} >> LongLongI{input.key1};
    }
    else if (c == '2')
    {
      in >> dc{' '} >> ComplexI{input.key2};
    }
    else if (c == '3')
    {
      in >> dc{' '} >> StringI{input.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> dc{':'};
  }
  in >> dc{')'};

  if (in)
  {
    obj = input;
  }

  in >> std::skipws;
  return in;
}

std::ostream & isaychev::operator<<(std::ostream & out, const DataStruct & obj)
{
  out << "(:key1 " << obj.key1 << "ll";
  out << ":key2 #c(" << obj.key2.real() << " " << obj.key2.imag() << ")";
  out << ":key3 \"" << obj.key3 << "\":)";
  return out;
}
>>>>>>> ebc1f256593acc7048121657479887c018d91482
