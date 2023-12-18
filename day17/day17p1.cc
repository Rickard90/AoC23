#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>


enum direction {
    north, east, south, west
};

struct Pos {
    int dist {};
    size_t x {};
    size_t y {};
    size_t steps {};
    direction prev {};
    std::vector<std::pair<int, int>> path {};
};


int main() {
    std::string line {};
    std::vector<std::vector<int>> grid {};
    std::vector<std::vector<std::vector<std::vector<int>>>> visited {};

    while (std::getline(std::cin, line)) 
    {
        grid.push_back({});
        visited.push_back({});//y
        for (size_t x = 0; x < line.length(); x++)
        {
            if (std::isdigit(line[x]))
            {
                std::string s = {line[x]};
                grid.back().push_back(std::stoi(s));
                visited.back().push_back({});//x
                for (int i {}; i < 4; i++)
                {
                    visited.back().back().push_back({});//north->east->south->west
                    visited.back().back().back().push_back(9999999);//0 steps
                    visited.back().back().back().push_back(9999999);//1 steps
                    visited.back().back().back().push_back(9999999);//2 steps
                }
            }
        }
    }

    for (auto v : grid)
    {
        for (int i : v)
        {
            std::cout << i;
        }
        std::cout << std::endl;
    }

    Pos pos;
    Pos new_pos {};
    std::vector<Pos> data {};
    std::priority_queue search (data.begin(), data.end(), [](Pos a, Pos b){
        return a.dist > b.dist;
    });

    Pos start {0, 0, 0, 0, south};
    search.push(start);

    int part1_sum {};
    do {
        pos = search.top();
        search.pop();
        size_t& x = pos.x;
        size_t& y = pos.y;

        pos.path.push_back({x, y});

        
        if ( x > 0 && !(pos.prev == west && pos.steps > 1) && pos.prev != east )
        {
            new_pos = {pos.dist+grid[y][x-1], x-1, y, pos.steps, pos.prev, pos.path};
            if (new_pos.x == grid[new_pos.x].size()-1 && new_pos.y == grid.size()-1)
            {
                part1_sum = new_pos.dist;
                break;
            }
            if (new_pos.prev == west)
            {
                new_pos.steps++;
            } 
            else
            {
                new_pos.steps = 0;
                new_pos.prev = west;
            }
            if (visited[y][x-1][west][new_pos.steps] > pos.dist+grid[y][x-1])
            {
                visited[y][x-1][west][new_pos.steps] = pos.dist+grid[y][x-1];
                search.push(new_pos);
            }
        }
        if ( x < grid[y].size()-1 && !(pos.prev == east && pos.steps > 1) && pos.prev != west )
        {
            new_pos = {pos.dist+grid[y][x+1], x+1, y, pos.steps, pos.prev, pos.path};
            if (new_pos.x == grid[pos.x].size()-1 && new_pos.y == grid.size()-1)
            {
                part1_sum = new_pos.dist;
                break;
            }
            if (new_pos.prev == east)
            {
                new_pos.steps++;
            } 
            else
            {
                new_pos.steps = 0;
                new_pos.prev = east;
            }
            if (visited[y][x+1][east][new_pos.steps] > pos.dist+grid[y][x+1])
            {
                visited[y][x+1][east][new_pos.steps] = pos.dist+grid[y][x+1];
                search.push(new_pos);
            }
        }
        if ( y > 0 && !(pos.prev == north && pos.steps > 1) && pos.prev != south )
        {
            new_pos = {pos.dist+grid[y-1][x], x, y-1, pos.steps, pos.prev, pos.path};
            if (new_pos.x == grid[pos.x].size()-1 && new_pos.y == grid.size()-1)
            {
                part1_sum = new_pos.dist;
                break;
            }
            if (new_pos.prev == north)
            {
                new_pos.steps++;
            } 
            else
            {
                new_pos.steps = 0;
                new_pos.prev = north;
            }
            if (visited[y-1][x][north][new_pos.steps] > pos.dist+grid[y-1][x])
            {
                visited[y-1][x][north][new_pos.steps] = pos.dist+grid[y-1][x];
                search.push(new_pos);
            }
        }
        if ( y < grid.size()-1 && !(pos.prev == south && pos.steps > 1) && pos.prev != north )
        {
            new_pos = {pos.dist+grid[y+1][x], x, y+1, pos.steps, pos.prev, pos.path};
            if (new_pos.x == grid[pos.x].size()-1 && new_pos.y == grid.size()-1)
            {
                part1_sum = new_pos.dist;
                break;
            }
            if (new_pos.prev == south)
            {
                new_pos.steps++;
            } 
            else
            {
                new_pos.steps = 0;
                new_pos.prev = south;
            }
            if (visited[y+1][x][south][new_pos.steps] >= pos.dist+grid[y+1][x])
            {
                visited[y+1][x][south][new_pos.steps] = pos.dist+grid[y+1][x];
                search.push(new_pos);
            }
        }

    } while (true);

    /*for (size_t y {}; y < grid.size(); y++)
    {
        for (size_t x {}; x < grid[y].size(); x++)
        {
            if (std::count(new_pos.path.begin(), new_pos.path.end(), std::pair<int, int>{x, y}) > 0 )
            {
                std::cout << "X";
            } else
            {
                std::cout << "-";
            }
        }
        std::cout << std::endl;
    }*/

   std::cout << "\npart 1: " << part1_sum << std::endl;

    return 0;
}