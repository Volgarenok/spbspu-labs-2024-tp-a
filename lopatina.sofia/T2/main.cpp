#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iterator>
#include <algorithm>


namespace lopatina
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;

    bool operator<(const DataStruct & sec)
    {
      if (key1 != sec.key1)
      {
        return key1 < sec.key1;
      }
      if (key2 != sec.key2)
      {
        return key2 < sec.key2;
      }
      return key3.size() < sec.key3.size();
    }
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct IntIO
  {
    int & ref;
  };

  struct DoubleIO
  {
    double & ref;
  };

  struct UllIO
  {
    unsigned long long & ref;
  };

  struct LongLongIO
  {
    long long & ref;
  };

  struct UllLiteralIO
  {
    unsigned long long & ref;
  };

  struct RationalIO
  {
    std::pair<long long, unsigned long long> & ref;
  };

  struct StringIO
  {
    std::string & ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

  class StreamGuard
  {
  public:
    StreamGuard(std::basic_ios<char> & s):
      s_(s),
      fill_(s.fill()),
      precision_(s.precision()),
      flags_(s.flags())
    {}
    ~StreamGuard()
    {
      s_.fill(fill_);
      s_.precision(precision_);
      s_.flags(flags_);
    }
  private:
    std::basic_ios<char> & s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags flags_;
  };

  std::istream & operator>>(std::istream & in, DelimiterIO && dest)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    char c = 0;
    in >> c;
    c = std::tolower(c);
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream & operator>>(std::istream & in, IntIO && dest)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    return in >> dest.ref;
  }

  std::istream & operator>>(std::istream & in, UllIO && dest)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    return in >> dest.ref;
  }

  std::istream & operator>>(std::istream & in, LongLongIO && dest)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    return in >> dest.ref;
  }

  std::istream & operator>>(std::istream & in, DoubleIO && dest)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{'d'};
  }

  std::istream & operator>>(std::istream & in, UllLiteralIO && dest)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{'u'} >> DelimiterIO{'l'} >> DelimiterIO{'l'};
  }

  std::istream & operator>>(std::istream & in, StringIO && dest)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }

  std::istream & operator>>(std::istream & in, LabelIO && dest)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    return in >> dest.exp;
  }

  std::istream & operator>>(std::istream & in, DataStruct & dest)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    DataStruct input;
    {
      using del = DelimiterIO;
      using label = LabelIO;
      using inT = IntIO;
      using dbl = DoubleIO;
      using str = StringIO;
      using ulllit = UllLiteralIO;
      using ll = LongLongIO;
      using ull = UllIO;
      std::string key;
      in >> del{'('} >> del{':'};
      for (size_t i = 0; i < 3; ++i)
      {
        in >> key;
        if (key == "key1")
        {
          in >> ulllit{input.key1} >> del{':'};
        }
        else if (key == "key2")
        {
          in >> del{'('} >> del{':'} >> del{'n'};
          in >> ll{input.key2.first};
          in >> del{':'} >> del{'d'};
          in >> ull{input.key2.second};
          in >> del{':'} >> del{')'} >> del{':'};
        }
        else if (key == "key3")
        {
          in >> str{input.key3} >> del{':'};
        }
      }
      in >> del{')'};
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream & operator<<(std::ostream & out, const DataStruct & data)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    StreamGuard fmtguard(out);
    out << "(:key1 " << data.key1 << "ull";
    out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
  }
}

int main()
{
  using lopatina::DataStruct;

  std::vector<DataStruct> data;

  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator<DataStruct>{std::cin},
      std::istream_iterator<DataStruct>{},
      std::back_inserter(data)
    );
    if (!std::cin)
    {
      std::cin.clear(std::ios::goodbit);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );
  return 0;
}
