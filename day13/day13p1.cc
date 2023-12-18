#include <iostream>
#include <vector>
#include <string>

int find_reflection(std::vector<std::string> const& lines)
{
    int found = 0;
    for (size_t split {1}; split < lines.size() && found == 0; split++)
    {
        for (size_t i {0}; split+i < lines.size() && split-i-1 < lines.size(); i++)
        {
            if (lines.at(split+i) != lines.at(split-i-1)) {
                found = 0;
                break;
            } else {
                found = split;
            }
        }
    }
    return found;
}


void turn(std::vector<std::string>& lines)
{
    std::vector<std::string> line_copy;

    for (size_t i {}; i < lines[0].size(); i++)
    {
        line_copy.push_back("");
    }

    for (size_t i {}; i < lines.size(); i++)
    {
        
        for (size_t j {}; j < lines[i].size(); j++)
        {
            line_copy[j].push_back(lines[i][j]);
        }
    }
    lines = line_copy;
}


int handle_map(std::vector<std::string>& lines)
{
    int sum {};
    sum = 100 * find_reflection(lines);
    turn(lines);
    sum += find_reflection(lines);
    turn(lines);
    return sum;
}


int main() {
    std::string line;
    int sum {};
    std::stringstream ss {};
    std::vector<std::string> lines {};

    while (std::getline(std::cin, line)) 
    {
        if (line.size() < 2) {
            sum += handle_map(lines);
            std::cout << "one map done" << std::endl;
            lines.clear();
        } else {
            lines.push_back(line);
        }
    }
    


   std::cout << "total sum: "<< sum << std::endl;

    return 0;
}