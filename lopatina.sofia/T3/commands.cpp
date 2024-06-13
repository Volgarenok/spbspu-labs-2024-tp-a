#include "commands.hpp"
#include <iomanip>
#include <algorithm>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>
#include "implementation_cmds.hpp"
#include "stream_guard.hpp"

void lopatina::areaCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function<double()>> cmds;
  cmds["EVEN"] = std::bind(doAreaEven, figures);
  cmds["ODD"] = std::bind(doAreaOdd, figures);
  cmds["MEAN"] = std::bind(doAreaMean, figures);
  std::string cmd;
  in >> cmd;
  if ((cmd == "MEAN") && figures.empty())
  {
    throw std::logic_error("No figures");
  }
  StreamGuard fmtguard(out);
  out << std::fixed << std::setprecision(1);
  try
  {
    out << cmds.at(cmd)() << '\n';
  }
  catch (const std::out_of_range &)
  {
    size_t num = std::stoull(cmd);
    if (num < 3)
    {
      throw std::logic_error("Not figure");
    }
    out << doAreaNum(figures, num) << '\n';
  }
}

void lopatina::maxCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function<double()>> cmds_area;
  std::map<std::string, std::function<size_t()>> cmds_vertexes;
  cmds_area["AREA"] = std::bind(doMaxArea, figures);
  cmds_vertexes["VERTEXES"] = std::bind(doMaxVertexes, figures);
  std::string cmd;
  in >> cmd;
  if (figures.empty())
  {
    throw std::logic_error("No figures");
  }
  try
  {
    out << cmds_vertexes.at(cmd)() << '\n';
  }
  catch (const std::out_of_range &)
  {
    StreamGuard fmtguard(out);
    out << std::fixed << std::setprecision(1);
    out << cmds_area.at(cmd)() << '\n';
  }
}

void lopatina::minCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function<double()>> cmds_area;
  std::map<std::string, std::function<size_t()>> cmds_vertexes;
  cmds_area["AREA"] = std::bind(doMinArea, figures);
  cmds_vertexes["VERTEXES"] = std::bind(doMinVertexes, figures);
  std::string cmd;
  in >> cmd;
  if (figures.empty())
  {
    throw std::logic_error("No figures");
  }
  try
  {
    out << cmds_vertexes.at(cmd)() << '\n';
  }
  catch (const std::out_of_range &)
  {
    StreamGuard fmtguard(out);
    out << std::fixed << std::setprecision(1);
    out << cmds_area.at(cmd)() << '\n';
  }
}

void lopatina::countCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function<size_t()>> cmds;
  cmds["EVEN"] = std::bind(doCountEven, figures);
  cmds["ODD"] = std::bind(doCountOdd, figures);
  std::string cmd;
  in >> cmd;
  try
  {
    out << cmds.at(cmd)() << '\n';
  }
  catch (const std::out_of_range &)
  {
    size_t num = std::stoull(cmd);
    if (num < 3)
    {
      throw std::logic_error("Not figure");
    }
    out << doCountNum(figures, num) << '\n';
  }
}

struct Counter
{
  size_t counter{0};
  size_t operator()(const lopatina::Polygon & polygon, const lopatina::Polygon & given_polygon, const lopatina::Polygon * const last)
  {
    if (polygon == given_polygon)
    {
      ++counter;
      const lopatina::Polygon * ptr = std::addressof(polygon);
      if (ptr == last)
      {
        return counter;
      }
      return 0;
    }
    size_t counter_temp = counter;
    counter = 0;
    return counter_temp;
  }
};


void lopatina::maxSeqCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  Polygon given_figure;
  in >> given_figure;
  if (!in)
  {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::logic_error("Invalid given figure");
  }
  using namespace std::placeholders;
  std::vector<size_t> counters;
  Counter counter;
  const lopatina::Polygon * last_pol_ptr = std::addressof(figures.back());
  std::transform(std::begin(figures), std::end(figures), std::back_inserter(counters), std::bind(counter, _1, given_figure, last_pol_ptr));
  out << *(std::max_element(std::begin(counters), std::end(counters))) << '\n';
}

bool isEquivalent(const lopatina::Polygon & polygon1, const lopatina::Polygon & polygon2, const lopatina::Polygon & given_polygon)
{
  if ((polygon1 == polygon2) && (polygon1 == given_polygon))
  {
    return true;
  }
  return false;
}

void lopatina::rmEchoCmd(std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  Polygon given_figure;
  in >> given_figure;
  if (!in)
  {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::logic_error("Invalid given figure");
  }
  using namespace std::placeholders;
  size_t size1 = figures.size();
  auto iter = std::unique(std::begin(figures), std::end(figures), std::bind(isEquivalent, _1, _2, given_figure));
  figures.resize(std::distance(std::begin(figures), iter));
  out << size1 - figures.size() << '\n';
}

struct RightAngle
{
  lopatina::Point point1;
  lopatina::Point point2;
  bool operator()(const lopatina::Point & point3)
  {
    lopatina::Point vector1 = {point2.x - point1.x, point2.y - point1.y};
    lopatina::Point vector2 = {point3.x - point1.x, point3.y - point1.y};
    point2 = point1;
    point1 = point3;
    return vector1.x * vector2.x + vector1.y * vector2.y == 0;
  }
};

bool hasRightAngle(const lopatina::Polygon & polygon)
{
  RightAngle angle{polygon.points[0], polygon.points[1]};
  bool is_right = std::any_of(std::rbegin(polygon.points), std::rend(polygon.points), angle);
  return is_right;
}

void lopatina::rightShapesCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  size_t counter = std::count_if(std::begin(figures), std::end(figures), hasRightAngle);
  out << counter << "\n";
}

