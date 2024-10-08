#include "commands.hpp"
#include <functional>
#include <map>
#include <algorithm>
#include <numeric>

struct HasNumOfVertexes
{
  size_t vertexNum;
  explicit HasNumOfVertexes(size_t num);
  bool operator()(const timchishina::Polygon& poly) const;
};

std::pair< timchishina::Point, timchishina::Point > makePair(const timchishina::Point& p1, const timchishina::Point& p2);
double shoelaceFormula(double acc, const std::pair< timchishina::Point, timchishina::Point >& points);
double sumArea(double acc, const timchishina::Polygon& poly); 
double calcArea(const timchishina::Polygon& poly);
bool isEven(const timchishina::Polygon& poly);
bool isOdd(const timchishina::Polygon& poly);
double calcEvenArea(const std::vector< timchishina::Polygon >& poly);
double calcOddArea(const std::vector< timchishina::Polygon >& poly);
double calcMeanArea(const std::vector< timchishina::Polygon >& poly);
double calcNumVertexArea(const std::vector< timchishina::Polygon >& poly, size_t vertexNum);
bool compareVertexes(const timchishina::Polygon& p1, const timchishina::Polygon& p2);
double getMaxArea(const std::vector< timchishina::Polygon >& poly);
size_t getMaxVertexes(const std::vector< timchishina::Polygon >& poly);
double getMinArea(const std::vector< timchishina::Polygon >& poly);
size_t getMinVertexes(const std::vector< timchishina::Polygon >& poly);
size_t countEven(const std::vector< timchishina::Polygon >& poly);
size_t countOdd(const std::vector< timchishina::Polygon >& poly);
size_t countNum(const std::vector< timchishina::Polygon >& poly, size_t vertexNum);

std::pair< timchishina::Point, timchishina::Point > makePair(const timchishina::Point& p1, const timchishina::Point& p2)
{
  return std::make_pair(p1, p2);
}

double shoelaceFormula(double acc, const std::pair< timchishina::Point, timchishina::Point >& points)
{
  double area = points.first.x * points.second.y - points.second.x * points.first.y;
  return acc + area;
}

double sumArea(double acc, const timchishina::Polygon& poly)
{
  return acc + calcArea(poly);
}

double calcArea(const timchishina::Polygon& poly)
{
  std::vector< std::pair< timchishina::Point, timchishina::Point > > pointPairs;
  std::transform(poly.points.begin(), poly.points.end() - 1, poly.points.begin() + 1,
    std::back_inserter(pointPairs), makePair);
  pointPairs.emplace_back(poly.points.back(), poly.points.front());
  double areaSum = std::accumulate(pointPairs.begin(), pointPairs.end(), 0.0, shoelaceFormula);
  return 0.5 * std::abs(areaSum);
}

void timchishina::doArea(std::vector< Polygon >& poly, std::istream& in, std::ostream& out)
{
  double result = 0.0;
  std::string subcommand;
  in >> subcommand;

  std::map< std::string, std::function< double() > > cmds;
  using namespace std::placeholders;
  cmds["EVEN"] = std::bind(calcEvenArea, poly);
  cmds["ODD"] = std::bind(calcOddArea, poly);
  cmds["MEAN"] = std::bind(calcMeanArea, poly);

  size_t vertexNum = 0;
  try
  {
    vertexNum = std::stoull(subcommand);
    if (vertexNum < 3)
    {
      throw std::logic_error("<INCORRECT VERTEX NUMBER>");
    }
    result = calcNumVertexArea(poly, vertexNum);
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

bool HasNumOfVertexes::operator()(const timchishina::Polygon& poly) const
{
  return poly.points.size() == vertexNum;
}

HasNumOfVertexes::HasNumOfVertexes(size_t num):
  vertexNum(num)
{}

bool isEven(const timchishina::Polygon& poly)
{
  return (poly.points.size() % 2 == 0);
}

bool isOdd(const timchishina::Polygon& poly)
{
  return (poly.points.size() % 2 != 0);
}

double calcEvenArea(const std::vector< timchishina::Polygon >& poly)
{
  std::vector< timchishina::Polygon > evenPolygons;
  std::copy_if(poly.begin(), poly.end(), std::back_inserter(evenPolygons), isEven);
  return std::accumulate(evenPolygons.begin(), evenPolygons.end(), 0.0, sumArea);
}

double calcOddArea(const std::vector< timchishina::Polygon >& poly)
{
  std::vector< timchishina::Polygon > oddPolygons;
  std::copy_if(poly.begin(), poly.end(), std::back_inserter(oddPolygons), isOdd);
  return std::accumulate(oddPolygons.begin(), oddPolygons.end(), 0.0, sumArea);
}

double calcMeanArea(const std::vector< timchishina::Polygon >& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<EMPTY POLYGONS>");
  }
  return std::accumulate(poly.begin(), poly.end(), 0.0, sumArea) / poly.size();
}

double calcNumVertexArea(const std::vector< timchishina::Polygon >& poly, size_t vertexNum)
{
  std::vector< timchishina::Polygon > filteredPolygons;
  std::copy_if(poly.begin(), poly.end(),
    std::back_inserter(filteredPolygons), HasNumOfVertexes(vertexNum));
  return std::accumulate(filteredPolygons.begin(), filteredPolygons.end(), 0.0, sumArea);
}

bool compareVertexes(const timchishina::Polygon& p1, const timchishina::Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}

void timchishina::doMax(std::vector< Polygon >& poly, std::istream& in, std::ostream& out)
{
  std::string subcommand;
  in >> subcommand;

  using namespace std::placeholders;
  std::map< std::string, std::function< double() > > cmdsArea;
  cmdsArea["AREA"] = std::bind(getMaxArea, poly);

  std::map< std::string, std::function< double() > > cmdsVert;
  cmdsVert["VERTEXES"] = std::bind(getMaxVertexes, poly);

  if (cmdsArea.find(subcommand) != cmdsArea.end())
  {
    out << cmdsArea[subcommand]() << '\n';
  }
  else if (cmdsVert.find(subcommand) != cmdsVert.end())
  {
    out << cmdsVert[subcommand]() << '\n';
  }
  else
  {
    throw std::invalid_argument("<INVALID SUBARGUMENT>");
  }
}

double getMaxArea(const std::vector< timchishina::Polygon >& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<EMPTY POLYGONS>");
  }
  using namespace std::placeholders;
  return calcArea(*std::max_element(poly.begin(), poly.end(),
    std::bind(std::less< double >(), std::bind(&calcArea, _1), std::bind(&calcArea, _2))));
}

size_t getMaxVertexes(const std::vector< timchishina::Polygon >& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<EMPTY POLYGONS>");
  }
  return std::max_element(poly.begin(), poly.end(), compareVertexes)->points.size();
}

void timchishina::doMin(std::vector< Polygon >& poly, std::istream& in, std::ostream& out)
{
  std::string subcommand;
  in >> subcommand;

  using namespace std::placeholders;
  std::map< std::string, std::function< double() > > cmdsArea;
  cmdsArea["AREA"] = std::bind(getMinArea, poly);

  std::map< std::string, std::function< double() > > cmdsVert;
  cmdsVert["VERTEXES"] = std::bind(getMinVertexes, poly);

  if (cmdsArea.find(subcommand) != cmdsArea.end())
  {
    out << cmdsArea[subcommand]() << '\n';
  }
  else if (cmdsVert.find(subcommand) != cmdsVert.end())
  {
    out << cmdsVert[subcommand]() << '\n';
  }
  else
  {
    throw std::invalid_argument("<INVALID SUBARGUMENT>");
  }
}

double getMinArea(const std::vector< timchishina::Polygon >& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<EMPTY POLYGONS>");
  }
  using namespace std::placeholders;
  return calcArea(*std::max_element(poly.begin(), poly.end(),
    std::bind(std::less< double >(), std::bind(&calcArea, _1), std::bind(&calcArea, _2))));
}

size_t getMinVertexes(const std::vector< timchishina::Polygon >& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<EMPTY POLYGONS>");
  }
  return std::min_element(poly.begin(), poly.end(), compareVertexes)->points.size();
}

void timchishina::doCount(std::vector< Polygon >& poly, std::istream& in, std::ostream& out)
{
  size_t result = 0;
  std::string subcommand;
  in >> subcommand;

  std::map< std::string, std::function< size_t() > > cmds;
  using namespace std::placeholders;
  cmds["EVEN"] = std::bind(countEven, poly);
  cmds["ODD"] = std::bind(countOdd, poly);

  size_t vertexNum = 0;
  try
  {
    vertexNum = std::stoull(subcommand);
    if (vertexNum < 3)
    {
      throw std::logic_error("<INCORRECT VERTEX NUMBER>");
    }
    result = countNum(poly, vertexNum);
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

size_t countEven(const std::vector< timchishina::Polygon >& poly)
{
  return std::count_if(poly.begin(), poly.end(), isEven);
}

size_t countOdd(const std::vector< timchishina::Polygon >& poly)
{
  return std::count_if(poly.begin(), poly.end(), isOdd);
}

size_t countNum(const std::vector< timchishina::Polygon >& poly, size_t vertexNum)
{
  return std::count_if(poly.begin(), poly.end(), HasNumOfVertexes(vertexNum));
}
