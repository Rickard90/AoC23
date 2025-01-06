#include <iostream>
#include <vector>
#include <string>
#include <sstream>

//original solution

struct Pos {
    int x {};
    int y {};
};

Pos next_pos(Pos prev, char dir, int steps)
{
    Pos ret {prev};   
    if (dir == 'U')
    {
        ret.y-=steps;
    } else if (dir == 'D')
    {
        ret.y+=steps;
    } else if (dir == 'L')
    {
        ret.x-=steps;
    } else if (dir == 'R')
    {
        ret.x+=steps;
    }
    return ret;
}


void filloutside(std::vector<std::vector<char>>& grid, int x, int y)
{
    if (y >= 0 && x >= 0 && x < grid.at(y).size() && y < grid.size() && grid.at(y).at(x) == '.')
    {
        grid.at(y).at(x) = '-';
        if (y < static_cast<int>(grid.size())-1 && grid.at(y+1).at(x) == '.')
        {
            filloutside(grid, x, y+1);
        }
        if (x < static_cast<int>(grid.at(y).size())-1 && grid.at(y).at(x+1) == '.')
        {
            filloutside(grid, x+1, y);
        }
        if (y > 0 && grid.at(y-1).at(x) == '.')
        {
            filloutside(grid, x, y-1);
        }
        if (x > 0 && grid.at(y).at(x-1) == '.')
        {
            filloutside(grid, x-1, y);
        }
    }
}

int main() {
    std::string line;
    std::stringstream ss {};
    std::vector<std::vector<char>> grid {};
    std::vector<std::pair<char, int>> instructions {};

    int max_x {};
    int max_y {};
    int min_x {};
    int min_y {};
    Pos pos {};
    while (std::getline(std::cin, line)) 
    {
        ss.str(line);
        if (line.size() > 2) 
        {
            std::pair<char, int> dir_steps {};
            ss >> dir_steps.first >> dir_steps.second;
            instructions.push_back(dir_steps);
            pos = next_pos(pos, dir_steps.first, dir_steps.second);
            max_x = std::max(max_x, pos.x);
            min_x = std::min(min_x, pos.x);
            max_y = std::max(max_y, pos.y);
            min_y = std::min(min_y, pos.y);
        }
        ss.str("");
        ss.clear();
    }

    for (int y {-1}; y <= max_y-min_y + 1; y++)
    {
        grid.push_back({});
        for (int x {-1}; x <= max_x-min_x + 1; x++)
        {
            grid.back().push_back('.');
        }
    }

    pos = {-min_x+1, -min_y+1};
    for (std::pair<char, int> i : instructions)
    {
        for (int step {}; step < i.second; step++)
        {
            if (i.first == 'U')
            {
                pos.y--;
            } else if (i.first == 'D')
            {
                pos.y++;
            } else if (i.first == 'L')
            {
                pos.x--;
            } else if (i.first == 'R')
            {
                pos.x++;
            }
            grid.at(pos.y).at(pos.x) = '#';
        }
    }
    grid.at(-min_y+1).at(-min_x+1) = 'S';
    
    //filloutside(grid, 0, 0);
    
    int outside {};
    for (size_t y {}; y < grid.size(); y++)
    {
        for (size_t x {}; x <= grid[y].size()-1; x++)
        {
            std::cout << grid[y][x];
            if (grid.at(y).at(x) == '-')
                outside++;
        }
        std::cout << std::endl;
    }

    std::cout << "total sum: "<< (grid.size()*grid[0].size()-outside) << std::endl;
    std::cout << std::flush;
    std::cout << std::endl;

    return 0;
}