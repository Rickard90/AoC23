#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

#define debug false


int search(std::map<std::string, std::vector<std::string>>& nodes, 
            std::queue<std::string>& s_queue,
            std::set<std::string>& connected)
{
    
    
    while (!s_queue.empty())
    {
        std::string from = s_queue.front();
        s_queue.pop();
        for (auto to : nodes[from])
        {
            if (std::count(connected.begin(), connected.end(), to) < 1)
            {
                s_queue.push(to);
                connected.insert(to);
            }
        }
        if (s_queue.size() == 3)
        {
            return connected.size();
        }
    }
    return 0;
}


int main() {
    std::string line {};
    std::map<std::string, std::vector<std::string>> nodes {};
    std::vector<std::pair<std::string, std::string>> connections {};
    std::stringstream ss {};
    size_t part1 {};


    while (std::getline(std::cin, line)) 
    {
        ss << line;
        std::string lhs, rhs;

        ss >> lhs;
        lhs = lhs.substr(0, lhs.size()-1);
        while (ss >> rhs)
        {
            nodes[rhs].push_back(lhs);
            nodes[lhs].push_back(rhs);
            connections.push_back({lhs, rhs});
        }
        
        ss.str("");
        ss.clear();
    }

    for (auto from : nodes)
    {
        std::cout << from.first << ":   ";
        for (auto to : from.second)
        {
            std::cout << to << " ";
        }
        std::cout << std::endl;
    }


    std::set<std::string> connected {};
    std::queue<std::string> s_queue {};
    for (auto node : nodes)
    {
        
        size_t group1 {1};
        connected.clear();
        s_queue.push(node.first);
        connected.insert(node.first);
        group1 = search(nodes, s_queue, connected);
        
        if (group1*(nodes.size()-group1) > part1)
        {
            part1 = group1*(nodes.size()-group1);
            std::cout << group1 << " * " << (nodes.size()-group1) << " = " << part1 << std::endl;

        }
        //part1 = std::max(part1, group1.size()*group2.size());
        
    }
    
    std::cout << "\nPart1: " << part1 << std::endl;

    return 0;
}