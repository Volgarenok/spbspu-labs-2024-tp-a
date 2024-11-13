#include <iostream>
#include <map>
#include "Commands.h"

int main() {
    std::map<std::string, TextMap> textMaps;

    std::cout << "Testing INPUT command:\n";
    stepanov::input(textMaps, "map1", "input.txt");
    stepanov::output(textMaps, "map1");

    return 0;
}
