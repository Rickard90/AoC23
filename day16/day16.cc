#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>


enum direction {
    north, east, south, west
};

struct Tile {
    char c {};
    bool energized {};
    std::vector<direction> dir {};
};

struct Pos {
    size_t x {};
    size_t y {};
};


int sim_beams(std::vector<std::vector<Tile>>& grid, size_t start_x, size_t start_y, direction dir)
{
    std::queue<std::pair<Pos, direction>> beams {};
    beams.push(std::pair<Pos, direction> {{start_x, start_y}, dir});
    grid[start_y][start_x].energized = true;
    grid[start_y][start_x].dir.push_back(dir);

    while (!beams.empty())
    {
        std::pair<Pos, direction> beam = beams.front();
        beams.pop();
        size_t& y = beam.first.y;
        size_t& x = beam.first.x;

        if (std::count(grid[y][x].dir.begin(), grid[y][x].dir.end(), beam.second) <= 1)
        {
            grid[y][x].energized = true;
            if (beam.second == north)
            {
                grid[y][x].dir.push_back(north);

                if (grid[y][x].c == '.')
                {
                    if (y > 0)
                    {
                        y--;
                        beams.push(beam);
                    }
                }
                else if (grid[y][x].c == '-')
                {
                    grid[y][x].energized = true;
                    if (x > 0)
                    {
                        beams.push(std::pair<Pos, direction> {{x-1, y}, west});
                    }
                    if (x < grid[y].size()-1)
                    {
                        beams.push(std::pair<Pos, direction> {{x+1, y}, east});
                    }  
                }
                else if (grid[y][x].c == '\\')
                {
                    grid[y][x].energized = true;
                    if (x > 0)
                    {
                        beams.push(std::pair<Pos, direction> {{x-1, y}, west});
                    }
                }
                else if (grid[y][x].c == '/')
                {
                    grid[y][x].energized = true;
                    if (x < grid[y].size()-1)
                    {
                        beams.push(std::pair<Pos, direction> {{x+1, y}, east});
                    }
                }
                else if (grid[y][x].c == '|')
                {
                    if (y > 0)
                    {
                        y--;
                        beams.push(beam);
                    }   
                }
            }
            else if (beam.second == east)
            {
                grid[y][x].dir.push_back(east);

                if (grid[y][x].c == '.')
                {
                    if (x < grid[y].size()-1)
                    {
                        x++;
                        beams.push(beam);
                    }
                }
                else if (grid[y][x].c == '-')
                {
                    if (x < grid[y].size()-1)
                    {
                        x++;
                        beams.push(beam);
                    }
                }
                else if (grid[y][x].c == '\\')
                {
                    grid[y][x].energized = true;
                    if (y < grid.size()-1)
                    {
                        beams.push(std::pair<Pos, direction> {{x, y+1}, south});
                    }
                }
                else if (grid[y][x].c == '/')
                {
                    grid[y][x].energized = true;
                    if (y > 0)
                    {
                        beams.push(std::pair<Pos, direction> {{x, y-1}, north});
                    }
                }
                else if (grid[y][x].c == '|')
                {
                    grid[y][x].energized = true;
                    if (y < grid.size()-1)
                    {
                        beams.push(std::pair<Pos, direction> {{x, y+1}, south});
                    }
                    if (y > 0)
                    {
                        beams.push(std::pair<Pos, direction> {{x, y-1}, north});
                    }     
                }
            }
            else if (beam.second == south)
            {
                grid[y][x].dir.push_back(south);

                if (grid[y][x].c == '.')
                {
                    if (y < grid.size()-1)
                    {
                        y++;
                        beams.push(beam);
                    }   
                }
                else if (grid[y][x].c == '-')
                {
                    grid[y][x].energized = true;
                    if (x > 0)
                    {
                        beams.push(std::pair<Pos, direction> {{x-1, y}, west});
                    }
                    if (x < grid[y].size()-1)
                    {
                        beams.push(std::pair<Pos, direction> {{x+1, y}, east});
                    }  
                }
                else if (grid[y][x].c == '\\')
                {
                    grid[y][x].energized = true;
                    if (x < grid[y].size()-1)
                    {
                        beams.push(std::pair<Pos, direction> {{x+1, y}, east});
                    }
                }
                else if (grid[y][x].c == '/')
                {
                    grid[y][x].energized = true;
                    if (x > 0)
                    {
                        beams.push(std::pair<Pos, direction> {{x-1, y}, west});
                    }
                }
                else if (grid[y][x].c == '|')
                {
                    if (y < grid.size()-1)
                    {
                        y++;
                        beams.push(beam); 
                    }
                }
            }
            else //west
            {
                grid[y][x].dir.push_back(west);

                if (grid[y][x].c == '.')
                {
                    if (x > 0)
                    {
                        x--;
                        beams.push(beam);
                    }
                }
                else if (grid[y][x].c == '-')
                {
                    if (x > 0)
                    {
                        x--;
                        beams.push(beam);
                    }
                }
                else if (grid[y][x].c == '\\')
                {
                    grid[y][x].energized = true;
                    if (y > 0)
                    {
                        beams.push(std::pair<Pos, direction> {{x, y-1}, north});
                    }
                }
                else if (grid[y][x].c == '/')
                {
                    grid[y][x].energized = true;
                    if (y < grid.size()-1)
                    {
                        beams.push(std::pair<Pos, direction> {{x, y+1}, south});
                    }
                }
                else if (grid[y][x].c == '|')
                {
                    grid[y][x].energized = true;
                    if (y < grid.size()-1)
                    {
                        beams.push(std::pair<Pos, direction> {{x, y+1}, south});
                    }
                    if (y > 0)
                    {
                        beams.push(std::pair<Pos, direction> {{x, y-1}, north});
                    }     
                }
            }
        }
    }
    
    int sum {};
    for (std::vector<Tile>& v : grid)
    {
        for (Tile& t : v)
        {
            sum += t.energized?1:0;
            t.energized = false;
            t.dir.clear();
        }
    }

    return sum;
}

int main() {
    std::string line {};
    int part1_sum {};
    std::vector<std::vector<Tile>> grid {};
    
    while (std::getline(std::cin, line)) 
    {
        grid.push_back({});
        for (size_t x = 0; x < line.length(); x++)
        {
            if (line[x] == '.' || line[x] == '|'  || line[x] == '-' || line[x] == '/' || line[x] == '\\')
                grid.back().push_back(Tile {line[x], false, {}});
        }
    }
    
    int best {};

    for (size_t x {}; x < grid[0].size(); x++)
    {
        best = std::max(sim_beams(grid, x, 0, south), best);
        best = std::max(sim_beams(grid, x, grid.size()-1, north), best);
    }
    for (size_t y {}; y < grid.size(); y++)
    {
        best = std::max(sim_beams(grid, 0, y, east), best);
        best = std::max(sim_beams(grid, grid[y].size()-1, y, west), best);
    }


   std::cout << "\npart 1: " << sim_beams(grid, 0, 0, east) << std::endl;
   std::cout << "\npart 2 : " << best << std::endl;

    return 0;
}