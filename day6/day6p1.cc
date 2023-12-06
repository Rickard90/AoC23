#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

int calc_distance(int charge_time, int race_time) {
    return (race_time-charge_time)*charge_time;
}

int main() {
    std::string line;
    std::stringstream ss {};
    std::vector<int> times {};
    std::vector<int> distances {};
    
    int time {}, distance{};
    std::getline(std::cin, line);
    ss.str(line.substr(line.find(':')+1));
    while (ss >> time) 
    {
        times.push_back(time);
        std::cout << "adding time:" << time << std::endl;
    }
    ss.str("");
    ss.clear();
    std::getline(std::cin, line);
    ss.str(line.substr(line.find(':')+1));
    while (ss >> distance) 
    {
        distances.push_back(distance);
        std::cout << "adding dist:" << distance << std::endl;
    }
    int sum {1};
    for (int i {}; i < times.size(); i++)
    {
        int ways_to_win {};
        for (int charge_time {}; charge_time < times[i]; charge_time++)
        {
            if (calc_distance(charge_time, times[i]) > distances[i]) {
                ways_to_win++;
            }
        }
        sum *= ways_to_win;
    }


    ss.str("");
    ss.clear();
    std::cout << sum;

    return 0;
}