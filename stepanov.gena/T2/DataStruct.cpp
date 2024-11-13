#include "DataStruct.h"
#include <bitset>
#include <iostream>
#include "StreamGuard.h"
#include "HelperStructsIO.h"
#include "TypeStructures.h"
#include <iomanip>

std::istream& stepanov::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimeterIO;
    in >> sep{ '(' };
    in >> sep{ ':' };
    for (int i = 0; i < 3; ++i)
    {
      using oct = OctUnsignedLongLongIO;
      using bin = BinUnsignedLongLongIO;
      using str = StringIO;
      std::string key = "";
      in >> key;
      if (key == "key1")
      {
        in >> oct{ input.key1_ };
      }
      else if (key == "key2")
      {
        in >> bin{ input.key2_ };
      }
      else if (key == "key3")
      {
        in >> str{ input.key3_ };
      }
      in >> sep{ ':' };
    }
    in >> sep{ ')' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream& stepanov::operator<<(std::ostream& out, const stepanov::DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard format(out);
  out << "(";
  out << ":key1 0" << std::oct << src.key1_;
  out << ":key2 0b" << BinUnsignedLongLong{src.key2_};
  out << ":key3 " << std::quoted(src.key3_);
  out << ":)";
  return out;
}

std::ostream& stepanov::operator<<(std::ostream& out, const stepanov::BinUnsignedLongLong& bin)
{
  if (bin.value == 0)
  {
    out << "" << bin.value;
  }
  else
  {
    out << "0" << bin.value;
  }
  return out;
}

bool stepanov::operator<(const stepanov::DataStruct& first, const stepanov::DataStruct& second)
{
  if (first.key1_ != second.key1_)
  {
    return first.key1_ < second.key1_;
  }
  else
  {
    if (first.key2_ != second.key2_)
    {
      return abs(first.key2_) < abs(second.key2_);
    }
    else
    {
      return first.key3_.size() < second.key3_.size();
    }
  }
}
