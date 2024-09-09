#include "command.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <map>

namespace sakovskaia
{
  double count(const std::vector< Polygon > & polygons, std::function< bool(const Polygon &) > filter)
  {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0, [& filter](double acc, const Polygon & p)
    {
      return filter(p) ? acc + get_area(p) : acc;
    });
  }

  void get::Area(const std::string & parameter, const std::vector< Polygon > & polygons)
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
      double area_sum = calculate_area_sum(polygons, [](const Polygon &p) {
        return get_size(p) % 2 != 0;
      });
      std::cout << std::fixed << std::setprecision(1) << area_sum << "\n";
    }
    else if (parameter == "MEAN")
    {
      if (polygons.empty())
      {
        std::cerr << "No polygons available.\n";
        return;
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

  void findMaxMin(const std::string & type, const std::vector< Polygon > & polygons, bool is_max)
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
        return get_area(lhs) < get_area(rhs);
      };
      const Polygon & result = * std::max_element(polygons.begin(), polygons.end(), comp);
      std::cout << std::fixed << std::setprecision(1) << get_area(result) << "\n";
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

  void findMaxSeq(const Polygon & pattern, std::vector< Polygon >::const_iterator iter, std::vector< Polygon >::const_iterator end, size_t current_max = 0)
  {
    auto start = std::find(iter, end, pattern);
    if (start == end)
    {
      return current_max;
    }
    auto seq_end = std::find_if(start, end, [& pattern](const Polygon & polygon)
    {
      return polygon != pattern;
    });
    size_t seq_length = std::distance(start, seq_end);
    current_max = std::max(current_max, seq_length);
    return find_max_sequence(pattern, seq_end, end, current_max);
  }

  void getMaxSeq(const Polygon & pattern, const std::vector< Polygon > & polygons)
  {
    size_t max_seq = find_max_sequence(pattern, polygons.begin(), polygons.end());
    std::cout << max_seq << "\n";
  }
}
