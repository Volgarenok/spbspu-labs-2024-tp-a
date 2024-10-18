#include "DataStruct.h"
#include "TypeStructures.h"
#include "HelperStructsIO.h"
#include "StreamGuard.h"

namespace stepanov
{
  bool operator<(const DataStruct& first, const DataStruct& second)
  {
    if (first.key1_ != second.key1_) return first.key1_ < second.key1_;
    if (first.key2_ != second.key2_) return first.key2_ < second.key2_;
    return first.key3_ < second.key3_;
  }

  std::istream & operator>>(std::istream & in, DataStruct & dest)
  {
    std::istream::sentry sentry(in);
    if(!sentry)
    {
      return in;
    }
    StreamGuard guard(in);

    if (!(in >> DelimeterIO{'('} >> DelimeterIO{':'}))
    {
      return in;
    }

    for (size_t i = 0; i < 3; ++i)
    {
      char num = 0;
      in >> DelimeterIO{'k'} >> DelimeterIO{'e'} >> DelimeterIO{'y'} >> num;

      switch (num)
      {
        case '1':
          in >> BinUnsignedLongLongIO{dest.key1_};
          break;

        case '2':
          in >> OctUnsignedLongLongIO{dest.key2_} >> DelimeterIO{':'};
          break;

        case '3':
          in >> StringIO{dest.key3_} >> DelimeterIO{':'};
          break;

        default:
          return in;
      }
    }

    in >> DelimeterIO{')'};
    return in;
  }

  std::ostream & operator<<(std::ostream & out, const DataStruct & dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    StreamGuard guard(out);

    DataStruct structCopy = dest;

    out << "(:key1 " << BinUnsignedLongLongIO{structCopy.key1_};
    out << ":key2 " << OctUnsignedLongLongIO{structCopy.key2_};
    out << ":key3 " << StringIO{structCopy.key3_} << ":)";

    return out;
  }
}
