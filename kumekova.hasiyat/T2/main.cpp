#include <algorithm>
#include <vector>
#include "DataStruct.hpp"
int main()
{
	using namespace kumekova;
	std::vector<DataStruct> data;
	try {
		std::copy(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>(), std::back_inserter(data));
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	std::sort(data.begin(), data.end());
	std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

	return 0;
}//Main.cpp
