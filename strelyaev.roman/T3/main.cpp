#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>
#include <functional>
#include <map>

namespace strelyaev
{
  struct Delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, Delimiter&& exp);
}

std::istream& strelyaev::operator>>(std::istream& in, Delimiter&& exp)
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

//////////////////////////////////////////////////////////////////

namespace strelyaev
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream& operator>>(std::istream&, Point&);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream&, Polygon&);

  size_t size_getter(const Polygon&);
}
///////////////////////////////////////////////////////////////////
std::istream& strelyaev::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = Delimiter;
  return in >> del{'('} >> point.x >> del{';'} >> point.y >> del{')'};
}

std::istream& strelyaev::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t size = 0;
  in >> size;
  if (size < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >(in), size, std::back_inserter(points));
  if (in.good())
  {
    poly.points = points;
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return in;
}

size_t strelyaev::size_getter(const Polygon& poly)
{
  return poly.points.size();
}

////////////////////////////////////////////////////////////////////////////
namespace strelyaev
{
  size_t get_area(const std::vector< Point >&);

  void count_cmd(std::ostream&,
      std::istream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void area_cmd(std::ostream&,
      std::istream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);
}



void strelyaev::count_cmd(std::ostream& out,
    std::istream& in,
    const std::vector< Polygon >& polygons_vector,
    const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  using namespace std::placeholders;
  std::string str_args = "";
  in >> str_args;
  std::function< bool(const Polygon&) > pred;
  try
  {
    size_t ver = std::stoull(str_args);
    pred = std::bind(std::equal_to< size_t >{}, std::bind(size_getter, _1), ver);
  }
  catch (...)
  {
    pred = args.at(str_args);
  }
  out << std::count_if(polygons_vector.cbegin(), polygons_vector.cend(), pred);
}

void strelyaev::area_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector,
      const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  std::string str_args = "";
  in >> str_args;
  

}

size_t strelyaev::get_area(const Polygon& poly)
{
  std::vector< Point > tmp;
  std::copy(poly.points.cbegin(), poly.points.cend(), std::back_inserter(tmp));
  tmp.push_back(tmp[0]);
  {
  
  }
}

int main(int argc, char** argv) //perms, maxseq
{
  using namespace strelyaev;
  if (false/*argc < 1*/)
  {
    std::cerr << "not enough arguments\n";
    return 1;
  }
  std::ifstream input("input.txt");
  if (!input.is_open())
  {
    std::cerr << "file error\n";
    return 1;
  }
  std::vector< Polygon > polygons_vector;
  while (!input.eof())
  {
    std::copy(std::istream_iterator< Polygon >(input), std::istream_iterator< Polygon >(), std::back_inserter(polygons_vector));
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function< bool(const Polygon&) > > args;
  {
    using namespace std::placeholders;
    args["EVEN"] = std::bind(std::equal_to< double >{}, std::bind(std::modulus< size_t >{}, std::bind(size_getter, _1), 2), 0);
    args["ODD"] = std::bind(std::not_equal_to< double >{}, std::bind(std::modulus< size_t >{}, std::bind(size_getter, _1), 2), 0);
  }

  std::map< std::string, std::function< void(std::ostream&, std::istream&, const std::vector< Polygon >&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["COUNT"] = std::bind(count_cmd, _1, _2, _3, args);
  }
  std::string cmd_name = "";
  while (std::cin >> cmd_name)
  {
    try
    {
      cmds.at(cmd_name)(std::cout, std::cin, polygons_vector);
      std::cout << "\n";
    }
    catch (const std::exception& e)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  return 0;
}