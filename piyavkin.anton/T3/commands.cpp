#include "commands.hpp"
#include <numeric>
#include <map>
#include <limits>
#include "streamguard.hpp"

bool isEven(const piyavkin::Polygon& pol)
{
  return (pol.points.size() % 2 == 0);
}

bool isOdd(const piyavkin::Polygon& pol)
{
  return !isEven(pol);
}

double getAreaMean(const std::vector< piyavkin::Polygon >& pols)
{
  double sum = piyavkin::getArea(pols);
  if (pols.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  return sum / pols.size();
}

double getAreaCond(const std::vector< piyavkin::Polygon >& pols, bool (*op)(const piyavkin::Polygon& pol))
{
  return piyavkin::getCorArea(pols, op);
}

size_t getNVertex(const std::string& name)
{
  size_t n = 0;
  try
  {
    n = std::stoull(name);
  }
  catch (const std::exception&)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  const size_t minN = 3;
  if (n < minN)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  return n;
}

bool isNVertex(const piyavkin::Polygon& pol, size_t num)
{
  return pol.points.size() == num;
}

double getAreaNVertex(const std::vector< piyavkin::Polygon >& pols, size_t name)
{
  auto fun = std::bind(isNVertex, std::placeholders::_1, name);
  return piyavkin::getCorArea(pols, fun);
}

void piyavkin::cmdArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& pols)
{
  std::string name = "";
  in >> name;
  double sum = 0;
  std::map< std::string, std::function< double(const std::vector< Polygon >&) > > subcmd;
  {
    using namespace std::placeholders;
    subcmd["EVEN"] = std::bind(getAreaCond, _1, isEven);
    subcmd["ODD"] = std::bind(getAreaCond, _1, isOdd);
    subcmd["MEAN"] = getAreaMean;
  }
  try
  {
    sum = subcmd.at(name)(pols);
  }
  catch (const std::out_of_range&)
  {
    size_t n = getNVertex(name);
    sum = getAreaNVertex(pols, n);
  }
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed << sum;
}

size_t piyavkin::detail::getVertex(const Polygon& pol)
{
  return pol.points.size();
}

void getAreaMin(std::ostream& out, const std::vector< piyavkin::Polygon >& pols)
{
  return piyavkin::detail::getAreaMinMax(out, pols, std::less< double >());
}

void getVertexMin(std::ostream& out, const std::vector< piyavkin::Polygon >& pols)
{
  return piyavkin::detail::getVertexMinMax(out, pols, std::less< size_t >());
}

void piyavkin::cmdMin(std::istream& in, std::ostream& out, const std::vector< Polygon >& pols)
{
  if (pols.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::string name = "";
  in >> name;
  std::map< std::string, std::function< void(std::ostream&, const std::vector< Polygon >&) > > subcmd;
  subcmd["AREA"] = getAreaMin;
  subcmd["VERTEXES"] = getVertexMin;
  subcmd.at(name)(out, pols);
}

void getAreaMax(std::ostream& out, const std::vector< piyavkin::Polygon >& pols)
{
  return piyavkin::detail::getAreaMinMax(out, pols, std::greater< double >());
}

void getVertexMax(std::ostream& out, const std::vector< piyavkin::Polygon >& pols)
{
  return piyavkin::detail::getVertexMinMax(out, pols, std::greater< size_t >());
}

void piyavkin::cmdMax(std::istream& in, std::ostream& out, const std::vector< Polygon >& pols)
{
  if (pols.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::string name = "";
  in >> name;
  std::map< std::string, std::function< void(std::ostream&, const std::vector< Polygon >&) > > subcmd;
  subcmd["AREA"] = getAreaMax;
  subcmd["VERTEXES"] = getVertexMax;
  subcmd.at(name)(out, pols);
}

size_t countCond(const std::vector< piyavkin::Polygon >& pols, bool (*op)(const piyavkin::Polygon& pol))
{
  return std::count_if(pols.cbegin(), pols.cend(), op);
}

void piyavkin::cmdCount(std::istream& in, std::ostream& out, const std::vector< Polygon >& pols)
{
  std::string name = "";
  in >> name;
  std::function< bool(const Polygon&) > countPred;
  std::map< std::string, std::function< size_t(const std::vector< Polygon >&) > > subcmd;
  {
    using namespace std::placeholders;
    subcmd["EVEN"] = std::bind(countCond, _1, isEven);
    subcmd["ODD"] = std::bind(countCond, _1, isOdd);
  }
  try
  {
    out << subcmd.at(name)(pols);
  }
  catch (const std::out_of_range&)
  {
    size_t n = getNVertex(name);
    out << count_if(pols.cbegin(), pols.cend(), std::bind(isNVertex, std::placeholders::_1, n));
  }
}

bool less(const piyavkin::Polygon& p1, const piyavkin::Polygon& p2)
{
  return piyavkin::getAreaPol(p1) < piyavkin::getAreaPol(p2);
}

void checkPol(std::istream& in)
{
  char c = 0;
  if (in)
  {
    in >> std::noskipws;
    in >> c;
    in >> std::skipws;
  }
  if (in.fail() || c != '\n')
  {
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void piyavkin::cmdLessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol)
{
  Polygon p;
  in >> p;
  checkPol(in);
  out << std::count_if(pol.begin(), pol.end(), std::bind(less, std::placeholders::_1, p));
}

bool interPred(const piyavkin::Polygon& p1, const piyavkin::Polygon& p2)
{
  auto pairP1 = std::minmax_element(p1.points.cbegin(), p1.points.cend());
  auto pairP2 = std::minmax_element(p2.points.cbegin(), p2.points.cend());
  return !(*pairP1.second < *pairP2.first || *pairP2.second < *pairP1.first);
}

void piyavkin::cmdIntersections(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol)
{
  Polygon p;
  in >> p;
  checkPol(in);
  out << std::count_if(pol.begin(), pol.end(), std::bind(interPred, std::placeholders::_1, p));
}
