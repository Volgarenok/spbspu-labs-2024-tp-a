#include "Commands.hpp"
#include <iomanip>
#include <algorithm>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>
#include <string>
#include "StreamGuard.hpp"

namespace vorobieva
{
  double doAreaEven(const std::vector<Polygon> & figures);
  double doAreaOdd(const std::vector<Polygon> & figures);
  double doAreaMean(const std::vector<Polygon> & figures);
  double doAreaNum(const std::vector<Polygon> & figures, size_t number);
  double doMaxArea(const std::vector<Polygon> & figures);
  size_t doMaxVertexes(const std::vector<Polygon> & figures);
  double doMinArea(const std::vector<Polygon> & figures);
  size_t doMinVertexes(const std::vector<Polygon> & figures);
  size_t doCountEven(const std::vector<Polygon> & figures);
  size_t doCountOdd(const std::vector<Polygon> & figures);
  size_t doCountNum(const std::vector<Polygon> & figures, size_t number);
}

int multiplyX1Y2(const vorobieva::Point & pointOne, const vorobieva::Point & pointTwo)
{
  int x1 = pointOne.x;
  int y2 = pointTwo.y;
  return x1 * y2;
}

int multiplyX2Y1(const vorobieva::Point & pointOne, const vorobieva::Point & pointTwo)
{
  int x2 = pointTwo.x;
  int y1 = pointOne.y;
  return x2 * y1;
}

bool isEven(const vorobieva::Polygon & polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool isOdd(const vorobieva::Polygon & polygon)
{
  return (!isEven(polygon));
}

bool isNum(const vorobieva::Polygon & polygon, size_t num)
{
  return (polygon.points.size() == num);
}

double areaCount(const vorobieva::Polygon & polygon)
{
  std::vector< vorobieva::Point > points = polygon.points;
  vorobieva::Point onePoint = points.front();
  vorobieva::Point otherPoint = points.back();
  std::vector< int > X_1_Y_2;
  std::vector< int > X_2_Y_1;
  std::transform(std::begin(points), std::end(points) - 1, std::begin(points) + 1, std::back_inserter(X_1_Y_2), multiplyX1Y2);
  std::transform(std::begin(points), std::end(points) - 1, std::begin(points) + 1, std::back_inserter(X_2_Y_1), multiplyX2Y1);
  double area = std::accumulate(std::begin(X_1_Y_2), std::end(X_1_Y_2), 0) - std::accumulate(std::begin(X_2_Y_1), std::end(X_2_Y_1), 0);
  area += otherPoint.x * onePoint.y - otherPoint.y * onePoint.x;
  return (std::abs(area)) / 2;
}


bool areaCompare(const vorobieva::Polygon & first, const vorobieva::Polygon & second)
{
  return areaCount(first) < areaCount(second);
}

bool vertexesCompare(const vorobieva::Polygon & first, const vorobieva::Polygon & second)
{
  return first.points.size() < second.points.size();
}

double vorobieva::doAreaNum(const std::vector< Polygon > & figures, size_t number)
{
  using namespace std::placeholders;
  std::vector< Polygon > container;
  std::vector< double > areas;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(container), std::bind(isNum, _1, number));
  std::transform(std::begin(container), std::end(container), std::back_inserter(areas), areaCount);
  double sum = std::accumulate(std::begin(areas), std::end(areas), 0);
  return sum;
}

double vorobieva::doAreaEven(const std::vector< Polygon > & figures)
{
  std::vector< Polygon > container;
  std::vector< double > areas;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(container), isEven);
  std::transform(std::begin(container), std::end(container), std::back_inserter(areas), areaCount);
  double sum = std::accumulate(std::begin(areas), std::end(areas), 0);
  return sum;
}

double vorobieva::doAreaOdd(const std::vector< Polygon > & figures)
{
  std::vector< Polygon > container;
  std::vector< double > areas;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(container), isOdd);
  std::transform(std::begin(container), std::end(container), std::back_inserter(areas), areaCount);
  double sum = std::accumulate(std::begin(areas), std::end(areas), 0);
  return sum;
}

double vorobieva::doAreaMean(const std::vector< Polygon > & figures)
{
  std::vector< double > areas;
  std::transform(std::begin(figures), std::end(figures), std::back_inserter(areas), areaCount);
  double sum = std::accumulate(std::begin(areas), std::end(areas), 0);
  double sumMean = sum / figures.size();
  return sumMean;
}

double vorobieva::doMaxArea(const std::vector< Polygon > & figures)
{
  auto maxFigure = std::max_element(std::begin(figures), std::end(figures), areaCompare);
  return areaCount(*maxFigure);
}

size_t vorobieva::doMaxVertexes(const std::vector< Polygon > & figures)
{
  auto maxVertexes = std::max_element(std::begin(figures), std::end(figures), vertexesCompare);
  return (*maxVertexes).points.size();
}

double vorobieva::doMinArea(const std::vector< Polygon > & figures)
{
  auto minFigure = std::min_element(std::begin(figures), std::end(figures), areaCompare);
  return areaCount(*minFigure);
}

size_t vorobieva::doMinVertexes(const std::vector< Polygon > & figures)
{
  auto minVertexes = std::min_element(std::begin(figures), std::end(figures), vertexesCompare);
  return (*minVertexes).points.size();
}

size_t vorobieva::doCountEven(const std::vector< Polygon > & figures)
{
  return std::count_if(std::begin(figures), std::end(figures), isEven);
}

size_t vorobieva::doCountOdd(const std::vector< Polygon > & figures)
{
  return std::count_if(std::begin(figures), std::end(figures), isOdd);
}

size_t vorobieva::doCountNum(const std::vector< Polygon > & figures, size_t number)
{
  using namespace std::placeholders;
  return std::count_if(std::begin(figures), std::end(figures), std::bind(isNum, _1, number));
}

void vorobieva::areaCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out)
{
  double result = 0.0;
  std::string cmd;
  in >> cmd;
  std::map< std::string, std::function< double() > > cmds;
  {
    using namespace std::placeholders;
    cmds["EVEN"] = std::bind(doAreaEven, figures);
    cmds["ODD"] = std::bind(doAreaOdd, figures);
    cmds["MEAN"] = std::bind(doAreaMean, figures);
  }
  try
  {
    size_t number = std::stoull(cmd);
    if (number < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    result = doAreaNum(figures, number);
  }
  catch (const std::invalid_argument&)
  {
    result = cmds[cmd]();
  }
  StreamGuard guard(out);
  out << std::fixed << std::setprecision(1);
  out << result << "\n";
}

void vorobieva::maxCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out)
{
  std::string cmd;
  in >> cmd;
  std::map< std::string, std::function< double() > > cmdsArea;
  std::map< std::string, std::function< double() > > cmdsVertexes;
  cmdsArea["AREA"] = std::bind(doMaxArea, figures);
  cmdsVertexes["VERTEXES"] = std::bind(doMaxVertexes, figures);
  if (cmdsArea.find(cmd) != cmdsArea.end())
  {
    out << std::fixed << std::setprecision(1);
    out << cmdsArea[cmd]() << "\n";
  }
  else if (cmdsVertexes.find(cmd) != cmdsVertexes.end())
  {
    out << cmdsVertexes[cmd]() << "\n";
  }
}

void vorobieva::minCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out)
{
  std::string cmd;
  in >> cmd;
  std::map< std::string, std::function< double() > > cmdsArea;
  std::map< std::string, std::function< double() > > cmdsVertexes;
  cmdsArea["AREA"] = std::bind(doMinArea, figures);
  cmdsVertexes["VERTEXES"] = std::bind(doMinVertexes, figures);
  if (cmdsArea.find(cmd) != cmdsArea.end())
  {
    out << std::fixed << std::setprecision(1);
    out << cmdsArea[cmd]() << "\n";
  }
  else if (cmdsVertexes.find(cmd) != cmdsVertexes.end())
  {
    out << cmdsVertexes[cmd]() << "\n";
  }
}

void vorobieva::countCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function < size_t() > > cmds;
  cmds["EVEN"] = std::bind(doCountEven, figures);
  cmds["ODD"] = std::bind(doCountOdd, figures);
  std::string cmd = "";
  in >> cmd;
  try
  {
    out << cmds.at(cmd)() << '\n';
  }
  catch (const std::out_of_range&)
  {
    size_t number = std::stoull(cmd);
    if (number < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    out << doCountNum(figures, number) << '\n';
  }
}

namespace vorobieva
{
  struct MaxSeq
  {
    size_t cur;
    size_t maxseq;
    bool operator()(const Polygon & polygon, const Polygon & data);
  };
}

bool vorobieva::MaxSeq::operator()(const Polygon & figures, const Polygon & data)
{
  if (figures == data)
  {
    cur++;
    maxseq = std::max(maxseq, cur);
  }
  else
  {
    cur = 0;
  }
  return maxseq;
}

void vorobieva::maxSeqCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  vorobieva::Polygon data;
  in >> data;
  if (data.points.size() < 3)
  {
    throw std::logic_error("INVALID COMMAND");
  }
  else
  {
    MaxSeq seq{ 0,0 };
    size_t numberSeq = std::count_if(figures.begin(), figures.end(), std::bind(std::ref(seq), _1, data));
    if (numberSeq < 1)
    {
      throw std::logic_error("INVALID COMMAND");
    }
    else
    {
      out << seq.maxseq << "\n";
    }
  }
}

bool checkPerms(const vorobieva::Polygon & polygon1, const vorobieva::Polygon & polygon2)
{
  if (polygon1.points.size() != polygon2.points.size())
  {
    return false;
  }
  return std::is_permutation(polygon1.points.cbegin(), polygon1.points.cend(), polygon2.points.cbegin());
}

void vorobieva::permsCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  Polygon rePolygon;
  in >> rePolygon;
  if (rePolygon.points.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  if (rePolygon.points.size() < 3)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  out << std::count_if(figures.begin(), figures.end(), std::bind(checkPerms, _1, rePolygon));
}

namespace vorobieva
{
  struct LessArea
  {
    double area;
    bool operator()(const Polygon & polygon) const;
  };
}

bool vorobieva::LessArea::operator()(const Polygon & polygon) const
{
  return areaCount(polygon) < area;
}

void vorobieva::lessAreaCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  Polygon refPolygon;
  in >> refPolygon;
  if (!(in && in.peek() == '\n'))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  auto count = std::count_if(figures.begin(), figures.end(), LessArea{ areaCount(refPolygon) });
  out << count;
}
