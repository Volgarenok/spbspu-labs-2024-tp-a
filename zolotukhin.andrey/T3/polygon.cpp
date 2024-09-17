#include "polygon.hpp"
#include "delimiter.hpp"

std::istream& zolotukhin::operator>>(std::istream& in, Point& point)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    using del = zolotukhin::delimiter_t;
    Point pos = {};
    in >> del{ '(' } >> pos.x >> del{ ';' } >> pos.y >> del{ ')' };
    if (in)
    {
        point = pos;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& zolotukhin::operator>>(std::istream& in, Polygon& poly)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    size_t verticesNumb = {};
    in >> verticesNumb;

    if (verticesNumb < 3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::vector< Point > p;
    p.reserve(verticesNumb);
    using inputItT = std::istream_iterator< Point >;
    std::copy_n(inputItT{ in }, verticesNumb, std::back_inserter(p));

    if (p.size() == verticesNumb)
    {
        poly.points = std::move(p);;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

double zolotukhin::CalculateArea::operator()(double res, const Point& point3)
{
    res += 0.5 * (std::abs((point1.x - point3.x) * (point2.y - point3.y) - (point2.x - point3.x) * (point1.y - point3.y)));
    point2 = point3;
    return res;
}

double zolotukhin::getArea(const zolotukhin::Polygon p)
{
    std::vector<zolotukhin::Point> points = p.points;
    using namespace std::placeholders;
    auto calcArea = std::bind(zolotukhin::CalculateArea{ points[0], points[1] }, _1, _2);
    return std::accumulate(std::next(points.begin()), points.end(), 0.0, calcArea);
}

bool zolotukhin::CalcRightCorner::operator()(const Point& point3)
{
    Point side1 = { point2.x - point1.x, point2.y - point1.y };
    Point side2 = { point3.x - point1.x, point3.y - point1.y };

    point1 = point2;
    point2 = point3;

    return side1.x * side2.x + side1.y * side2.y == 0;
}

bool zolotukhin::operator==(const Polygon & lhs, const Polygon & rhs)
{
    return lhs.points == rhs.points;
}

bool zolotukhin::operator==(const Point & lhs, const Point & rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool zolotukhin::operator<(const Point& p1, const Point& p2)
{
  return (p1.x < p2.x && p1.y < p2.y);
}

size_t zolotukhin::Polygon::getCorners() const
{
    if (points.size() < 3)
    {
        throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto calcCorner = CalcRightCorner{ points[points.size() - 1], points[points.size() - 2] };
    return std::find_if(points.cbegin(), points.cend(), calcCorner) != points.cend();
}

