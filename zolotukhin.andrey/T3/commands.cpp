#include "commands.hpp"
#include <functional>
#include <algorithm>
#include <map>
#include "streamGuard.hpp"
#include <cmath>
#include <set>
#include <iomanip>

void getMaxSeq(std::istream& input, std::ostream& output, const std::vector<zolotukhin::Polygon>& polygons)
{
  zolotukhin::Polygon pattern;
  input >> pattern;
  if (pattern.points.size() < 3)
  {
    throw std::invalid_argument("");
  }
  std::set<zolotukhin::Point> same(pattern.points.cbegin(), pattern.points.cend());
  if (same.size() != pattern.points.size())
  {
    throw std::invalid_argument("");
  }
  int cur_seq = 0;
  int max_seq = 0;
  for (auto & p : polygons)
  {
    if (p == pattern)
    {
      cur_seq++;
    }
    else if (cur_seq > max_seq)
    {
      max_seq = cur_seq;
      cur_seq = 0;
    }
  }
  output << std::fixed << std::setprecision(1) << max_seq;
}

bool isEven(const zolotukhin::Polygon& p)
{
  return p.points.size() % 2 == 0;
}

bool isOdd(const zolotukhin::Polygon& p)
{
  return p.points.size() % 2 == 1;
}

bool rightVertex(const zolotukhin::Polygon& p, size_t vertexNum)
{
  return p.points.size() == vertexNum;
}

double getDistance(const zolotukhin::Point& p1, const zolotukhin::Point& p2)
{
  return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

bool isRectangleTriangle(const zolotukhin::Point& p1, const zolotukhin::Point& p2, const zolotukhin::Point& p3)
{
  double a = getDistance(p1, p2);
  double b = getDistance(p2, p3);
  double c = getDistance(p1, p3);
  return std::pow(a, 2) - std::pow(b, 2) - std::pow(c, 2) <= 1e-9;
}

bool isRightShape(const zolotukhin::Polygon& poly)
{
  int s = 0;
  s += isRectangleTriangle(poly.points[poly.points.size() - 1], poly.points[0], poly.points[1]);
  s += isRectangleTriangle(poly.points[poly.points.size() - 2], poly.points[poly.points.size() - 1], poly.points[0]);
  for (size_t i = 1; i < poly.points.size() - 1; i++)
  {
    s += isRectangleTriangle(poly.points[i - 1], poly.points[i], poly.points[i + 1]);
  }
  return s;
}

void zolotukhin::doRightShapes(std::vector<zolotukhin::Polygon>& polygons, std::ostream& out)
{
  int cnt = 0;
  for (auto& poly : polygons)
  {
    if (isRightShape(poly)) cnt++;
  }
  out << cnt << '\n';
}

double calcAreaEven(const std::vector<zolotukhin::Polygon>& polygons)
{
  std::vector<zolotukhin::Polygon> tmp;
  std::vector<double> a;
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tmp), isEven);
  std::transform(tmp.cbegin(), tmp.cend(), std::back_inserter(a), std::bind(zolotukhin::getArea, std::placeholders::_1));
  return std::accumulate(a.cbegin(), a.cend(), 0.0);
}

double calcAreaOdd(const std::vector<zolotukhin::Polygon>& polygons)
{
  std::vector<zolotukhin::Polygon> tmp;
  std::vector<double> a;
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tmp), isOdd);
  std::transform(tmp.cbegin(), tmp.cend(), std::back_inserter(a), std::bind(zolotukhin::getArea, std::placeholders::_1));
  return std::accumulate(a.cbegin(), a.cend(), 0.0);
}

double calcAreaMean(const std::vector<zolotukhin::Polygon>& polygons)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  double totalArea = std::accumulate(
      polygons.begin(), polygons.end(), 0.0,
      std::bind(std::plus<>(), std::placeholders::_1,
      std::bind(&zolotukhin::getArea, std::placeholders::_2)));
  return totalArea / polygons.size();
}

double calcAreaForVertices(const std::vector<zolotukhin::Polygon>& polygons, size_t vertexNum)
{
  std::vector<zolotukhin::Polygon> tmp;
  std::vector<double> a;
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tmp), std::bind(rightVertex, std::placeholders::_1, vertexNum));
  std::transform(tmp.cbegin(), tmp.cend(), std::back_inserter(a), std::bind(zolotukhin::getArea, std::placeholders::_1));
  return std::accumulate(a.cbegin(), a.cend(), 0.0);
}

void zolotukhin::doArea(std::vector<Polygon>& poly, std::istream& in, std::ostream& out)
{
  double result = 0.0;
  std::string subcommand;
  in >> subcommand;
  std::map<std::string, std::function<double()>> cmds;
  using namespace std::placeholders;
  cmds["EVEN"] = std::bind(calcAreaEven, std::ref(poly));
  cmds["ODD"] = std::bind(calcAreaOdd, std::ref(poly));
  cmds["MEAN"] = std::bind(calcAreaMean, std::ref(poly));
  size_t vertexNum = 0;
  try
  {
    vertexNum = std::stoull(subcommand);
    if (vertexNum < 3)
    {
      throw std::logic_error("<INCORRECT VERTEX NUMBER>");
    }
    result = calcAreaForVertices(poly, vertexNum);
  }
  catch (const std::invalid_argument&)
  {
    if (cmds.find(subcommand) != cmds.end())
    {
      result = cmds[subcommand]();
    }
    else
    {
      throw std::invalid_argument("<INVALID SUBARGUMENT>");
    }
  }
  out << result << '\n';
}

double maxArea(const std::vector<zolotukhin::Polygon>& polygons)
{
  std::vector<double> a;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(a), std::bind(zolotukhin::getArea, std::placeholders::_1));
  return *std::max_element(a.cbegin(), a.cend());
}

double minArea(const std::vector<zolotukhin::Polygon>& polygons)
{
  std::vector<double> a;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(a), std::bind(zolotukhin::getArea, std::placeholders::_1));
  return *std::min_element(a.cbegin(), a.cend());
}

double getVert(const zolotukhin::Polygon p)
{
  return p.points.size();
}

double maxVertexes(const std::vector<zolotukhin::Polygon>& polygons)
{
  std::vector<double> a;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(a), std::bind(getVert, std::placeholders::_1));
  return *std::max_element(a.cbegin(), a.cend());
}

double minVertexes(const std::vector<zolotukhin::Polygon>& polygons)
{
  std::vector<double> a;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(a), std::bind(getVert, std::placeholders::_1));
  return *std::min_element(a.cbegin(), a.cend());
}

void zolotukhin::doMax(std::vector<Polygon>& poly, std::istream& in, std::ostream& out)
{
  double result = 0.0;
  std::string subcommand;
  in >> subcommand;
  std::map<std::string, std::function<double()>> cmds;
  using namespace std::placeholders;
  cmds["AREA"] = std::bind(maxArea, std::ref(poly));
  cmds["VERTEXES"] = std::bind(maxVertexes, std::ref(poly));
  try
  {
  }
  catch (const std::invalid_argument&) {
    if (cmds.find(subcommand) != cmds.end())
    {
      result = cmds[subcommand]();
    }
    else
    {
      throw std::invalid_argument("<INVALID SUBARGUMENT>");
    }
  }
  out << result << '\n';
}

void zolotukhin::doMin(std::vector<Polygon>& poly, std::istream& in, std::ostream& out)
{
  double result = 0.0;
  std::string subcommand;
  in >> subcommand;
  std::map<std::string, std::function<double()>> cmds;
  using namespace std::placeholders;
  cmds["AREA"] = std::bind(minArea, std::ref(poly));
  cmds["VERTEXES"] = std::bind(minVertexes, std::ref(poly));
  try
  {
  }
  catch (const std::invalid_argument&)
  {
    if (cmds.find(subcommand) != cmds.end())
      {
        result = cmds[subcommand]();
      }
      else
      {
        throw std::invalid_argument("<INVALID SUBARGUMENT>");
      }
  }
  out << result << '\n';
}

bool areaComp(const zolotukhin::Polygon p, double ar)
{
  return zolotukhin::getArea(p) < ar;
}

void zolotukhin::lessarea(std::vector<Polygon>& poly, std::istream& in, std::ostream& out)
{
  zolotukhin::Polygon t;
  in >> t;
  if (!in)
    {
      throw std::exception();
    }
  double area = zolotukhin::getArea(t);
  out << std::count_if(poly.cbegin(), poly.cend(), std::bind(areaComp, std::placeholders::_1, area));
}

int countEven(std::vector<zolotukhin::Polygon>& polygons)
{
  return std::count_if(polygons.cbegin(), polygons.cend(), isEven);
}

int countOdd(std::vector<zolotukhin::Polygon>& polygons)
{
  return std::count_if(polygons.cbegin(), polygons.cend(), isOdd);
}

int countVerticles(std::vector<zolotukhin::Polygon>& polygons, size_t v)
{
  return std::count_if(polygons.cbegin(), polygons.cend(), std::bind(rightVertex, std::placeholders::_1, v));
}

void zolotukhin::doCount(std::vector<Polygon>& poly, std::istream& in, std::ostream& out)
{
  double result = 0.0;
  std::string subcommand;
  in >> subcommand;
  std::map<std::string, std::function<double()>> cmds;
  using namespace std::placeholders;
  cmds["EVEN"] = std::bind(countEven, std::ref(poly));
  cmds["ODD"] = std::bind(countOdd, std::ref(poly));
  size_t vertexNum = 0;
  try
  {
    vertexNum = std::stoull(subcommand);
    if (vertexNum < 3)
    {
      throw std::logic_error("<INCORRECT VERTEX NUMBER>");
    }
    result = countVerticles(poly, vertexNum);
  }
  catch (const std::invalid_argument&)
  {
    if (cmds.find(subcommand) != cmds.end())
    {
      result = cmds[subcommand]();
    }
    else
    {
      throw std::invalid_argument("<INVALID SUBARGUMENT>");
    }
  }
  out << result << '\n';
}
