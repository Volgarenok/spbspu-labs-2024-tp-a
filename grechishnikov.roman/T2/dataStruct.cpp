#include "dataStruct.hpp"
#include <iomanip>
#include <string>
#include "scopeGuard.hpp"
#include "delimiter.hpp"
#include "keyDelimiters.hpp"

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
      in >> Key1_Delimiter{ data.key1 };
    }
    else if (str == "key2")
    {
      check = check | 0b010;
      in >> Key2_Delimiter{ data.key2 };
    }
    else if (str == "key3")
    {
      check = check | 0b100;
      in >> Key3_Delimiter{ data.key3 };
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
  out << ":" << "key2 " << "#c" << data.key2;
  out << ":" << "key3 " << "\"" << data.key3 << "\"" << ":)";
  return out;
}

std::ostream& grechishnikov::operator<<(std::ostream& out, const std::complex< double >& comp)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  ScopeGuard sGuard(out);

  out << std::fixed << std::setprecision(1) << "(" << comp.real() << " " << comp.imag() << ")";
  return out;
}
