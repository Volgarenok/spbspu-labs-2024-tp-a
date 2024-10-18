#include <algorithm>
#include <cmath>
#include <complex>
#include <exception>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "DataStruct.hpp"

using kumekova::DataStruct;

int main()
{
  try
    {
    std::string input = "";
    std::vector<DataStruct> data;

    while (std::getline(std::cin, input))
    {
      std::istringstream iss(input);
      DataStruct temp;
      if (iss >> temp)
      {
        data.push_back(temp);
      }
    }

    std::sort(std::begin(data), std::end(data), kumekova::compareDataStruct);

    std::copy(std::begin(data), std::end(data),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));
  }
  catch (std::exception &ex)
    {
    std::cerr << ex.what();
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
