#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <iomanip>
#include <stdexcept>

namespace strelyaev
{
  class StreamGuard
  {
  public:
    StreamGuard(std::basic_ios< char >& s);
    ~StreamGuard();

  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

strelyaev::StreamGuard::StreamGuard(std::basic_ios< char >& s):
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{}
strelyaev::StreamGuard::~StreamGuard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}

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
  int get_x(const Point&);
  int get_y(const Point&);
  double get_area(const Polygon&);
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

int strelyaev::get_x(const Point& p)
{
  return p.x;
}

int strelyaev::get_y(const Point& p)
{
  return p.y;
}

double strelyaev::get_area(const Polygon& poly)
{
  std::vector< Point > tmp = poly.points;
  tmp.push_back(tmp[0]);
  {
    using namespace std::placeholders;
    std::function< int(const Point&, const Point&) > multiply_x_y = std::bind(std::multiplies< int >{}, std::bind(get_x, _1), std::bind(get_y, _2));
    std::function< int(const Point&, const Point&) > gauss_func = std::bind(std::minus< int >{}, std::bind(multiply_x_y, _1, _2), std::bind(multiply_x_y, _2, _1));
    std::vector< int > determ;
    std::transform(++tmp.begin(), tmp.end(), tmp.begin(), std::back_inserter(determ), gauss_func);
    return std::abs(std::accumulate(determ.cbegin(), determ.cend(), 0.0)) / 2.0;
  }
}

////////////////////////////////////////////////////////////////////////////
namespace strelyaev
{
  void count_cmd(std::ostream&,
      std::istream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void area_cmd(std::ostream&,
      std::istream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void find_area(std::ostream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

void find_verts(std::ostream& out,
    const std::vector< Polygon >& polygons_vector,
    std::function< size_t(const std::vector< size_t >&) > func);

void max_cmd(std::ostream& out, std::istream& in,
    const std::vector< Polygon >& polygons_vector);

void min_cmd(std::ostream& out, std::istream& in,
    const std::vector< Polygon >& polygons_vector);

void perms_cmd(std::ostream& out, std::istream& in,
    const std::vector< Polygon >& polygons_vector);

bool permutation_polygons(const Polygon& lhs, const Polygon& rhs);
}
////////////////////////////////////////////////////////////////////////////////////
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
  std::function< bool(const Polygon&) > pred;
  std::string str_args = "";
  in >> str_args;
  int devide = 1;
  if (str_args == "MEAN")
  {
    devide = 2;
  }
  try
  {
    using namespace std::placeholders;
    size_t ver = std::stoull(str_args);
    pred = std::bind(std::equal_to< size_t >{}, std::bind(size_getter, _1), ver);
  }
  catch (...)
  {
    pred = args.at(str_args);
  }
  std::vector< Polygon > area_polygons;
  std::vector< double > areas;
  std::copy_if(polygons_vector.cbegin(), polygons_vector.cend(), std::back_inserter(area_polygons), pred);
  std::transform(area_polygons.cbegin(), area_polygons.cend(), std::back_inserter(areas), get_area);
  out << std::accumulate(areas.begin(), areas.end(), 0) / devide;
}

void strelyaev::max_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector)
{
  StreamGuard s_guard(out);
  std::string str_args = "";
  in >> str_args;
  if (str_args == "AREA")
  {
    std::vector< double > areas;
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), get_area);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::max_element(areas.begin(), areas.end());
  }
  if (str_args == "VERTEXES")
  {
    std::vector< size_t > areas;
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), size_getter);
    out << *std::max_element(areas.begin(), areas.end());
  }
}

void strelyaev::min_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector)
{
  StreamGuard s_guard(out);
  std::string str_args = "";
  in >> str_args;
  if (str_args == "AREA")
  {
    std::vector< double > areas;
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), get_area);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::min_element(areas.begin(), areas.end());
  }
  if (str_args == "VERTEXES")
  {
    std::vector< size_t > areas;
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), size_getter);
    out << *std::min_element(areas.begin(), areas.end());
  }
}

bool strelyaev::permutation_polygons(const Polygon& lhs, const Polygon& rhs)
{
  using namespace std::placeholders;
  auto compare_x = std::bind(std::equal_to< int >{}, std::bind(get_x, _1), std::bind(get_x, _2));
  auto compare_y = std::bind(std::equal_to< int >{}, std::bind(get_y, _1), std::bind(get_y, _2));
  auto compare_points = std::bind(std::logical_and<>{}, std::bind(compare_x, _1, _2), std::bind(compare_y, _1, _2));
  return std::is_permutation(rhs.points.cbegin(), rhs.points.cend(), lhs.points.cbegin(), lhs.points.cend(), compare_points);
}

void strelyaev::perms_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polys)
{
  Polygon poly;
  in >> poly;
  std::vector< Polygon > correct;
  using namespace std::placeholders;
  std::function< bool(const Polygon&) > pred = std::bind(std::equal_to< size_t >{}, std::bind(size_getter, _1), poly.points.size());
  std::copy_if(polys.cbegin(), polys.cend(), std::back_inserter(correct), pred);
  if (correct.empty())
  {
    throw std::out_of_range("Something is wrong with a command");
  }
  pred = std::bind(permutation_polygons, poly, _1);
  out << std::count_if(correct.cbegin(), correct.cend(), pred);
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
    args["MEAN"] = std::bind(std::equal_to< int >{}, 1, 1);
  }

  std::map< std::string, std::function< bool(const Polygon&) > > args_count;
  args_count["EVEN"] = args["EVEN"];
  args_count["ODD"] = args["ODD"];

  std::map< std::string, std::function< void(std::ostream&, std::istream&, const std::vector< Polygon >&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["COUNT"] = std::bind(count_cmd, _1, _2, _3, args_count);
    cmds["AREA"] = std::bind(area_cmd, _1, _2, _3, args);
    cmds["MAX"] = std::bind(max_cmd, _1, _2, _3);
    cmds["MIN"] = std::bind(min_cmd, _1, _2, _3);
    cmds["PERMS"] = std::bind(perms_cmd, _1, _2, _3);
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
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
