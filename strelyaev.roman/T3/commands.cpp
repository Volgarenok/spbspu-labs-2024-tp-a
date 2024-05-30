#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>

void checkEmpty(const std::vector< strelyaev::Polygon >& v)
{
  if (v.empty())
  {
    throw std::logic_error("EMPTY VECTOR");
  }
}

void strelyaev::count(std::ostream& out,
    std::istream& in,
    const std::vector< Polygon >& polygons_vector,
    const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  using namespace std::placeholders;
  std::string str_args = "";
  in >> str_args;
  std::function< bool(const Polygon&) > pred;
  try
  {
    size_t ver = std::stoull(str_args);
    if (ver < 3)
    {
      throw std::logic_error("INVALID COMMANDS");
    }
    pred = std::bind(std::equal_to< size_t >{}, std::bind(get_size, _1), ver);
  }
  catch (...)
  {
    pred = args.at(str_args);
  }
  size_t count = std::count_if(polygons_vector.cbegin(), polygons_vector.cend(), pred);
  out << count;
}

void strelyaev::getArea(std::ostream& out, std::istream& in,
    const std::vector< Polygon >& polygons_vector,
    const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  std::function< bool(const Polygon&) > pred;
  std::string str_args = "";
  in >> str_args;
  size_t devide = 1;
  if (str_args == "MEAN")
  {
    checkEmpty(polygons_vector);
    devide = polygons_vector.size();
  }
  try
  {
    using namespace std::placeholders;
    size_t ver = std::stoull(str_args);
    if (ver < 3)
    {
      throw std::logic_error("INVALID COMMANDS");
    }
    pred = std::bind(std::equal_to< size_t >{}, std::bind(get_size, _1), ver);
  }
  catch (...)
  {
    pred = args.at(str_args);
  }
  std::vector< Polygon > area_polygons;
  std::copy_if(polygons_vector.cbegin(), polygons_vector.cend(), std::back_inserter(area_polygons), pred);
  std::vector< double > areas(area_polygons.size());
  std::transform(area_polygons.cbegin(), area_polygons.cend(), std::back_inserter(areas), get_area);
  out << std::setprecision(1);
  out << std::fixed;
  double a = std::accumulate(areas.begin(), areas.end(), 0.0) / devide;
  out << a;
}

void strelyaev::findMax(std::ostream& out, std::istream& in, const std::vector< Polygon >& polygons_vector)
{
  checkEmpty(polygons_vector);
  std::string str_args = "";
  in >> str_args;
  if (str_args == "AREA")
  {
    std::vector< double > areas(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), get_area);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::max_element(areas.begin(), areas.end());
  }
  if (str_args == "VERTEXES")
  {
    std::vector< size_t > areas(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), get_size);
    out << *std::max_element(areas.begin(), areas.end());
  }
}

void strelyaev::findMin(std::ostream& out, std::istream& in, const std::vector< Polygon >& polygons_vector)
{
  checkEmpty(polygons_vector);
  std::string str_args = "";
  in >> str_args;
    if (str_args == "AREA")
  {
    std::vector< double > tmp(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(tmp), get_area);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::min_element(tmp.begin(), tmp.end());
  }
  if (str_args == "VERTEXES")
  {
    std::vector< size_t > tmp(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(tmp), get_size);
    out << *std::min_element(tmp.begin(), tmp.end());
  }
}

bool strelyaev::isPermutationPolygons(const Polygon& lhs, const Polygon& rhs)
{
  using namespace std::placeholders;
  auto compare_x = std::bind(std::equal_to< int >{}, std::bind(get_x, _1), std::bind(get_x, _2));
  auto compare_y = std::bind(std::equal_to< int >{}, std::bind(get_y, _1), std::bind(get_y, _2));
  auto compare_points = std::bind(std::logical_and<>{}, std::bind(compare_x, _1, _2), std::bind(compare_y, _1, _2));
  return std::is_permutation(rhs.points.cbegin(), rhs.points.cend(), lhs.points.cbegin(), lhs.points.cend(), compare_points);
}

void strelyaev::getPerms(std::ostream& out, std::istream& in, const std::vector< Polygon >& polys)
{
  checkEmpty(polys);
  Polygon poly;
  in >> poly;
  std::vector< Polygon > correct;
  using namespace std::placeholders;
  std::function< bool(const Polygon&) > pred = std::bind(std::equal_to< size_t >{}, std::bind(get_size, _1), poly.points.size());
  std::copy_if(polys.cbegin(), polys.cend(), std::back_inserter(correct), pred);
  if (correct.empty())
  {
    throw std::out_of_range("Something is wrong with a command");
  }
  pred = std::bind(isPermutationPolygons, poly, _1);
  out << std::count_if(correct.cbegin(), correct.cend(), pred);
}

struct SeqCounter
{
  public:
    SeqCounter(const std::vector< strelyaev::Point >& src);
    size_t operator()(const strelyaev::Polygon& plg);
    size_t operator()() const;

  private:
    size_t count_;
    size_t max_seq_count_;
    const std::vector< strelyaev::Point > src_;
  };

SeqCounter::SeqCounter(const std::vector< strelyaev::Point >& src):
  count_(0),
  max_seq_count_(0),
  src_(src)
{}

size_t SeqCounter::operator()(const strelyaev::Polygon& plg)
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


void strelyaev::getMaxSeq(std::ostream& out, std::istream& in,
    const std::vector< Polygon >& polygons_vector)
{
  size_t numOfVertexes = 0;
  using in_it = std::istream_iterator< Point >;
  in >> numOfVertexes;

  if (numOfVertexes < 3)
  {
    throw std::logic_error("TOO LOW VERTEXES");
  }
  std::vector< Point > srcPoints;
  std::copy_n(in_it{in}, numOfVertexes, std::back_inserter(srcPoints));
  std::vector< size_t > sequences(srcPoints.size());
  if (srcPoints.empty() || in.peek() != '\n')
  {
    throw std::logic_error("WRONG NUM OF VERTEXES");
  }

  SeqCounter counter_functor(srcPoints);
  out << std::for_each(std::begin(polygons_vector), std::end(polygons_vector), std::ref(counter_functor))();
}
