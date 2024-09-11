#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>

void isEmpty(const std::vector< altun::Polygon >& a)
{
  if (a.empty())
  {
    throw std::logic_error("<EMPTY VECTOR>");
  }
}

void altun::count(std::istream& in, std::ostream& out,
    const std::vector< Polygon >& polygons,
    const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  using namespace std::placeholders;
  std::string strArgs = "";
  in >> strArgs;

  std::function< bool(const Polygon&) > pred;
  try
  {
    size_t ver = std::stoull(strArgs);
    if (ver < 3)
    {
      throw std::logic_error("<INVALID COMMANDS>");
    }
    pred = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), ver);
  }
  catch (...)
  {
    pred = args.at(strArgs);
  }

  size_t count = std::count_if(polygons.cbegin(), polygons.cend(), pred);
  out << count << "\n";
}

void altun::getArea(std::istream& in, std::ostream& out,
    const std::vector< Polygon >& polygons,
    const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  std::function< bool(const Polygon&) > pred;
  std::string strArgs = "";
  in >> strArgs;
  size_t devide = 1;

  if (strArgs == "MEAN")
  {
    isEmpty(polygons);
    devide = polygons.size();
  }

  try
  {
    using namespace std::placeholders;
    size_t ver = std::stoull(strArgs);
    if (ver < 3)
    {
      throw std::logic_error("<INVALID COMMANDS>");
    }
    pred = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), ver);
  }
  catch (...)
  {
    pred = args.at(strArgs);
  }

  std::vector< Polygon > polyAreas;
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polyAreas), pred);
  std::vector< double > areas(polyAreas.size());
  std::transform(polyAreas.cbegin(), polyAreas.cend(), std::back_inserter(areas), getPolyArea);
  out << std::setprecision(1);
  out << std::fixed;

  double a = std::accumulate(areas.begin(), areas.end(), 0.0) / devide;
  out << a << "\n";
}

void altun::findMax(std::istream& in, std::ostream& out,
    const std::vector< Polygon >& polygons)
{
  isEmpty(polygons);
  std::string strArgs = "";
  in >> strArgs;

  if (strArgs == "AREA")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), getPolyArea);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::max_element(areas.begin(), areas.end()) << "\n";
  }

  if (strArgs == "VERTEXES")
  {
    std::vector< size_t > areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), getSize);
    out << *std::max_element(areas.begin(), areas.end()) << "\n";
  }
}

void altun::findMin(std::istream& in, std::ostream& out,
    const std::vector< Polygon >& polygons)
{
  isEmpty(polygons);
  std::string strArgs = "";
  in >> strArgs;

  if (strArgs == "AREA")
  {
    std::vector< double > tmp(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(tmp), getPolyArea);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::min_element(tmp.begin(), tmp.end()) << "\n";
  }

  if (strArgs == "VERTEXES")
  {
    std::vector< size_t > tmp(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(tmp), getSize);
    out << *std::min_element(tmp.begin(), tmp.end()) << "\n";
  }
}

struct SeqCounter
{
  public:
    SeqCounter(const std::vector< altun::Point >& src);
    size_t operator()(const altun::Polygon& plg);
    size_t operator()() const;

  private:
    size_t count_;
    size_t max_seq_count_;
    const std::vector< altun::Point > src_;
  };

SeqCounter::SeqCounter(const std::vector< altun::Point >& src):
  count_(0),
  max_seq_count_(0),
  src_(src)
{}

size_t SeqCounter::operator()(const altun::Polygon& plg)
{
  if (plg.points == src_)
  {
    count_++;
    if (count_ > max_seq_count_)
    {
      max_seq_count_ = count_;
    }
  }
  else
  {
    count_ = 0;
  }

  return max_seq_count_;
}

size_t SeqCounter::operator()() const
{
  return max_seq_count_;
}

void altun::maxSeq(std::istream& in, std::ostream& out,
    const std::vector< Polygon >& polygons)
{
  size_t numOfVertexes = 0;
  using in_it = std::istream_iterator< Point >;
  in >> numOfVertexes;

  if (numOfVertexes < 3)
  {
    throw std::logic_error("<NOT ENOUGH VERTEXES>");
  }
  std::vector< Point > srcPoints;
  std::copy_n(in_it{in}, numOfVertexes, std::back_inserter(srcPoints));
  std::vector< size_t > sequences(srcPoints.size());
  if (srcPoints.empty() || in.peek() != '\n')
  {
    throw std::logic_error("<INVALID NUMBER OF VERTEXES>");
  }

  SeqCounter counter_functor(srcPoints);
  out << std::for_each(std::begin(polygons), std::end(polygons), std::ref(counter_functor))() << "\n";
}

void altun::echo(std::istream& in, std::ostream& out,
      std::vector< Polygon >& polygons)
{
  Polygon arg;
  in >> arg;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENT>");
  }
  std::string restOfLine;
  std::getline(in, restOfLine);
  size_t count = std::count(polygons.cbegin(), polygons.cend(), arg);
  if (count == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  out << count << "\n";

  std::vector< Polygon > temp;
  for (const auto& poly : polygons)
  {
    temp.push_back(poly);
    if (poly == arg)
    {
      temp.push_back(arg);
    }
  }
  polygons = std::move(temp);
}

altun::Point pointsDifference(const altun::Point& first, const altun::Point& second)
{
  return altun::Point{second.x - first.x, second.y - first.y};
}

bool isSame(altun::Polygon first, altun::Polygon second)
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }
  std::vector< altun::Point > firstDiffs(first.points.size() - 1);
  std::vector< altun::Point > secondDiffs(first.points.size() - 1);
  using namespace std::placeholders;
  std::transform(first.points.cbegin() + 1, first.points.cend(), firstDiffs.begin(), std::bind(pointsDifference, _1, first.points[0]));
  std::transform(second.points.cbegin() + 1, second.points.cend(), secondDiffs.begin(), std::bind(pointsDifference, _1, second.points[0]));
  return (firstDiffs == secondDiffs);
}

void altun::same(std::istream& in, std::ostream& out,
    const std::vector< Polygon > polygons)
{
  altun::Polygon context;
  in >> context;
  if (!in || in.peek() != '\n')
  {
    throw std::exception();
  }
  using namespace std::placeholders;
  out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(isSame, _1, context)) << "\n";
}
