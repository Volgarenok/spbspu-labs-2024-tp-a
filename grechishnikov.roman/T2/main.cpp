#include <iostream>
#include <vector>
#include <iterator>
#include "dataStruct.hpp"

#include "keyDelimiters.hpp"
#include <complex>

int main()
{
  using namespace grechishnikov;

  size_t oct = 0;
  std::cin >> Key1_Delimiter{ oct };
  std::cout << oct << '\n';

  std::complex< double > com;
  std::cin >> Key2_Delimiter{ com };
  std::cout << com << '\n';

  std::string st;
  std::cin >> Key3_Delimiter{ st };
  std::cout << st << '\n';


  if (!std::cin)
  {
    std::cerr << "Error\n";
    return 1;
  }


  std::vector< DataStruct > data{ {10, { 3.1, 3.003 }, "aaa" } };

//  using input_it_t = std::istream_iterator< DataStruct >;
//  std::copy(input_it_t{ std::sin }, input_it_t{}, std::back_inserter(data));

  using output_it_t = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), output_it_t{ std::cout, "\n" });
}
