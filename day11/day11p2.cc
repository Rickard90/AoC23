#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct galaxy {
    long long int x {};
    long long int y {};
};

long long int distance(galaxy const a, galaxy const b) {
    return std::abs(a.x-b.x) + std::abs(a.y-b.y);
}

int main() {
    std::string line;

    
    std::vector<std::string> grid {};
    
    while (std::getline(std::cin, line)) 
    {
        grid.push_back(line);
    }

    std::vector<int> empty_col {};
    for (size_t x = 0; x < grid[0].size(); x++) 
    {
        bool empty = true;
        for (std::string& s : grid)
        {
            empty = s[x]=='.'?empty: false;
        }
        if (empty) {
            empty_col.push_back(x);
        }
    }


    std::vector<galaxy> galaxies {};
    for (long long int y {}, mod_y {}; y < static_cast<long long int>(grid.size()); y++)
    {
        if (static_cast<int>(grid[y].find_first_of('#')) == -1) {
            mod_y+=999999;
        }
        for (long long int x {}, mod_x {}; x < static_cast<long long int>(grid[y].size()); x++)
        {
            if (std::count(empty_col.begin(), empty_col.end(), x) == 1) {
                mod_x += 999999;
            }
            if (grid[y][x] == '#') {
                galaxies.push_back(galaxy{mod_x+x, mod_y+y});
            }
        }
    }

    long long int sum {};
    for (size_t i {}; i < galaxies.size(); i++) {
        for (size_t j {i+1}; j < galaxies.size(); j++) {
            sum += distance(galaxies[i], galaxies[j]);
        }
    }

   std::cout << sum << std::endl;

    return 0;
}