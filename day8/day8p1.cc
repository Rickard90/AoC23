#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>

int main() {
    std::string line;
    std::map<std::string, std::pair<std::string, std::string>> nodes {};

    std::string path;
    std::getline(std::cin, path);

    while (std::getline(std::cin, line)) 
    {
        if (line.size()>5) {
            std::string name {}, left {}, right {};
            name = line.substr(0,3);
            left = line.substr(7,3);
            right = line.substr(12,3);
            nodes[name] = std::pair<std::string, std::string>(left, right);
        }
    }

    std::string current_node = "AAA";
    int steps {};

    for (size_t i {}; current_node != "ZZZ"; i++)
    {
        if (i > path.length()-2) {
            i = 0;
        }
        steps++;
        char c = path[i];
        if (c == 'L') {
            std::string next = nodes[current_node].first;
            current_node = next;
        }
        else { //'R'
            std::string next = nodes[current_node].second;
            current_node = next;
        }
    }

    std::cout << "Length: " << steps;

    return 0;
}