#include "DataStruct.hpp"
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>

int main()
{
    using namespace kumekova;
    using InputIter = std::istream_iterator<DataStruct>;
    using OutputIter = std::ostream_iterator<DataStruct>;

    constexpr auto MaxStreamSize = std::numeric_limits<std::streamsize>::max();

    std::vector<DataStruct> data;

    while (!std::cin.eof()) {
        std::copy(InputIter(std::cin), InputIter(), std::back_inserter(data));
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(MaxStreamSize, '\n');
        }
    }

    std::sort(data.begin(), data.end());

    std::copy(data.begin(), data.end(), OutputIter(std::cout, "\n"));

    return 0;
}
