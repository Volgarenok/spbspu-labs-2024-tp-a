#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>
#include <iterator>
namespace lazareva
{

  struct Delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, Delimiter&& exp)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    char c = 0;
    in >> c;
    if (c != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  return in;
  }

  struct DataStruct
  {
    double key1;
    long long key2;
    std::string key3;
  };

  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    if (lhs.key2 != rhs.key2)
    {
      return lhs.key2 < rhs.key2;
    }
    return lhs.key3.size() < rhs.key3.size();
  }

  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }

    using del = lazareva::Delimiter;
    in >> del{'('};
    for (int b = 0; b < 3; b++)
    {
      in  >> del{':'} >> del{'k'} >> del{'e'} >> del{'y'};
      int i = 0;
      in >> i;
      if (i == 1)
      {
        double value = 0;
        in >> value;
        data.key1 = value;
        in >> del{'d'};
      }
      else if (i == 2)
      {
        long long value = 0;
        in >> value;
        data.key2 = value;
        in >> del{'l'} >> del{'l'};
      }
      else if (i == 3)
      {
        std::string value = "";
        in >> del{'"'};
        std::getline(in, value, '\"');
        data.key3 = value;
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> del{':'} >> del{')'};
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& data)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    out << std::fixed;
    out << "(:key1 " << std::setprecision(1) <<  data.key1 << "d:key2 " << data.key2 << "ll:key3 \"" << data.key3 << "\":)";
    return out;
  }
}


int main()
{
  using lazareva::DataStruct;
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    using input_it = std::istream_iterator< DataStruct >;
    std::copy(input_it{std::cin}, input_it{}, std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  using output_it = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), output_it{std::cout, "\n"});
}
