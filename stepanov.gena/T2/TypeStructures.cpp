#include "TypeStructures.h"
#include <bitset>
#include <iostream>
#include <StreamGuard.h>
#include <HelperStructsIO.h>

stepanov::BinUnsignedLongLongIO::BinUnsignedLongLongIO(unsigned long long& ref) :
  ref_(ref)
{}

stepanov::StringIO::StringIO(std::string& ref) :
  ref_(ref)
{}

stepanov::OctUnsignedLongLongIO::OctUnsignedLongLongIO(unsigned long long& ref) :
  ref_(ref)
{}

std::istream& stepanov::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> stepanov::DelimeterIO{ '"' }, dest.ref_, '"');
}

std::istream& stepanov::operator>>(std::istream& in, BinUnsignedLongLongIO&& dest)
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

std::istream& stepanov::operator>>(std::istream& in, OctUnsignedLongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  StreamGuard format(in);
  return in >> DelimeterIO{ '0' } >> std::oct >> dest.ref_;
}
