#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

long long int calc_distance(long long int charge_time, long long int race_time) {
    return (race_time-charge_time)*charge_time;
}

int main() {
    std::string line;
    std::stringstream ss {};
    std::vector<long long int> times {};
    std::vector<long long int> distances {};
    
    long long int time {}, distance{};
    std::getline(std::cin, line);
    std::string modified = line.substr(line.find(':')+1);
    modified.erase(std::remove_if(modified.begin(), modified.end(), isspace), modified.end());
    ss.str(modified);
    std::cout << modified << std::endl;
    ss >> time;
    times.push_back(time);
    std::cout << "adding time:" << time << std::endl;
    ss.str("");
    ss.clear();


    std::getline(std::cin, line);
    modified = line.substr(line.find(':')+1);
    modified.erase(std::remove_if(modified.begin(), modified.end(), isspace), modified.end());
    std::cout << modified << std::endl;
    ss.str(modified);
    ss >> distance;
    distances.push_back(distance);
    std::cout << "adding dist:" << distance << std::endl;
    
    long long int sum {1};
    for (long long int i {}; i < times.size(); i++)
    {
        long long int ways_to_win {};
        for (long long int charge_time {}; charge_time < times[i]; charge_time++)
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