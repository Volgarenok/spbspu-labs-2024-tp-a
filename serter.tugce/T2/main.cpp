#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "dataIO.hpp"
#include "dataStruct.hpp"

int main()
{
    std::vector<serter::DataStruct> data;
    serter::DataStruct temp;

    // Veri okuma
    while (std::cin >> temp)
    {
        data.push_back(temp);
    }

    if (std::cin.eof())
    {
        // EOF hatası yoksa sıralama yap
        std::sort(data.begin(), data.end());

        // Verileri yazdır
        std::copy(data.begin(), data.end(), std::ostream_iterator<serter::DataStruct>(std::cout, "\n"));
    }
    else
    {
        // Giriş akışında hata oluştu
        std::cerr << "Giriş akışında bir hata oluştu.\n";
        return 1;
    }

    return 0;
}

