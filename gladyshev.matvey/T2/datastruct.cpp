#include "datastruct.hpp"

#include <string>
#include <algorithm>
#include <cmath>

#include "streamguard.hpp"
#include "delimiter.hpp"
#include "parsescientific.hpp"

bool gladyshev::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 < other.key1) return true;
        if (key1 > other.key1) return false;

        if (key2 < other.key2) return true;
        if (key2 > other.key2) return false;

        return key3.size() < other.key3.size();
}

std::istream& gladyshev::operator>>(std::istream& in, DataStruct& value)
{
 std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard StreamGuard(in);
  in >> Delimiter{"(:"};
  double key1 = 0;
  char key2 = 0;
  std::string key3 = "";
  std::string supstr = "";
  for (size_t i = 0; i < 3; ++i)
  {
    in >> supstr;
    if (supstr == "key1")
    {
      std::getline(in, supstr, ':');
      std::transform(supstr.cbegin(), supstr.cend(), supstr.begin(), ::tolower);
      double mantissa = 0;
      int num = 0;
      if (supstr.find('e') != std::string::npos)
      {
        mantissa = std::stod(supstr.substr(0, supstr.find('e')));
        num = std::stoi(supstr.substr(supstr.find('e') + 1));
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
      if (mantissa < 1 || mantissa >= 10)
      {
        in.setstate(std::ios::failbit);
      }
      key1 = mantissa * std::pow(10, num);
    }
    else if (supstr == "key2")
    {
      in >> Delimiter{"'"} >> key2 >> Delimiter{"':"};
    }
    else if (supstr == "key3")
    {
      in >> Delimiter{"\""};
      std::getline(in, key3, '"');
      in >> Delimiter{":"};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> Delimiter{")"};
  if (in)
  {
    value = DataStruct{key1, key2, key3};
  }
  return in;
}

std::ostream& gladyshev::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard StreamGuard(out);
  out << std::fixed;
  out.precision(1);
  out << "(:key1 ";
  parseScientific(out, value.key1);
  out << ":key2 '" << value.key2 << "':key3 \"" << value.key3 << "\":)";
  return out;
}
