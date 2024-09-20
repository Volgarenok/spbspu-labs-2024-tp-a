#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <limits>
#include <map>
#include <functional>
#include <vector>

#include "Geometry.h"
#include "Commands.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Error: Invalid number of arguments.\n";
        return EXIT_FAILURE;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cout << "Error: Unable to open file.\n";
        return EXIT_FAILURE;
    }

    std::vector<serter::Polygon> data;
    using iter = std::istream_iterator<serter::Polygon>;

    try {
        std::copy(iter(input), iter(), std::back_inserter(data));
    } catch (const std::exception& e) {
        std::cout << "Error: Failed to read polygons from file.\n";
        return EXIT_FAILURE;
    }

    std::map<std::string, std::function<void(std::istream&, std::ostream&)>> commands;
    using namespace std::placeholders;
    commands["AREA"] = std::bind(serter::area, std::cref(data), _1, _2);
    commands["MIN"] = std::bind(serter::min, std::cref(data), _1, _2);
    commands["MAX"] = std::bind(serter::max, std::cref(data), _1, _2);
    commands["COUNT"] = std::bind(serter::count, std::cref(data), _1, _2);
    commands["ECHO"] = std::bind(serter::echo, std::ref(data), _1, _2);
    commands["RMECHO"] = std::bind(serter::rmEcho, std::ref(data), _1, _2);
    commands["LESSAREA"] = std::bind(serter::lessArea, std::cref(data), _1, _2);

    while (true) {
        std::string command;
        std::cout << "> ";  // Kullanıcıdan komut girişi bekliyor
        std::cin >> command;

        if (!std::cin) {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.clear();  // Hatalı giriş temizleniyor
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;  // Bir sonraki komutu bekle
        }

        if (command == "exit") {
            break;  // Programdan çıkış
        }

        auto it = commands.find(command);
        if (it != commands.end()) {
            try {
                it->second(std::cin, std::cout);  // Komut çalıştırılıyor
            } catch (const std::exception& e) {
                std::cout << "<INVALID COMMAND>: " << e.what() << "\n";
                std::cin.clear();  // Girdiyi temizle
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
