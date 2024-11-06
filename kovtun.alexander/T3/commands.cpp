#include "commands.hpp"


void kovtun::area(const std::vector< kovtun::Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::map< std::string, std::pair<
      std::function< bool(const kovtun::Polygon & polygon) >,
      std::function< double(const kovtun::Polygon & polygon, size_t count) > > > args
      {
          {"EVEN", std::make_pair(isEven, getTotalArea)},
          {"ODD", std::make_pair(isOdd, getTotalArea)},
          {"MEAN", std::make_pair(notEmpty, getMeanArea)}
      };

  std::string arg;
  in >> arg;

  std::function< double(const kovtun::Polygon &) > calculator;
  std::vector< kovtun::Polygon > selection;
  if (args.find(arg) == args.end())
  {
    size_t vertexNum = std::stoul(arg);
    if (vertexNum < 3)
    {
      throw std::invalid_argument("not enough vertexes");
    }
    auto predicate = std::bind(equalVertex, vertexNum, std::placeholders::_1);
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(selection), predicate);
    calculator = std::bind(getTotalArea, std::placeholders::_1, selection.size());
  }
  else
  {
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(selection), args.at(arg).first);
    calculator = std::bind(args.at(arg).second, std::placeholders::_1, selection.size());
  }

  if (arg == "MEAN" && polygons.empty())
  {
    throw std::invalid_argument("no polygons");
  }

  std::vector< double > result(selection.size());
  std::transform(selection.cbegin(), selection.cend(), result.begin(), calculator);

  kovtun::IOScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(result.cbegin(), result.cend(), 0.0) << '\n';
}

void kovtun::max(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;

  kovtun::IOScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  if (arg == "AREA")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("no polygons");
    }
    auto maxElem = std::max_element(polygons.begin(), polygons.end(), area_comparator);
    auto result = getArea(*maxElem);

    out << result << "\n";
  }
  else if (arg == "VERTEXES")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("no polygons");
    }
    auto maxVert = std::max_element(polygons.begin(), polygons.end(), vertex_comparator);
    auto result = maxVert->points.size();

    out << result << "\n";
  }
  else
  {
    throw std::invalid_argument("MAX invalid argument");
  }
}

void kovtun::min(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("no polygons");
  }

  std::string arg;
  in >> arg;

  kovtun::IOScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  if (arg == "AREA")
  {
    auto maxElem = std::min_element(polygons.begin(), polygons.end(), area_comparator);
    auto result = getArea(*maxElem);

    out << result << "\n";
  }
  else if (arg == "VERTEXES")
  {
    auto maxVert = std::min_element(polygons.begin(), polygons.end(), vertex_comparator);
    auto result = maxVert->points.size();

    out << result << "\n";
  }
  else
  {
    throw std::invalid_argument("MAX invalid argument");
  }
}

void kovtun::count(const std::vector< kovtun::Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::map< std::string, std::function< bool(const Polygon &) > > args
  {
    {"EVEN", isEven},
    {"ODD", isOdd}
  };

  std::string arg;
  in >> arg;

  size_t sum = 0;
  if (args.find(arg) != args.end())
  {
    sum = std::count_if(polygons.cbegin(), polygons.cend(), args.at(arg));
  }
  else
  {
    size_t num = std::stoul(arg);
    if (num < 3)
    {
      throw std::invalid_argument("not enough vertexes");
    }
    auto predicate = std::bind(equalVertex, num, std::placeholders::_1);
    sum = std::count_if(polygons.cbegin(), polygons.cend(), predicate);
  }

  out << sum << "\n";
}

void kovtun::lessArea(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("invalid polygon");
  }

  auto predicate = std::bind(area_comparator, std::placeholders::_1, std::cref(polygon));
  size_t result = std::count_if(polygons.cbegin(), polygons.cend(), predicate);
  out << result << "\n";
}

void kovtun::same(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("invalid polygon");
  }

  auto predicate = std::bind(same_comparator, std::cref(polygon), std::placeholders::_1);
  size_t result = std::count_if(polygons.cbegin(), polygons.cend(), predicate);
  out << result << "\n";
}

void kovtun::rmecho(std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("invalid polygon");
  }

  auto predicate = std::bind(duplicate_comparator, std::cref(polygon), std::placeholders::_1, std::placeholders::_2);
  auto last = std::unique(polygons.begin(), polygons.end(), predicate);

  size_t result = std::distance(last, polygons.end());
  polygons.erase(last, polygons.end());
  out << result << "\n";
}

bool kovtun::isEven(const kovtun::Polygon & polygon)
{
  return polygon.points.size() % 2 == 0 && notEmpty(polygon);
}

bool kovtun::isOdd(const kovtun::Polygon & polygon)
{
  return polygon.points.size() % 2 != 0 && notEmpty(polygon);
}

bool kovtun::notEmpty(const kovtun::Polygon & polygon)
{
  return !polygon.points.empty();
}

double kovtun::getTotalArea(const kovtun::Polygon & polygon, size_t count)
{
  count = 1;
  return getMeanArea(polygon, count);
}

double kovtun::getMeanArea(const kovtun::Polygon & polygon, size_t count)
{
  if (!notEmpty(polygon))
  {
    throw std::invalid_argument("no polygons");
  }

  return getArea(polygon) / count;
}

bool kovtun::equalVertex(size_t count, const kovtun::Polygon & polygon)
{
  return count == polygon.points.size();
}

bool kovtun::area_comparator(const kovtun::Polygon & first, const kovtun::Polygon & second)
{
  return getArea(first) < getArea(second);
}

bool kovtun::vertex_comparator(const kovtun::Polygon & first, const kovtun::Polygon & second)
{
  return first.points.size() < second.points.size();
}

bool kovtun::same_comparator(const kovtun::Polygon & first, const kovtun::Polygon & second)
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }

  kovtun::Point delta = {
      second.points.front().x - first.points.front().x,
      second.points.front().y - first.points.front().y
  };

  auto predicate = std::bind(superimposed_comparator, second, std::placeholders::_1, delta);
  auto num = std::distance(first.points.cbegin(), first.points.cend());
  auto selection = std::count_if(first.points.cbegin(), first.points.cend(), predicate);

  return selection == num;
}

bool kovtun::superimposed_comparator(const kovtun::Polygon & polygon, const kovtun::Point & point, const kovtun::Point & delta)
{
  kovtun::Point dest = { point.x + delta.x, point.y + delta.y };
  auto predicate = std::bind(areEqual, dest, std::placeholders::_1);
  return std::find_if(polygon.points.cbegin(), polygon.points.cend(), predicate) != polygon.points.cend();
}

bool kovtun::areEqual(const kovtun::Point & first, const kovtun::Point & second)
{
  return first == second;
}

bool kovtun::duplicate_comparator(const kovtun::Polygon & selected, const kovtun::Polygon & first, const kovtun::Polygon & second)
{
  return first == second && selected == first;
}
