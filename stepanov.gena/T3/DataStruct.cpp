#include "DataStruct.h"
#include <iterator>
#include <algorithm>
#include <StreamGuard.h>
#include <HelperStructsIO.h>

std::istream& stepanov::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using sep = DelimeterIO;
  in >> sep{'('};
  in >> dest.x_;
  in >> sep{';'};
  in >> dest.y_;
  in >> sep{')'};
  return in;
}
 
