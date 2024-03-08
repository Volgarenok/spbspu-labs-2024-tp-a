#include "dataStruct.hpp"
#include <iomanip>
#include "delimeterI.hpp"
#include "parseFunctions.hpp"
#include "streamGuard.hpp"

std::istream& kravchenko::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using cDel = DelimeterI;
  DataStruct temp{ 0, {0, 0}, "" };
  in >> cDel{ '(' } >> cDel{ ':' };
  for (short i = 0; i < 3; ++i)
  {
    std::string key;
    std::getline(in, key, ' ');
    if (key == "key1")
    {
      parseSignedLL(in, temp.key1);
    }
    else if (key == "key2")
    {
      parseComplex(in, temp.key2);
    }
    else if (key == "key3")
    {
      in >> cDel{ '"' };
      std::getline(in, temp.key3, '"');
    }
    in >> cDel{ ':' };
  }
  in >> cDel{ ')' };
  if (in)
  {
    value = temp;
  }
  return in;
}

std::ostream& kravchenko::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
	StreamGuard guard(out);
	out << std::setprecision(1) << std::fixed;
  out << "(:";
  out << "key1 " << value.key1 << "ll:";
  out << "key2 #c(" << value.key2.real() << ' ' << value.key2.imag() << "):";
  out << "key3 \"" << value.key3 << '\"';
  out << ":)";
  return out;
}

bool kravchenko::DataStruct::operator<(const DataStruct &other)
{
	if (key1 == other.key1)
	{
		if (std::abs(key2) == std::abs(other.key2))
		{
			return key3.size() < other.key3.size();
		}
		return std::abs(key2) < std::abs(other.key2);
	}
  return key1 < other.key1;
}