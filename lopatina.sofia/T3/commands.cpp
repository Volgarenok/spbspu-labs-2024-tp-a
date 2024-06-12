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
  cmds["EVEN"] = std::bind(areaEven, figures);
  cmds["ODD"] = std::bind(areaOdd, figures);
  cmds["MEAN"] = std::bind(areaMean, figures);
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
    out << areaNum(figures, num) << '\n';
  }
}

void lopatina::maxCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function<double()>> cmds_area;
  std::map<std::string, std::function<size_t()>> cmds_vertexes;
  cmds_area["AREA"] = std::bind(maxArea, figures);
  cmds_vertexes["VERTEXES"] = std::bind(maxVertexes, figures);
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
  cmds_area["AREA"] = std::bind(minArea, figures);
  cmds_vertexes["VERTEXES"] = std::bind(minVertexes, figures);
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
  cmds["EVEN"] = std::bind(countEven, figures);
  cmds["ODD"] = std::bind(countOdd, figures);
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
    out << countNum(figures, num) << '\n';
  }
}

class Counter
{
public:
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
private:
  size_t counter = 0;
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
  const lopatina::Polygon * last_polygone_ptr = std::addressof(figures.back());
  std::transform(std::begin(figures), std::end(figures), std::back_inserter(counters), std::bind(counter, _1, given_figure, last_polygone_ptr));
  out << *(std::max_element(std::begin(counters), std::end(counters))) << '\n';
}

size_t countForRmEcho(size_t init, const size_t & counter)
{
  if (counter > 0)
  {
    return init + counter - 1;
  }
  return init;
}

bool rmEchoPredicate(const lopatina::Polygon & polygon1, const lopatina::Polygon & polygon2, const lopatina::Polygon & given_polygon)
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
  std::vector<size_t> counters;
  Counter counter;
  const lopatina::Polygon * last_polygone_ptr = std::addressof(figures.back());
  std::transform(std::begin(figures), std::end(figures), std::back_inserter(counters), std::bind(counter, _1, given_figure, last_polygone_ptr));
  size_t sum_rm = std::accumulate(std::begin(counters), std::end(counters), 0, countForRmEcho);
  auto iter = std::unique(std::begin(figures), std::end(figures), std::bind(rmEchoPredicate, _1, _2, given_figure));
  figures.resize(std::distance(std::begin(figures), iter));
  out << sum_rm << '\n';
}

void lopatina::rightShapesCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  out << "RIGHTSHAPES\n";
}

