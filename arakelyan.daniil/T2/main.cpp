#include <iostream>
#include <limits>

#include "dataStruct.hpp"


// namespace arakelyan
// {
  // struct SomeDataS
  // {
  //   SomeDataS() = default;
  //   SomeDataS(int aa, int bb):
  //     a(aa),
  //     b(bb)
  //   {}
  //   int a;
  //   int b;
  // };

  // struct SeparIO 
  // {
  //   char expSep;
  // };

  // struct LableIO
  // {
  //   std::string expLab;
  // };

  // std::istream &operator>>(std::istream &in, SeparIO &&exp)
  // {
  //   std::istream::sentry guard(in);
  //   if (!guard)
  //   {
  //     return in;
  //   }
  //   char c = 0;
  //   in >> c;
  //   if (c != exp.expSep)
  //   {
  //     in.setstate(std::ios::failbit);
  //     return in;
  //   }
  //   return in;
  // }

  // std::istream &operator>>(std::istream &in, LableIO &&exp)
  // {
  //   std::istream::sentry guard(in);
  //   if (!guard)
  //   {
  //     return in;
  //   }
  //   std::string expec = "";
  //   in >> expec;
  //   if (expec != exp.expLab)
  //   {
  //     in.setstate(std::ios::failbit);
  //     return in;
  //   }
  //   return in;
  // }

  //format: {:key: 10 :key: 20}
  // std::istream &operator>>(std::istream &in, SomeDataS &data)
  // {
  //   std::istream::sentry guard(in);
  //   if (!guard)
  //   {
  //     return in;
  //   }
  //   using sep = SeparIO;
  //   using lab = LableIO;
  //   int a = 0;
  //   int b = 0;
  //   in >> sep{'{'};
  //   in >> lab{"key1"} >> sep{':'} >> a;
  //   in >> lab{"key2"} >> sep{':'} >> b;
  //   in >> sep{'}'};
  //   if (in)
  //   {
  //     data = SomeDataS(a,b);
  //   }
  //   return in;
  // }

  // std::ostream &operator<<(std::ostream &out, const SomeDataS &data)
  // {
  //   std::ostream::sentry guard(out);
  //   if (!guard)
  //   {
  //     return out;
  //   }
  //   out << ":key1:" << data.a << " :key2:" << data.b;
  //   return out;
  // }
// }

int main()
{
  //in format -> (:key1 10:key2 30)
  using namespace arakelyan;
  DataStruct data;
  while(!(std::cin >> data))
  {
    if (!(std::cin))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::cout << data << "\n";
  return 0;
}
