#include "commands.hpp"

namespace sakovskaia
{
  double calculateArea(const std::vector< Point > & points, int n, int i)
  {
    if (i >= n)
    {
        return 0.0;
    }
    int j = (i + 1) % n;
    double current_area = points[i].x * points[j].y - points[j].x * points[i].y;
    return current_area + calculateArea(points, n, i + 1);
  }

  double countArea(const Polygon & polygon)
  {
    const std::vector< Point > & points = polygon.points;
    int n = points.size();
    double area = calculateArea(points, n, 0);
    return std::abs(area) / 2.0;
  }

  double count(const std::vector< Polygon > & polygons, bool (* filter)(const Polygon &))
  {
    double sum = 0.0;
    for (const Polygon & polygon : polygons)
    {
      if (filter(polygon))
      {
        sum += countArea(polygon);
      }
    }
    return sum;
  }

  bool isEven(const Polygon & p)
  {
    return get_size(p) % 2 == 0;
  }

  bool isOdd(const Polygon & p)
  {
    return get_size(p) % 2 != 0;
  }

  bool alwaysTrue(const Polygon &)
  {
    return true;
  }

  double countWithVertexCheck(const std::vector< Polygon > & polygons, int vertex_count)
  {
    double sum = 0.0;
    for (const Polygon& polygon : polygons)
    {
      if (hasVertexCount(polygon, vertex_count))
      {
        sum += getArea(polygon);
      }
    }
    return sum;
  }

  double getArea(const std::string & parameter, const std::vector< Polygon > & polygons)
  {
    if (parameter == "EVEN")
    {
      double area_sum = count(polygons, isEven);
      std::cout << std::fixed << std::setprecision(1) << area_sum << "\n";
    }
    else if (parameter == "ODD")
    {
      double area_sum = count(polygons, isOdd);
      std::cout << std::fixed << std::setprecision(1) << area_sum << "\n";
    }
    else if (parameter == "MEAN")
    {
      if (polygons.empty())
      {
        std::cerr << "No polygons available.\n";
        return 0.0;
      }
      double total_area = count(polygons, alwaysTrue);
      std::cout << std::fixed << std::setprecision(1) << total_area / polygons.size() << "\n";
    }
    else
    {
      try
      {
        int vertex_count = std::stoi(parameter);
        double area_sum = countWithVertexCheck(polygons, vertex_count);
        std::cout << std::fixed << std::setprecision(1) << area_sum << "\n";
      }
      catch (const std::invalid_argument &)
      {
        std::cerr << "Invalid argument for AREA command\n";
      }
    }
  }

  bool compareArea(const Polygon & lhs, const Polygon & rhs)
  {
    return countArea(lhs) < countArea(rhs);
  }

  bool compareVertices(const Polygon & lhs, const Polygon & rhs)
  {
    return get_size(lhs) < get_size(rhs);
  }

  void getMaxMin(const std::string & type, const std::vector< Polygon > & polygons)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons available.\n";
      return;
    }

    if (type == "AREA")
    {
      const Polygon & result = * std::max_element(polygons.begin(), polygons.end(), compareArea);
      std::cout << std::fixed << std::setprecision(1) << getArea(result) << "\n";
    }
    else if (type == "VERTEXES")
    {
      const Polygon & result = * std::max_element(polygons.begin(), polygons.end(), compareVertices);
      std::cout << get_size(result) << "\n";
    }
  }

  bool isNotEqualToPattern(const Polygon & polygon, const Polygon & pattern)
  {
    return polygon != pattern;
  }

  size_t findMaxSeq(const Polygon & pattern, std::vector< Polygon >::const_iterator iter, std::vector< Polygon >::const_iterator end, size_t current_max)
  {
    auto start = std::find(iter, end, pattern);
    if (start == end)
    {
      return current_max;
    }
    auto it = std::find_if(iter, end, std::bind(isNotEqualToPattern, std::placeholders::_1, pattern));
    return std::distance(iter, it);
  }

  void getMaxSeq(const Polygon & pattern, const std::vector< Polygon > & polygons)
  {
    size_t max_seq = findMaxSeq(pattern, polygons.begin(), polygons.end());
    std::cout << max_seq << "\n";
  }

  bool areEqualPolygons(const Polygon & lhs, const Polygon & rhs, const Polygon & pattern)
  {
    return lhs == rhs && lhs == pattern;
  }

  void getRmecho(const Polygon & pattern, std::vector< Polygon > & polygons)
  {
    auto it = std::unique(polygons.begin(), polygons.end(), std::bind(areEqualPolygons, std::placeholders::_1, std::placeholders::_2, pattern));
    size_t removed_count = polygons.end() - it;
    polygons.erase(it, polygons.end());
    std::cout << removed_count << "\n";
  }

  double squaredDist(const Point & a, const Point & b)
  {
    return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
  }

  bool isRectangle(const Polygon & polygon)
  {
    if (polygon.points.size() != 4)
    {
      return false;
    }
    const auto & p1 = polygon.points[0];
    const auto & p2 = polygon.points[1];
    const auto & p3 = polygon.points[2];
    const auto & p4 = polygon.points[3];
    return squaredDist(p1, p2) == squaredDist(p3, p4) &&
           squaredDist(p2, p3) == squaredDist(p1, p4) &&
           squaredDist(p1, p3) == squaredDist(p2, p4);
  }

  void getRects(const std::vector< Polygon > & polygons)
  {
    size_t rectangle_count = std::count_if(polygons.begin(), polygons.end(), isRectangle);
    std::cout << rectangle_count << "\n";
  }

  void getCommand(const std::string & command, std::vector< Polygon > & polygons)
  {
    std::istringstream stream(command);
    std::string cmd;
    stream >> cmd;
    if (cmd == "AREA")
    {
      std::string param;
      stream >> param;
      getArea(param, polygons);
    }
    else if (cmd == "MAX" || cmd == "MIN")
    {
      std::string type;
      stream >> type;
      getMaxMin(type, polygons);
    }
    else if (cmd == "MAXSEQ")
    {
      Polygon pattern;
      stream >> pattern;
      getMaxSeq(pattern, polygons);
    }
    else if (cmd == "RMECHO")
    {
      Polygon pattern;
      stream >> pattern;
      getRmecho(pattern, polygons);
    }
    else if (cmd == "RECTS")
    {
      getRects(polygons);
    }
    else
    {
      std::cerr << "Unknown command\n";
    }
  }
}

