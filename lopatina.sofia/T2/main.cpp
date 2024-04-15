#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iterator>
#include <algorithm>


namespace lopatina
{
// (:key1 89ull:key2 (:N -2:D 3:):key3 "Data":)

//( : "key1" 12 : "key2" 2.89d : "key3" "stst" : )
  struct DataStruct
  {
    int key1;
    double key2;
    std::string key3;
/*
    unsigned long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
*/
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
/*
  struct UllLiteralIO
  {
    unsigned long long & ref;
  };

  struct RationalIO
  {
    std::pair<long long, unsigned long long> & ref;
  };
*/
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
    std::cout << "OP DEL\n";
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    char c = 0;
    in >> c;
    if (in && (c != dest.exp))
    {
      std::cout << "BAD!!!\n";
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream & operator>>(std::istream & in, IntIO && dest)
  {
    std::cout << "OP INT\n";
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    return in >> dest.ref;
  }

  std::istream & operator>>(std::istream & in, DoubleIO && dest)
  {
    std::cout << "OP DOUBLE\n";
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{'d'};
  }

  std::istream & operator>>(std::istream & in, StringIO && dest)
  {
    std::cout << "OP STR\n";
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }

  std::istream & operator>>(std::istream & in, LabelIO && dest)
  {
    std::cout << "OP LABEL\n";
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
/*
    std::string data = "";
    if ((in >> StringIO{data}) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
*/
    return in >> dest.exp;
  }

  std::istream & operator>>(std::istream & in, DataStruct & dest)
  {
//(:key1 12:key2 2.89d:key3 "stst":)
    std::cout << "OP DATA\n";
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
      in >> del{'('} >> del{':'};
      std::string key;
      in >> key;
//      std::cout << key << '\n';
      if (key == "key1")
      {
        in >> inT{input.key1} >> del{':'};
        in >> key;
        if (key == "key2")
        {
          in >> dbl{input.key2} >> del{':'} >> label{"key3"} >> str{input.key3} >> del{':'};
        }
        else if (key == "key3")
        {
          in >> str{input.key3} >> del{':'} >> label{"key2"} >> dbl{input.key2} >> del{':'};
        }
        else
        {
          return in;
        }
      }
      else if (key == "key2")
      {
        in >> dbl{input.key2} >> del{':'};
        in >> key;
        if (key == "key1")
        {
          in >> inT{input.key1} >> del{':'} >> label{"key3"} >> str{input.key3} >> del{':'};
        }
        else if (key == "key3")
        {
          in >> str{input.key3} >> del{':'} >> label{"key1"} >> inT{input.key1} >> del{':'};
        }
        else
        {
          return in;
        }
      }
      else if (key == "key3")
      {
        in >> str{input.key3} >> del{':'};
        in >> key;
        if (key == "key2")
        {
          in >> dbl{input.key2} >> del{':'} >> label{"key1"} >> inT{input.key1} >> del{':'};
        }
        else if (key == "key1")
        {
          in >> inT{input.key1} >> del{':'} >> label{"key2"} >> dbl{input.key2} >> del{':'};
        }
        else
        {
          return in;
        }
      }
      else
      {
        return in;
      }
/*
      in >> label{"key1"} >> inT{input.key1} >> del{':'};
      in >> label{"key2"} >> dbl{input.key2} >> del{':'};
      in >> label{"key3"} >> str{input.key3};
      in >> del{':'} >> del{')'};
*/
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
// (:key1 89ull:key2 (:N -2:D 3:):key3 "Data":)
    out << "(:key1 " << data.key1;
    out << ":key2 " << data.key2;
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
  }
}

//std::vector<lopatina::DataStruct> sortData(std::vector<lopatina::DataStruct> & data)
void sortData(std::vector<lopatina::DataStruct> & data)
{
  std::vector<lopatina::DataStruct> new_data;
  new_data.push_back(data.front());
  for (auto ptr = data.cbegin(); ptr != data.cend(); ++ptr)
  {
    std::cout << (*ptr).key1 << '\n';
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
  std::cout << "DATA: \n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );
  return 0;
/*
  lopatina::DataStruct d(0, 0);
  while (!(std::cin.eof()))
  {
    if (!(std::cin >> d))
    {
      std::cin.clear(std::ios::goodbit);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
      std::cout << d << '\n';
      return 0;
    }
  }

/*
  int a = 0, b = 0;
  char c = 0;
  while (!(std::cin.eof()))
  {
    if (!(std::cin >> a >> b))
    {
      std::cin.clear(std::ios::goodbit);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
      std::cout << a << ' ' << b << '\n';
      return 0;
    }
  }
*/
}
