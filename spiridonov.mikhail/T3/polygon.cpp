#include "polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>
#include "delimeter.hpp"

std::istream& spiridonov::operator>>(std::istream& in, Point& point)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    using del = spiridonov::DelimeterChar;
    Point temp{ 0, 0 };
    in >> del{ '(' } >> temp.x >> del{ ';' } >> temp.y >> del{ ')' };
    if (in)
    {
        point = temp;
    }
    return in;
}

std::ostream& spiridonov::operator<<(std::ostream& out, const Point& point)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    out << '(' << point.x << ';' << point.y << ')';
    return out;
}

std::istream& spiridonov::operator>>(std::istream& in, Polygon& polygon)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    std::size_t n = 0;
    in >> n;
    if (n < 3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::vector< Point > points;
    std::generate_n(std::back_inserter(points), n,
        [&]() {
        Point point{ 0, 0 };
        if (in >> point)
        {
            return point;
        }
        return Point{};
    });

    if (in)
    {
        polygon.points = points;
    }
    return in;
}

std::ostream& spiridonov::operator<<(std::ostream& out, const Polygon& polygon)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    using output = std::ostream_iterator< Point >;
    out << polygon.points.size() << ' ';
    std::copy(polygon.points.cbegin(), polygon.points.cend(), output{ out, " " });
    return out;
}
