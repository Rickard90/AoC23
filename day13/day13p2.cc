#include <iostream>
#include <vector>
#include <string>


int dif(std::string const& l1, std::string const& l2)
{
    int dif {};
    for (size_t i {}; i < l1.size(); i++)
    {
        if (l1[i] != l2[i])
        {
            dif++;
        }
    }

    return dif;
}


int find_reflection(std::vector<std::string> const& lines)
{
    int found = 0;
    int smudges = 0;
    for (size_t split {1}; split < lines.size() && found == 0; split++)
    {
        for (size_t i {0}; split+i < lines.size() && split-i-1 < lines.size(); i++)
        {
            smudges += dif(lines.at(split+i), lines.at(split-i-1));
            if (smudges > 1) {
                found = 0;
                smudges = 0;
                break;
            } else {
                found = split;
            }
        }
        if (found != 0 && smudges != 1)
            found = 0;
    }

    if (smudges == 1)
        return found;
    return 0;
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
    return sum;
}


int main() {
    std::string line;
    int sum {};
    std::vector<std::string> lines {};

    while (std::getline(std::cin, line)) 
    {
        if (line.size() < 2) {
            sum += handle_map(lines);
            lines.clear();
        } else {
            lines.push_back(line);
        }
    }

   std::cout << "total sum: "<< sum << std::endl;

    return 0;
}