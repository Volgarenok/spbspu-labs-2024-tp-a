#include <iostream>
#include <map>
#include "Commands.h"

int main() {
    std::map<std::string, TextMap> textMaps;  // Карта, которая будет передаваться в функции

    std::cout << "Testing INPUT command:\n";
    stepanov::input(textMaps, "map1", "input.txt");  // "file1.txt" содержит несколько строк текста
    stepanov::output(textMaps, "map1");

    return 0;
}
