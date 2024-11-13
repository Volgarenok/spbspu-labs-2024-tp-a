#include <iostream>
#include <map>
#include "Commands.h"

int main() {
    std::map<std::string, TextMap> textMaps;

    std::cout << "Testing INPUT command:\n";
    stepanov::input(textMaps, "map1", "input.txt");
    stepanov::addLine(textMaps, "map1", "addedline", 7);
    stepanov::remove(textMaps, "map1", "addedline");
    stepanov::output(textMaps, "map1");
    std::cout << '\n';
    stepanov::input(textMaps, "map2", "input2.txt");
    stepanov::output(textMaps, "map2");
    std::cout << '\n';
    stepanov::add(textMaps,  "map3", "map1", "map2");
    stepanov::output(textMaps, "map3");
    std::cout << '\n';
    stepanov::merge(textMaps,  "map4", "map1", "map2");
    stepanov::output(textMaps, "map4");

    return 0;
}
