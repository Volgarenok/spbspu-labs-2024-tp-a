#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>

#include "DataStruct.hpp"

int main()
{
    using namespace kumekova;
    using OutputIter = std::ostream_iterator<DataStruct>;

    std::vector<DataStruct> data;

    while (true) {
        DataStruct temp;
        if (!std::cin) {
            std::cerr << "Error: Invalid input stream" << std::endl;
            break;
        }
        try {
            std::cin >> temp;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
        if (!std::cin) {
            std::cerr << "Error: Input stream failed" << std::endl;
            break;
        }
        data.push_back(temp);
        if (std::cin.eof()) {
            break;
        }
    }

    std::sort(data.begin(), data.end());

    if (!std::cout) {
        std::cerr << "Error: Invalid output stream" << std::endl;
        return 1;
    }

    std::copy(data.begin(), data.end(), OutputIter(std::cout, "\n"));

    return 0;
}
