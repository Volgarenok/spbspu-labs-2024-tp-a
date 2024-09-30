#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

namespace petrov {

    struct DataStruct {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;

        // Переопределение оператора побитового сдвига для ввода
        friend std::istream& operator>>(std::istream& is, DataStruct& data) {
            char ch;
            std::string key1_str, key2_str, key3_str;

            // Чтение данных в формате (:key1 value:key2 value:key3 value:)
            is >> ch; // Считываем открывающую скобку
            if (ch != '(') {
                is.setstate(std::ios::failbit);
                return is;
            }

            // Чтение key1
            is >> key1_str >> data.key1;
            if (is.fail() || key1_str.find("key1") == std::string::npos) {
                is.setstate(std::ios::failbit);
                return is;
            }

            // Чтение key2
            is >> key2_str >> data.key2;
            if (is.fail() || key2_str.find("key2") == std::string::npos) {
                is.setstate(std::ios::failbit);
                return is;
            }

            // Чтение key3
            is >> key3_str;
            std::getline(is, data.key3, ':'); // Читаем до двоеточия, чтобы получить строку
            if (is.fail() || key3_str.find("key3") == std::string::npos) {
                is.setstate(std::ios::failbit);
                return is;
            }

            // Чтение закрывающей скобки
            is >> ch; // Считываем закрывающую скобку
            if (ch != ')') {
                is.setstate(std::ios::failbit);
            }

            return is;
        }

        // Переопределение оператора побитового сдвига для вывода
        friend std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
            os << "(:key1 " << data.key1 << ":key2 " << data.key2 << ":key3 \"" << data.key3 << "\":)";
            return os;
        }
    };

    bool compare(const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1) return a.key1 < b.key1;
        if (a.key2 != b.key2) return a.key2 < b.key2;
        return a.key3.length() < b.key3.length();
    }

} // namespace petrov

int main() {
    std::cout << "petrov.ivan" << std::endl;

    std::vector<petrov::DataStruct> data;
    petrov::DataStruct temp;

    // Чтение данных
    while (std::cin >> temp) {
        data.push_back(temp);
    }

    // Сортировка данных
    std::sort(data.begin(), data.end(), petrov::compare);

    // Вывод отсортированных данных
    std::copy(data.begin(), data.end(), std::ostream_iterator<petrov::DataStruct>(std::cout, "\n"));

    return 0;
}


/*#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>

#include "DataStruct.hpp"

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
}*/
