#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <iterator>
#include "dataStruct.hpp"

int main() {
  using lazareva::DataStruct;
  std::vector<DataStruct> data;

    while (!std::cin.eof()) {
    using input_it = std::istream_iterator<DataStruct>;
    std::copy(input_it{std::cin}, input_it{}, std::back_inserter(data));

    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  // Отладка: Вывод считанных данных
  std::cout << "Считанные данные:\n";
  for (const auto& item : data) {
    std::cout << item << std::endl;
  }

  // Сортировка
  std::sort(data.begin(), data.end());

  // Отладка: Вывод отсортированных данных
  std::cout << "Отсортированные данные:\n";
  for (const auto& item : data) {
    std::cout << item << std::endl;
  }

  // Вывод в поток вывода
  using output_it = std::ostream_iterator<DataStruct>;
  std::copy(data.cbegin(), data.cend(), output_it{std::cout, "\n"});

  return 0;
}
