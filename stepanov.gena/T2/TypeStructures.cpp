#include "TypeStructures.h"
#include <bitset>
#include <iostream>
#include "StreamGuard.h"
#include "HelperStructsIO.h"

namespace stepanov
{
  BinUnsignedLongLongIO::BinUnsignedLongLongIO(unsigned long long& ref) :
    ref_(ref)
  {}

  StringIO::StringIO(std::string& ref) :
    ref_(ref)
  {}

  OctUnsignedLongLongIO::OctUnsignedLongLongIO(unsigned long long& ref) :
    ref_(ref)
  {}

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimeterIO{ '"' }, dest.ref_, '"');
  }

  std::istream& operator>>(std::istream& in, BinUnsignedLongLongIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    StreamGuard format(in);
    in >> DelimeterIO{ '0' } >> DelimeterIO{ 'b' };
    in >> dest.ref_;
    return in;
  }

  std::istream& operator>>(std::istream& in, OctUnsignedLongLongIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    StreamGuard format(in);
    return in >> DelimeterIO{ '0' } >> std::oct >> dest.ref_;
  }
}
