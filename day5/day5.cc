#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

struct seed {
    long long int soil {};
    long long int fert {};
    long long int water {};
    long long int light {};
    long long int temp {};
    long long int humid {};
    long long int location {};
};

int main() {
    std::string line;
    std::stringstream ss {};
    std::map<long long int, long long int> map_seed_soil {};
    std::map<long long int, long long int> map_soil_fert {};
    std::map<long long int, long long int> map_fert_water {};
    std::map<long long int, long long int> map_water_light {};
    std::map<long long int, long long int> map_light_temp {};
    std::map<long long int, long long int> map_temp_humid {};
    std::map<long long int, long long int> map_humid_location {};
    std::vector<seed> seeds {};
    std::map<long long int, long long int> location_seed {};

    std::getline(std::cin, line);
    ss.str(line.substr(line.find(':')+1));

    //read seeds
    long long int seed_nr {};
    while (ss >> seed_nr)
    {
        seeds.push_back();
    }
    ss.str("");
    ss.clear();

    for (long long int i {}; i < 100; i++) {
        map_seed_soil[i] = i;
        map_soil_fert[i] = i;
        map_fert_water[i] = i;
        map_water_light[i] = i;
        map_light_temp[i] = i;
        map_temp_humid[i] = i;
        map_humid_location[i] = i;
    }

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
        std::cout << "LINE: " << line << std::endl;
        if (line.empty()) {

        } else if (line.substr(0,4) == "seed") {
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
        } else { //ranges
            long long int dest {};
            long long int source {};
            int amount {};

            ss.str(line);
            ss >> dest >> source >> amount;
            //for (; amount >= 0; amount--){
            for (int seed : seeds) {


                switch (state) {
                    case seed_soil:
                        if ()

                        //map_seed_soil[source+amount] = dest+amount;
                        break;
                    case soil_fert:
                        map_soil_fert[source+amount] = dest+amount;
                        break;
                    case fert_water:
                        map_fert_water[source+amount] = dest+amount;
                        break;
                    case water_light:
                        map_water_light[source+amount] = dest+amount;
                        break;
                    case light_temp:
                        map_light_temp[source+amount] = dest+amount;
                        break;
                    case temp_humid:
                        map_temp_humid[source+amount] = dest+amount;
                        break;
                    case humid_location:
                        map_humid_location[source+amount] = dest+amount;
                        break;
                    default:
                        std::cout << "something went wrong\n";
                }
            }

            ss.str("");
            ss.clear();
        }

    }

    for (long long int seed : seeds) {
        long long int soil = map_seed_soil[seed];
        long long int fert = map_soil_fert[soil];
        long long int water = map_fert_water[fert];
        long long int light = map_water_light[water];
        long long int temp = map_light_temp[light];
        long long int humid = map_temp_humid[temp];
        long long int location = map_humid_location[humid];
        std::cout << "seed:" << seed << " soil:" << soil << " fert:" << fert << " water:" << water 
                  << " light:" << light << " temp:" << temp << " humid:" << humid << " location:" << location << std::endl;
        location_seed[location] = seed;
    }

    std::cout << (*std::min_element(location_seed.begin(), location_seed.end())).first << std::endl;



    
    return 0;
}