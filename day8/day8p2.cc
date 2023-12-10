#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

int main() {
    std::string line;
    std::map<std::string, std::pair<std::string, std::string>> nodes {};
    std::vector<std::string> locations {};
    std::vector<int> cycle {};

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
            if (name[2] == 'A') {
                locations.push_back(name);
                cycle.push_back(0);
            }

        }
    }

    for (auto s : locations)
    {
        std::cout << s << ' ';
    }
    std::cout << "\n" << std::endl;


    for (size_t j {}; j < locations.size(); j++)
    {
        for (size_t i {}; locations[j][2]!='Z'; i++)
        {
            if (i > path.length()-2) {
                i = 0;
            }
            cycle[j]++;
        
            if (path.at(i) == 'L') {
                locations[j] = nodes[locations[j]].first;
            }
            else { //'R'
                locations[j] = nodes[locations[j]].second;
            }
        }
    }
    long long int steps {1};
    for (size_t i {}; i < locations.size(); i++)
    {
        steps = std::lcm(cycle[i], steps);
    }

    std::cout << "Length: " << steps;

    return 0;
}