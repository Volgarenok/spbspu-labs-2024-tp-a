#include "datastruct.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <limits>

int main()
{
  using namespace skopchenko;
  std::vector<DataStruct> dataStructs;

  // Считывание данных из стандартного ввода
  std::istream_iterator<DataStruct> it(std::cin);
  std::istream_iterator<DataStruct> end;

  // Копируем только корректные структуры данных
  std::copy_if(it, end, std::back_inserter(dataStructs),
               [](const DataStruct &data) {
                 return !std::cin.fail();
               });

  // Сортировка данных
  std::sort(dataStructs.begin(), dataStructs.end(), compare);

  // Вывод отсортированных данных в стандартный вывод
  std::copy(dataStructs.begin(), dataStructs.end(),
            std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}

