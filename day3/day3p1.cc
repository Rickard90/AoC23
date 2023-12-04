#include <iostream>
#include <vector>
#include <string>


int main() {
    std::string line;
    std::vector<std::vector<char>> grid {};

    int sum {};

    while (std::getline(std::cin, line))
    {
        grid.emplace_back(std::vector<char> {});
        for (char c : line)
        {
            grid.back().push_back(c);
        }
    }

    for (size_t x {}; x < grid.size(); x++)
    {
        for (size_t y {}; y < grid.size(); y++)
        {
            int value {};
            char part {'.'};
            while (isdigit(grid[x][y])) {
                if (part == '.') {
                    if ( x>0 && grid[x-1][y] != '.' && !isdigit(grid[x-1][y]) ) {
                        part = grid[x-1][y];
                    }
                    if (x<grid.size()-1 && grid[x+1][y] != '.' && !isdigit(grid[x+1][y]) ) {
                        part = grid[x+1][y];
                    }
                    if ( y>0 && grid[x][y-1] != '.' && !isdigit(grid[x][y-1]) ) {
                        part = grid[x][y-1];
                    }
                    if ( y < grid.size()-1 && grid[x][y+1] != '.' && !isdigit(grid[x][y+1]) ) {
                        part = grid[x][y+1];
                    }
                    if ( x>0 && y>0 && grid[x-1][y-1] != '.' && !isdigit(grid[x-1][y-1]) ) {
                        part = grid[x-1][y-1];
                    }
                    if ( x<grid.size()-2 && y<grid.size()-1 && grid[x+1][y+1] != '.' && !isdigit(grid[x+1][y+1]) ) {
                        part = grid[x+1][y+1];
                    }
                    if ( x<grid.size()-2 && y>0 && grid[x+1][y-1] != '.' && !isdigit(grid[x+1][y-1]) ) {
                        part = grid[x+1][y-1];
                    }
                    if ( x>0 && y < grid.size()-1 && grid[x-1][y+1] != '.' && !isdigit(grid[x-1][y+1]) ) {
                        part = grid[x-1][y+1];
                    }
                }
                value *=10;
                std::string temp {grid[x][y]};
                value += std::stoi(temp);
                ++y;
            }
            if (part != '.' && !isdigit(part)) {
                sum += value;
            }
        }   
    }

    std::cout << "sum: " << sum << std::endl;
    return 0;
}