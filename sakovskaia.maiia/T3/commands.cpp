#include "commands.hpp"

namespace sakovskaia
{
  double getArea(const Polygon & polygon)
  {
    double area = 0.0;
    const std::vector< Point > & points = polygon.points;
    int n = points.size();
    for (int i = 0; i < n; ++i)
    {
      int j = (i + 1) % n;
      area += points[i].x * points[j].y - points[j].x * points[i].y;
    }
    return std::abs(area) / 2.0;
  }

  double getArea(const std::string & parameter, const std::vector< Polygon > & polygons)
  {
    if (parameter == "EVEN")
    {
      double area_sum = count(polygons, [](const Polygon & p)
      {
        return get_size(p) % 2 == 0;
      });
      std::cout << std::fixed << std::setprecision(1) << area_sum << "\n";
    }
    else if (parameter == "ODD")
    {
      double area_sum = count(polygons, [](const Polygon & p) {
        return get_size(p) % 2 != 0;
      });
      std::cout << std::fixed << std::setprecision(1) << area_sum << "\n";
    }
    else if (parameter == "MEAN")
    {
      if (polygons.empty())
      {
        std::cerr << "No polygons available.\n";
        return 0.0;
      }
      double total_area = count(polygons, [](const Polygon &) { return true; });
      std::cout << std::fixed << std::setprecision(1) << total_area / polygons.size() << "\n";
    }
    else
    {
      try
      {
        int vertex_count = std::stoi(parameter);
        double area_sum = count(polygons, [vertex_count](const Polygon & p)
        {
          return get_size(p) == static_cast< size_t >(vertex_count);
        });
        std::cout << std::fixed << std::setprecision(1) << area_sum << "\n";
      }
      catch (const std::invalid_argument &)
      {
        std::cerr << "Invalid argument for AREA command\n";
      }
    }
  }

  double count(const std::vector< Polygon > & polygons, std::function< bool(const Polygon &) > filter)
  {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0, [& filter](double acc, const Polygon & p)
    {
      return filter(p) ? acc + getArea(p) : acc;
    });
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
      auto comp = [](const Polygon & lhs, const Polygon & rhs)
      {
        return getArea(lhs) < getArea(rhs);
      };
      const Polygon & result = * std::max_element(polygons.begin(), polygons.end(), comp);
      std::cout << std::fixed << std::setprecision(1) << getArea(result) << "\n";
    }
    else if (type == "VERTEXES")
    {
      auto comp = [](const Polygon & lhs, const Polygon & rhs)
      {
        return get_size(lhs) < get_size(rhs);
      };
      const Polygon & result = * std::max_element(polygons.begin(), polygons.end(), comp);
      std::cout << get_size(result) << "\n";
    }
  }

  size_t findMaxSeq(const Polygon & pattern, std::vector< Polygon >::const_iterator iter, std::vector< Polygon >::const_iterator end, size_t current_max)
  {
    auto start = std::find(iter, end, pattern);
    if (start == end)
    {
      return current_max;
    }
    auto it = std::find_if(iter, end, [& pattern](const Polygon & polygon)
    {
      return polygon != pattern;
    });
    return std::distance(iter, it);
  }

  void getMaxSeq(const Polygon & pattern, const std::vector< Polygon > & polygons)
  {
    size_t max_seq = findMaxSeq(pattern, polygons.begin(), polygons.end());
    std::cout << max_seq << "\n";
  }

  void getRmecho(const Polygon & pattern, std::vector< Polygon > & polygons)
  {
    auto it = std::unique(polygons.begin(), polygons.end(), [& pattern](const Polygon & lhs, const Polygon & rhs)
    {
      return lhs == rhs && lhs == pattern;
    });
    size_t removed_count = polygons.end() - it;
    polygons.erase(it, polygons.end());
    std::cout << removed_count << "\n";
  }

  bool isRectangle(const Polygon & polygon)
  {
    if (polygon.points.size() != 4)
    {
      return false;
    }
    auto dist_squared = [](const Point & a, const Point & b)
    {
      return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    };
    const auto & p1 = polygon.points[0];
    const auto & p2 = polygon.points[1];
    const auto & p3 = polygon.points[2];
    const auto & p4 = polygon.points[3];
    return dist_squared(p1, p2) == dist_squared(p3, p4) &&
           dist_squared(p2, p3) == dist_squared(p1, p4) &&
           dist_squared(p1, p3) == dist_squared(p2, p4);
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

