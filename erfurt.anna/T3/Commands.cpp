#include "Commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <string>
#include <iomanip>
#include <StreamGuard.hpp>
#include "Utilites.hpp"

namespace erfurt
{
	using namespace std::placeholders;

	void makeArea(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
	{
		StreamGuard guard(out);
		out << std::setprecision(1) << std::fixed;
		std::string temp;
		std::cin >> temp;
		double acc;
		double sum = 0.0;
		if (temp == "EVEN" || temp == "ODD")
		{
			acc = std::accumulate(polygons.begin(), polygons.end(), sum, AccAreaEvenOdd{temp});
		}
		else if (temp == "MEAN")
		{
			acc = std::accumulate(polygons.begin(), polygons.end(), sum, AccAreaMean{polygons.size()});
		}
		else
		{
			try
			{
				int n = std::stoi(temp);
				acc = std::accumulate(polygons.begin(), polygons.end(), sum, AccAreaVertexes{n});
			}
			catch (const std::invalid_argument&)
			{
				throw std::invalid_argument("INVALID ARGUMENT");
			}
		}
		out << acc;
	}

	void makeMax(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
	{
		StreamGuard guard(out);
		out << std::setprecision(1) << std::fixed;
		std::string temp;
		std::cin >> temp;
		if (temp == "AREA")
		{
			auto acc = (std::max_element(polygons.begin(), polygons.end(), [](auto lhs, auto rhs) {return (getArea(lhs) < (getArea(rhs))); }));
			out << getArea(*acc);
		}
		else if (temp == "VERTEXES")
		{
			auto acc = (std::max_element(polygons.begin(), polygons.end(), [](auto lhs, auto rhs) {return (lhs.points.size() < rhs.points.size()); }));
			out << acc->points.size();
		}
		else
		{
			throw std::invalid_argument("INVALID ARGUMENT");
		}
	}

	void makeMin(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
	{
		StreamGuard guard(out);
		out << std::setprecision(1) << std::fixed;
		std::string temp;
		std::cin >> temp;
		if (temp == "AREA")
		{
			auto acc = (std::min_element(polygons.begin(), polygons.end(), [](auto lhs, auto rhs) {return (getArea(lhs) < (getArea(rhs))); }));
			out << getArea(*acc);
		}
		else if (temp == "VERTEXES")
		{
			auto acc = (std::min_element(polygons.begin(), polygons.end(), [](auto lhs, auto rhs) {return (lhs.points.size() < rhs.points.size()); }));
			out << acc->points.size();
		}
		else
		{
			throw std::invalid_argument("INVALID ARGUMENT");
		}
	}

	void makeCount(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
	{
		std::string temp;
		std::cin >> temp;
		size_t result;
		if (temp == "EVEN" || temp == "ODD")
		{
			result = std::count_if(polygons.begin(), polygons.end(), [temp](auto poly)
				{return ((temp == "ODD" && poly.points.size() % 2 == 1) || (temp == "EVEN" && poly.points.size() % 2 == 0)); });
		}
		else
		{
			try
			{
				size_t n = std::stoi(temp);
				result = std::count_if(polygons.begin(), polygons.end(), [n](auto poly)
					{return (n == poly.points.size()); });
			}
			catch (const std::invalid_argument&)
			{
				throw std::invalid_argument("INVALID ARGUMENT");
			}
		}
		out << result;
	}

	void makePerms(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
	{
		Polygon poly;
		in >> poly;
		if (!in || poly.points.empty())
		{
			throw std::invalid_argument("INVALID ARGUMENT");
		}
		out << count_if(polygons.cbegin(), polygons.cend(), std::bind(isPerm, _1, poly));
	}

	void makeRmecho(std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
	{
		Polygon poly;
		in >> poly;
		if (!in || poly.points.empty())
		{
			throw std::invalid_argument("INVALID ARGUMENT");
		}
		auto last = std::unique(polygons.begin(), polygons.end(), std::bind(IdenticalPoly{ poly }, _1, _2));
		size_t erased = std::distance(last, polygons.end());
		polygons.erase(last, polygons.end());
		out << erased;
	}
}