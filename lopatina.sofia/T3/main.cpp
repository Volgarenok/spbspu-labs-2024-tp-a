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

int multi1(const Point & point, const Point * const last)
{
  const Point * ptr = std::addressof(point);
  if (ptr != last)
  {
    int x1 = (*ptr).x;
    int y2 = (*(++ptr)).y;
    return x1 * y2;
  }
  return 0;
}

int multi2(const Point & point, const Point * const last)
{
  const Point * ptr = std::addressof(point);
  if (ptr != last)
  {
    int y1 = (*ptr).y;
    int x2 = (*(++ptr)).x;
    return y1 * x2;
  }
  return 0;
}

double areaCount(const Polygon & polygon)
{
  std::vector<Point> points = polygon.points;
  Point * last_point = std::addressof(points.back());
  using namespace std::placeholders;
  std::vector<int> x1y2;
  std::vector<int> y1x2;
  auto iter1 = std::transform(std::begin(points), std::end(points), std::back_inserter(x1y2), std::bind(multi1, _1, last_point));
  auto iter2 = std::transform(std::begin(points), std::end(points), std::back_inserter(y1x2), std::bind(multi2, _1, last_point));
  double area = (std::abs(std::accumulate(std::begin(x1y2), std::end(x1y2),0) - std::accumulate(std::begin(y1x2), std::end(y1x2),0))) / 2;
  return area;
}

double sumArea(double init, const Polygon & polygon)
{
  return init + areaCount(polygon);
}

bool isEven(const Polygon & polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool isOdd(const Polygon & polygon)
{
  return (!isEven(polygon));
}

bool isNum(const Polygon & polygon, size_t num)
{
  return (polygon.points.size() == num);
}

void areaEven(const std::vector <Polygon> & figures)
{
  using namespace std::placeholders;
  std::vector <Polygon> filter;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(filter), isEven);
  double sum = std::accumulate(std::begin(filter), std::end(filter), 0, sumArea);
  std::cout << "AREA EVEN: " << sum << '\n';
}

void areaOdd(const std::vector <Polygon> & figures)
{
  using namespace std::placeholders;
  std::vector <Polygon> filter;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(filter), isOdd);
  double sum = std::accumulate(std::begin(filter), std::end(filter), 0, sumArea);
  std::cout << "AREA ODD: " << sum << '\n';
}

void areaMean(const std::vector <Polygon> & figures)
{
  using namespace std::placeholders;
  double sum = std::accumulate(std::begin(figures), std::end(figures), 0, sumArea);
  double sum_mean = sum / figures.size();
  std::cout << "AREA MEAN: " << sum_mean << '\n';
}

void areaNum(const std::vector <Polygon> & figures, size_t num)
{
  using namespace std::placeholders;
  std::vector <Polygon> filter;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(filter), std::bind(isNum, _1, num));
  double sum = std::accumulate(std::begin(filter), std::end(filter), 0, sumArea);
  std::cout << "AREA NUM: " << sum << '\n';
}
//-------
namespace lopatina
{
  void areaCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
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
      size_t num = std::stoull(cmd);
      areaNum(figures, num);
    }
  }
}
//------
bool areaComp(const Polygon & first, const Polygon & second)
{
  return areaCount(first) < areaCount(second);
}
bool vertexesComp(const Polygon & first, const Polygon & second)
{
  return first.points.size() < second.points.size();
}

void maxArea(const std::vector<Polygon> & figures)
{
  auto max_figure = std::max_element(std::begin(figures), std::end(figures), areaComp);
  double max_area = areaCount(*max_figure);
  std::cout << "MAX AREA: " << max_area << '\n';
}
void maxVertexes(const std::vector<Polygon> & figures)
{
  auto max_figure = std::max_element(std::begin(figures), std::end(figures), vertexesComp);
  double max_vertexes = (*max_figure).points.size();
  std::cout << "MAX VERTEXES: " << max_vertexes << '\n';
}

void minArea(const std::vector<Polygon> & figures)
{
  auto min_figure = std::min_element(std::begin(figures), std::end(figures), areaComp);
  double min_area = areaCount(*min_figure);
  std::cout << "MIN AREA: " << min_area << '\n';
}
void minVertexes(const std::vector<Polygon> & figures)
{
  auto min_figure = std::min_element(std::begin(figures), std::end(figures), vertexesComp);
  double min_vertexes = (*min_figure).points.size();
  std::cout << "MIN VERTEXES: " << min_vertexes << '\n';
}

namespace lopatina
{
  void maxCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
  {
    out << "MAX\n";
    using namespace std::placeholders;
    std::map<std::string, std::function<void()>> cmds;
    cmds["AREA"] = std::bind(maxArea, figures);
    cmds["VERTEXES"] = std::bind(maxVertexes, figures);
    std::string cmd;
    in >> cmd;
    if (figures.empty())
    {
      throw std::logic_error("No figures");
    }
    cmds.at(cmd)();
  }

  void minCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
  {
    out << "MIN\n";
    using namespace std::placeholders;
    std::map<std::string, std::function<void()>> cmds;
    cmds["AREA"] = std::bind(minArea, figures);
    cmds["VERTEXES"] = std::bind(minVertexes, figures);
    std::string cmd;
    in >> cmd;
    if (figures.empty())
    {
      throw std::logic_error("No figures");
    }
    cmds.at(cmd)();
  }
}

namespace lopatina
{
  void countCmd(const std::vector<Polygon>, std::istream &, std::ostream & out)
  {
    out << "COUNT\n";
/*
    using namespace std::placeholders;
    std::map<std::string, std::function<void()>> cmds;
    cmds["EVEN"] = std::bind(countEven, figures);
    cmds["ODD"] = std::bind(countOdd, figures);
    std::string cmd;
    in >> cmd;
    try
    {
      cmds.at(cmd)();
    }
    catch (const std::out_of_range &)
    {
      size_t num = std::stoull(cmd);
      countNum(figures, num);
    }*/
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
