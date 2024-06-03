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
  for (size_t i = 0; i < count; ++i)
  {
    Point point;
    in >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
    if (in)
    {
      polygon.points.push_back(point);
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
//  std::vector<Point> points = polygon.points;
  Point * last_point = std::addressof(points.back());
  using namespace std::placeholders;
  std::vector<int> x1y2;
  std::vector<int> y1x2;
  auto iter1 = std::transform(std::begin(points), std::end(points), std::back_inserter(x1y2), std::bind(multi1, _1, last_point));
  auto iter2 = std::transform(std::begin(points), std::end(points), std::back_inserter(y1x2), std::bind(multi2, _1, last_point));
  double area = (std::abs(std::accumulate(std::begin(x1y2), std::end(x1y2),0) - std::accumulate(std::begin(y1x2), std::end(y1x2),0))) / 2;
  return area;
}

double sumArea(double init, Polygon & polygon, int flag_is_even)
{
  if (flag_is_even == 1)
  {
    if (polygon.points.size() % 2 == 0)
    {
      return init + areaCount(polygon.points);
    }
  }
  else if (flag_is_even == 0)
  {
    if (polygon.points.size() % 2 != 0)
    {
      return init + areaCount(polygon.points);
    }
  }
  return init;
}

double sumAreaNum(double init, Polygon & polygon, int num)
{
  if (polygon.points.size() == num)
  {
    return init + areaCount(polygon.points);
  }
  return init;
}

double countAreaMean(double init, Polygon & polygon)
{
  double area = areaCount(polygon.points);
  return init + area;
}

void areaEven(std::vector <Polygon> & figures)
{
  using namespace std::placeholders;
  double sum = std::accumulate(std::begin(figures), std::end(figures), 0, std::bind(sumArea, _1, _2, 1));
  std::cout << "AREA EVEN: " << sum << '\n';
}

void areaOdd(std::vector <Polygon> & figures)
{
  using namespace std::placeholders;
  double sum = std::accumulate(std::begin(figures), std::end(figures), 0, std::bind(sumArea, _1, _2, 0));
  std::cout << "AREA ODD: " << sum << '\n';
}

void areaMean(std::vector <Polygon> & figures)
{
  using namespace std::placeholders;
  double sum = std::accumulate(std::begin(figures), std::end(figures), 0, countAreaMean);
  double sum_mean = sum / figures.size();
  std::cout << "AREA MEAN: " << sum_mean << '\n';
}

void areaNum(std::vector <Polygon> & figures, int num)
{
  using namespace std::placeholders;
  double sum = std::accumulate(std::begin(figures), std::end(figures), 0, std::bind(sumAreaNum, _1, _2, num));
  std::cout << "AREA NUM: " << sum << '\n';
}
//-------
namespace lopatina
{
  void areaCmd(std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
  {
    out << "AREA\n";
    using namespace std::placeholders;
    std::map<std::string, std::function<void()>> cmds;
    cmds["EVEN"] = std::bind(areaEven, figures);
    cmds["ODD"] = std::bind(areaOdd, figures);
    cmds["MEAN"] = std::bind(areaMean, figures);
    std::string cmd;
    in >> cmd;
    if ((cmd == "MEAN") && figures.empty())
    {
      throw std::logic_error("No figure");
    }
    try
    {
      cmds.at(cmd)();
    }
    catch (const std::out_of_range &)
    {
      int num = std::stoull(cmd);
      areaNum(figures, num);
    }
  }

  void maxCmd(const std::vector<Polygon>, std::istream &, std::ostream & out)
  {
    out << "MAX\n";
  }

  void minCmd(const std::vector<Polygon>, std::istream &, std::ostream & out)
  {
    out << "MIN\n";
  }

  void countCmd(const std::vector<Polygon>, std::istream &, std::ostream & out)
  {
    out << "COUNT\n";
  }
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
    cmds["AREA"] = std::bind(lopatina::areaCmd, figures, _1, _2);
    cmds["MAX"] = std::bind(lopatina::maxCmd, figures, _1, _2);
    cmds["MIN"] = std::bind(lopatina::minCmd, figures, _1, _2);
    cmds["COUNT"] = std::bind(lopatina::countCmd, figures, _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (...)
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
/*
  std::cout << "AREAS:\n";
  for (auto iter = figures.begin(); iter != figures.end(); ++iter)
  {
    std::cout << areaCount((*iter).points) << '\n';
  }
*/
  return 0;
}
