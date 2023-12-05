#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

struct seed {
    long long int nr {};
    long long int soil {-1};
    long long int fert {-1};
    long long int water {-1};
    long long int light {-1};
    long long int temp {-1};
    long long int humid {-1};
    long long int location {-1};
};

bool in_range(long long int index, long long int start, long long int length) 
{
    //std::cout << "checking if index:" << index << " is in range " << start << ":" << start+length << " returning " << (index >= start && index <= start+length-1) << std::endl;
    return index >= start && index <= start+length-1;
}

int main() {
    std::string line;
    std::stringstream ss {};
    std::vector<seed> seeds {};
    std::vector<long long int> locations {};

    std::getline(std::cin, line);
    ss.str(line.substr(line.find(':')+1));

    //read seeds
    long long int seed_nr {};
    while (ss >> seed_nr)
    {
        seeds.push_back(seed{seed_nr});
    }
    ss.str("");
    ss.clear();

    enum states {
        seed_soil,
        soil_fert,
        fert_water,
        water_light,
        light_temp,
        temp_humid,
        humid_location
    };
    states state = seed_soil;
    //read maps
    while (std::getline(std::cin, line))
    {
        if (line.substr(0,4) == "seed") {
            state = seed_soil;
        } else if (line.substr(0,4) == "soil") {
            state = soil_fert;
        } else if (line.substr(0,4) == "fert") {
            state = fert_water;
        } else if (line.substr(0,5) == "water") {
            state = water_light;
        } else if (line.substr(0,5) == "light") {
            state = light_temp;
        } else if (line.substr(0,4) == "temp") {
            state = temp_humid;
        } else if (line.substr(0,5) == "humid") {
            state = humid_location;
        } else if (line.length()>0 && (line.at(0))) { //ranges
            long long int dest {};
            long long int source {};
            int amount {};

            ss.str(line);
            ss >> dest >> source >> amount;
            long long int offset = dest-source;
            for (auto& seed : seeds) {
                //std::cout << "seed: " << seed.nr << " soil: " << seed.soil << " fert: " << seed.fert << " water: " << seed.water 
                //          << " light: " << seed.light << " temp: " << seed.temp << " humid: " << seed.humid << "location: " << seed.location << std::endl;
                switch (state) {
                    case seed_soil:
                        if (seed.soil == -1) {
                            seed.soil = seed.nr;
                        }
                        if (in_range(seed.nr, source, amount)) {
                            seed.soil += offset;
                        }
                        break;
                    case soil_fert:
                        if (seed.fert == -1) {
                            seed.fert = seed.soil;
                        }
                        if (in_range(seed.soil, source, amount)) {
                            seed.fert += offset;
                        }
                        break;
                    case fert_water:
                        if (seed.water == -1) {
                            seed.water = seed.fert;
                        }
                        if (in_range(seed.fert, source, amount)) {
                            seed.water += offset;
                        }
                        break;
                    case water_light:
                        if (seed.light == -1) {
                            seed.light = seed.water;
                        }
                        if (in_range(seed.water, source, amount)) {
                            seed.light += offset;
                        }
                        break;
                    case light_temp:
                        if (seed.temp == -1) {
                            seed.temp = seed.light;
                        }
                        if (in_range(seed.light, source, amount)) {
                            seed.temp += offset;
                        }
                        break;
                    case temp_humid:
                        if (seed.humid == -1) {
                            seed.humid = seed.temp;
                        }
                        if (in_range(seed.temp, source, amount)) {
                            seed.humid += offset;
                        }
                        break;
                    case humid_location:
                        if (seed.location == -1) {
                            seed.location = seed.humid;
                        }
                        if (in_range(seed.humid, source, amount)) {
                            seed.location += offset;
                        }
                        break;
                    default:
                        std::cout << "something went wrong\n";
                }
            }

            ss.str("");
            ss.clear();
        }

    }

    for (seed seed : seeds) {
        std::cout << "seed:" << seed.nr << " soil:" << seed.soil << " fert:" << seed.fert << " water:" << seed.water 
                  << " light:" << seed.light << " temp:" << seed.temp << " humid:" << seed.humid << " location:" << seed.location << std::endl;
        locations.push_back(seed.location);
        std::cout << seed.location << std::endl;
    }

    std::cout << "Answer: "<< *std::min_element(locations.begin(), locations.end()) << std::endl;



    
    return 0;
}