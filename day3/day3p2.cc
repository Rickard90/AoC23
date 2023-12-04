#include <iostream>
#include <vector>
#include <map>
#include <string>


int main() {
    std::string line;
    std::vector<std::vector<char>> grid {};
    std::vector<std::vector<std::pair<int,int>>> values {};
    int index {};
    int sum {};

    //load data
    while (std::getline(std::cin, line)) 
    {
        grid.emplace_back(std::vector<char> {});
        values.emplace_back(std::vector<std::pair<int,int>> {});
        for (char c : line)
        {
            grid.back().push_back(c);
            values.back().push_back(std::pair<int,int>{0,index});
        }
    }

    //read all numbers into a grid
    for (size_t x {}; x < grid.size(); x++)
    {
        for (size_t y {}; y < grid.size(); y++)
        {
            int value {};
            while (isdigit(grid[x][y])) {
                value *=10;
                std::string temp {grid[x][y]};
                value += std::stoi(temp);
                ++y;
            }
            if (value != 0) {
                index++;
            }
            for (int _y = y-1; isdigit(grid[x][_y]) && _y >= 0; _y-- ) {
                values[x][_y] = {value, index};
            }
        }
    }

    //find * and matching numbers
    for (size_t x {}; x < grid.size(); x++)
    {
        for (size_t y {}; y < grid.size(); y++)
        {
            if (grid[x][y] == '*') {
                int gear_value {1};
                std::map<int, int> gear_values;
                if ( x>0 && values[x-1][y].second != 0) {
                    gear_values[values[x-1][y].second] = values[x-1][y].first;
                }
                if ( x<grid.size()-1 && values[x+1][y].second != 0 ) {
                    gear_values[values[x+1][y].second] = values[x+1][y].first;
                }
                if ( y>0 && values[x][y-1].second != 0 ) {
                    gear_values[values[x][y-1].second] = values[x][y-1].first;
                }
                if ( y < grid.size()-1 && values[x][y+1].second != 0 ) {
                    gear_values[values[x][y+1].second] = values[x][y+1].first;
                }
                if ( x>0 && y>0 && values[x-1][y-1].second != 0 ) {
                    gear_values[values[x-1][y-1].second] = values[x-1][y-1].first;
                }
                if ( x<grid.size()-1 && y<grid.size()-1 && values[x+1][y+1].second != 0 ) {
                    gear_values[values[x+1][y+1].second] = values[x+1][y+1].first;
                }
                if ( x<grid.size()-1 && y>0 && values[x+1][y-1].second != 0 ) {
                    gear_values[values[x+1][y-1].second] = values[x+1][y-1].first;
                }
                if ( x>0 && y < grid.size()-1 && values[x-1][y+1].second != 0 ) {
                    gear_values[values[x-1][y].second] = values[x-1][y+1].first;
                }
                if (gear_values.size() == 2) {
                    for (std::pair<int,int> value: gear_values) {
                        gear_value *= value.second;
                    }
                }
                if (gear_value > 1) {
                    sum += gear_value;
                }
            }
        }
    }

    std::cout << "sum: " << sum << std::endl;
    return 0;
}