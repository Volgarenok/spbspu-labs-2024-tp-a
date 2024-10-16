#include "DataStruct.h"
#include <iostream>
#include "StreamGuard.h"
#include "HelperStructsIO.h"
#include "TypeStructures.h"

namespace stepanov
{
  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimeterIO;
      in >> sep{'('};
      in >> sep{':'};
      for (int i = 0; i < 3; ++i)
      {
        using oct = OctUnsignedLongLongIO;
        using bin = BinUnsignedLongLongIO;
        using str = StringIO;
        std::string key = "";
        in >> key;
        if (key == "key1")
        {
          in >> oct{input.key1_};
        }
        else if (key == "key2")
        {
          in >> bin{input.key2_};
        }
        else if (key == "key3")
        {
          in >> str{input.key3_};
        }
        in >> sep{':'};
      }
      in >> sep{')'};
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
}
