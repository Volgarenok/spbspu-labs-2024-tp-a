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
