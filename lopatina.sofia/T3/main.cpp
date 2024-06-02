#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>

struct Point
{
  int x, y;
};

struct Polygon
{
  std::vector<Point> points;
};

//------------
class StreamGuard
{
public:
  explicit StreamGuard(std::basic_ios< char > & stream):
    stream_(stream),
    fill_(stream.fill()),
    precision_(stream.precision()),
    flags_(stream.flags())
  {}
  ~StreamGuard()
  {
    stream_.fill(fill_);
    stream_.precision(precision_);
    stream_.flags(flags_);
  }
private:
  std::basic_ios< char > & stream_;
  char fill_;
  std::streamsize precision_;
  std::basic_ios< char >::fmtflags flags_;
};

struct DelimiterIO
{
  char exp;
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
//
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
//----
std::istream & operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Polygon polygon;
  int count = 0;
  in >> count;
//  std::cout << count <<'\n';
  for (size_t i = 0; i < count; ++i)
  {
    Point point;
    in >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
    if (in)
    {
      polygon.points.push_back(point);
//      std::cout << point.x << ' ' << point.y << '\n';
    }
  }
  if (in)
  {
    dest = polygon;
  }
  return in;
}


std::ostream & operator<<(std::ostream & out, const Polygon & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard fmtguard(out);
  for (auto iter = data.points.begin(); iter != data.points.end(); ++iter)
  {
    out << "(" << (*iter).x << ";" << (*iter).y << ") ";
  }
  return out;
}

//-------
namespace lopatina
{
  void area(const std::vector<Polygon>, std::istream &, std::ostream & out)
  {
    out << "AREA\n";
  }

  void max(const std::vector<Polygon>, std::istream &, std::ostream & out)
  {
    out << "MAX\n";
  }

  void min(const std::vector<Polygon>, std::istream &, std::ostream & out)
  {
    out << "MIN\n";
  }

  void count(std::istream &, std::ostream & out)
  {
    out << "COUNT\n";
  }
}

int multi1(Point & point, const Point * const last)
{
  Point * ptr = std::addressof(point);
  if (ptr != last)
  {
    int x1 = point.x;
    int y2 = (*(++ptr)).y;
    return x1 * y2;
  }
  return 0;
}

int multi2(Point & point, const Point * const last)
{
  Point * ptr = std::addressof(point);
  if (ptr != last)
  {
    int y1 = point.y;
    int x2 = (*(++ptr)).x;
    return y1 * x2;
  }
  return 0;
}

double areaCount(std::vector<Point> & points)
{
  Point * last_point = std::addressof(points.back());
  using namespace std::placeholders;
  std::vector<int> x1y2;
  std::vector<int> y1x2;
  auto iter1 = std::transform(std::begin(points), std::end(points), std::back_inserter(x1y2), std::bind(multi1, _1, last_point));
  auto iter2 = std::transform(std::begin(points), std::end(points), std::back_inserter(y1x2), std::bind(multi2, _1, last_point));
  double area = (std::abs(std::accumulate(std::begin(x1y2), std::end(x1y2),0) - std::accumulate(std::begin(y1x2), std::end(y1x2),0))) / 2;
  return area;
}


int main(int argc, char ** argv)
{
  if (argc < 2)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "No such file\n";
    return 1;
  }
//read data
  std::vector<Polygon> figures;
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator<Polygon>{input},
      std::istream_iterator<Polygon>{},
      std::back_inserter(figures)
    );
    if (!input && !input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::map<std::string, std::function<void(std::istream &, std::ostream &)>> cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(lopatina::area, figures, _1, _2);
    cmds["MAX"] = std::bind(lopatina::max, figures, _1, _2);
    cmds["MIN"] = std::bind(lopatina::min, figures, _1, _2);
    cmds["COUNT"] = lopatina::count;
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::copy(
    std::begin(figures),
    std::end(figures),
    std::ostream_iterator<Polygon>(std::cout, "\n")
  );
  std::cout << "AREAS:\n";
  for (auto iter = figures.begin(); iter != figures.end(); ++iter)
  {
    std::cout << areaCount((*iter).points) << '\n';
  }
  return 0;
}
