#include <iostream>
#include <vector>
#include <string>

struct galaxy {
    int x {};
    int y {};
};

int distance(galaxy const a, galaxy const b) {
    return std::abs(a.x-b.x) + std::abs(a.y-b.y);
}

int main() {
    std::string line;
    
    std::vector<std::string> grid {};
    
    while (std::getline(std::cin, line)) 
    {
        if (static_cast<int>(line.find_first_of('#')) == -1)
            grid.push_back(line);
        grid.push_back(line);
    }

    for (size_t x = 0; x < grid[0].size(); x++) 
    {
        bool empty = true;
        for (std::string& s : grid)
        {
            empty = s[x]=='.'?empty: false;
        }
        if (empty) {
            for (std::string& s : grid)
            {
                s.insert(x, ".");
            }
            x++;
        }
    }

    std::vector<galaxy> galaxies {};
    for (int x {}; x < static_cast<int>(grid[0].size()); x++)
    {
        for (int y {}; y < static_cast<int>(grid.size()); y++)
        {
            if (grid.at(y).at(x) == '#') {
                galaxies.push_back(galaxy{x,y});
            }
        }
    }

    int sum {};
    for (int i {}; i < galaxies.size(); i++) {
        for (int j {i+1}; j < galaxies.size(); j++) {
            sum += distance(galaxies[i], galaxies[j]);
        }
    }

   std::cout << sum << std::endl;

    return 0;
}