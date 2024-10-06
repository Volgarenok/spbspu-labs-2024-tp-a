#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <complex>
#include <cmath>
#include <exception>

#include "DataStruct.hpp"

using kumekova::DataStruct;

int main()
{
    try
        {
            std::string input;
            std::vector<DataStruct> data;
            
            while (std::getline(std::cin, input))
            {
                std::istringstream iss(input);
                DataStruct temp;
                if (iss >> temp)
                {
                    data.push_back(std::move(temp));
                }
            }

            std::sort(data.begin(), data.end(), kumekova::compareDataStruct);

            std::copy(
                data.begin(),
                data.end(),
                std::ostream_iterator<DataStruct>(std::cout, "\n")
                );
        }
    catch (std::exception& ex)
        {
            std::cerr << ex.what();
            return EXIT_FAILURE;
        }
    return EXIT_SUCCESS;
}
