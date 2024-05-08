#include "dataStruct.hpp"
#include <iomanip>
#include <string>
#include <cmath>
#include "scopeGuard.hpp"
#include "delimiter.hpp"
#include "keyDelimiters.hpp"

double findModule(const std::complex< double >& comp);

std::istream& grechishnikov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimiter;
  std::string str = "";
  in >> del{ '(' };
  size_t check = 0b000;
  for (size_t i = 0; i < 3; i++)
  {
    in >> del{ ':' };
    std::getline(in, str, ' ');
    if (str == "key1")
    {
      check = check | 0b001;
      in >> Key1Delimiter{ data.key1 };
    }
    else if (str == "key2")
    {
      check = check | 0b010;
      in >> Key2Delimiter{ data.key2 };
    }
    else if (str == "key3")
    {
      check = check | 0b100;
      in >> Key3Delimiter{ data.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  if (!in || check != 0b111)
  {
    in.setstate(std::ios::failbit);
  }
  in >> del{ ':' };
  in >> del{ ')' };
  return in;
}

std::ostream& grechishnikov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  ScopeGuard sGuard(out);

  out << std::oct <<"(:" << "key1 " << "0" << data.key1;
  out << std::fixed << std::setprecision(1);
  out << ":" << "key2 " << "#c(" << data.key2.real() << " " << data.key2.imag() << ")";;
  out << ":" << "key3 " << "\"" << data.key3 << "\"" << ":)";
  return out;
}

bool grechishnikov::operator<(const DataStruct& first, const DataStruct& second)
{
  if (first.key1 != second.key1)
  {
    return first.key1 < second.key1;
  }
  if (first.key2 != second.key2)
  {
    return findModule(first.key2) < findModule(second.key2);
  }
  return first.key3.length() < second.key3.length();
}

double findModule(const std::complex< double >& comp)
{
  return std::sqrt(std::pow(comp.real(), 2) + std::pow(comp.imag(), 2));
}
