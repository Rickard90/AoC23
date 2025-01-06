#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

#define debug false


void search(std::map<std::string, std::vector<std::string>>& nodes, 
            std::queue<std::string>& s_queue,
            std::set<std::string>& connected, 
            std::pair<std::string, std::string> const& cut1,
            std::pair<std::string, std::string> const& cut2,
            std::pair<std::string, std::string> const& cut3, 
            size_t& group)
{
    bool cut1first {}, cut1second {};
    bool cut2first {}, cut2second {};
    bool cut3first {}, cut3second {};
    if (s_queue.front() == cut1.first)
    {
        cut1first = true;
    } else if (s_queue.front() == cut1.second)
    {
        cut1second = true;
    }
    
    while (!s_queue.empty())
    {
        std::string from = s_queue.front();
        s_queue.pop();
        for (auto to : nodes[from])
        {
            if (!(from == cut1.first && to == cut1.second) &&
                !(from == cut1.second && to == cut1.first) &&
                !(from == cut2.first && to == cut2.second) &&
                !(from == cut2.second && to == cut2.first) &&
                !(from == cut3.first && to == cut3.second) &&
                !(from == cut3.second && to == cut3.first) &&
                std::count(connected.begin(), connected.end(), to) < 1)
            {

                if (to == cut1.first)
                {
                    cut1first = true;
                } else if (to == cut1.second)
                {
                    cut1second = true;
                }
                if (to == cut2.first)
                {
                    cut2first = true;
                } else if (to == cut2.second)
                {
                    cut2second = true;
                }
                if (to == cut3.first)
                {
                    cut3first = true;
                } else if (to == cut3.second)
                {
                    cut3second = true;
                }
                if ((cut1first && cut1second) || (cut2first && cut2second) || (cut3first && cut3second))
                {
                    group = 0;
                    s_queue = {};
                    return ;
                }
                s_queue.push(to);
                connected.insert(to);
                group++;
                
            }
        }
    }

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
    for (size_t cut1 {}; cut1 < connections.size(); cut1++)
    {
        //std::cout << cut1 << " / " << connections.size() << std::endl;
        for (size_t cut2 {cut1+1}; cut2 < connections.size(); cut2++)
        {
            std::cout << "  " << cut2 << " / " << connections.size() << std::endl;
            for (size_t cut3 {cut2+1}; cut3 < connections.size(); cut3++)
            {
                //std::cout << "      " << cut3 << " / " << connections.size() << std::endl;
                size_t group1 {1}, group2 {};
                connected.clear();
                s_queue.push(connections[cut1].first);
                connected.insert(connections[cut1].first);
                search(nodes, s_queue, connected, connections[cut1], connections[cut2], connections[cut3], group1);
                
                if (group1 > 0 && std::count(connected.begin(), connected.end(), connections[cut1].second) < 1)
                {
                    group2++;
                    s_queue.push(connections[cut1].second);
                    connected.insert(connections[cut1].second);
                    search(nodes, s_queue, connected, connections[cut1], connections[cut2], connections[cut3], group2);
                    
                }
                if (group1*group2 > part1)
                {
                    part1 = group1*group2;
                    std::cout << connections[cut1].first << "-" << connections[cut1].second << std::endl;
                    std::cout << connections[cut2].first << "-" << connections[cut2].second << std::endl;
                    std::cout << connections[cut3].first << "-" << connections[cut3].second << std::endl;
                    std::cout << group1 << " * " << group2 << " = " << part1 << std::endl;

                }
                //part1 = std::max(part1, group1.size()*group2.size());
                
            }
        }
    }

    
    std::cout << "\nPart1: " << part1 << std::endl;

    return 0;
}