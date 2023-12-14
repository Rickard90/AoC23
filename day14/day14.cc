#include <iostream>
#include <vector>
#include <map>
#include <string>

void tilt(std::vector<std::string>& grid)
{
    bool done {};
    while (!done)
    {
        done = true;
        for (size_t y {}; y < grid.size(); y++)
        {
            for (size_t x {}; x < grid[y].size(); x++)
            {
                if (grid[y][x] == 'O')
                {
                    if (y > 0 && grid[y-1][x] == '.')
                    {
                        grid[y-1][x] = 'O';
                        grid[y][x] = '.';
                        done = false;
                    }
                }
            }
        }
    }
}

void turn(std::vector<std::string>& grid)
{
    std::vector<std::string> copy {};
    for (size_t x {}; x < grid[0].size(); x++)
    {
        copy.push_back("");
        for (size_t y {}; y < grid.size(); y++)
        {
            copy[x].push_back('.');
        }
    }
    
    for (size_t y {}; y < grid.size(); y++)
    {
        for (size_t x {}; x < grid[y].size(); x++)
        {
            copy[x][grid.size() - y -1] = grid[y][x];
        }
    }
    grid = copy;
}

int eval(std::vector<std::string>& grid)
{
    int sum {};
    for (size_t y {}; y < grid.size(); y++)
    {
        for (size_t x {}; x < grid[y].size(); x++)
        {
            if (grid[y][x] == 'O')
            {
                sum += grid.size() - y;
            }
        }
    }
    return sum;
}

int main() {
    std::string line;
    
    std::vector<std::string> grid {};
    
    while (std::getline(std::cin, line)) 
    {
        grid.push_back(line);
    }

    tilt(grid);
    std::cout << "part 1: " << eval(grid) << std::endl;
    turn(grid);

    for (int n {1}; n < 4*1000; n++)
    {
        tilt(grid);
        turn(grid);
    }
    

   std::cout << "part 2:" << eval(grid) << std::endl;

    return 0;
}