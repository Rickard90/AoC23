#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <numeric>


enum Direction {
    north_south,
    west_east,
    north_east,
    south_east,
    west_north,
    west_south,
    none,
    start
};

struct Pos {
    Direction dir = none;
    int distance = -1;
};

void next(std::pair<int, int>& from, std::vector<std::vector<Pos>> const& grid) 
{
    if (grid[from.first][from.second].dir == north_south) {
        if (grid[from.first-1][from.second].distance == -1) {
            from.first--;
        } 
        else if (grid[from.first+1][from.second].distance == -1) {
            from.first++;
        }
    }
    else if (grid[from.first][from.second].dir == west_north) {
        if (grid[from.first-1][from.second].distance == -1) {
            from.first--;
        }
        else if (grid[from.first][from.second-1].distance == -1) {
            from.second--;
        }
    }
    else if (grid[from.first][from.second].dir == north_east) {
        if (grid[from.first-1][from.second].distance == -1) {
            from.first--;
        }
        else if (grid[from.first][from.second+1].distance == -1) {
            from.second++;
        }
    }
    else if (grid[from.first][from.second].dir == west_east) {
        if (grid[from.first][from.second-1].distance == -1) {
            from.second--;
        }
        else if (grid[from.first][from.second+1].distance == -1) {
            from.second++;
        }
    }
    else if (grid[from.first][from.second].dir == west_south) {
        if (grid[from.first][from.second-1].distance == -1) {
            from.second--;
        }
        else if (grid[from.first+1][from.second].distance == -1) {
            from.first++;
        }
    }
    else if (grid[from.first][from.second].dir == south_east) {
        if (grid[from.first][from.second+1].distance == -1) {
            from.second++;
        }
        else if (grid[from.first+1][from.second].distance == -1) {
            from.first++;
        }
    }
}

void set_start_pos(std::pair<int, int> const& start_pos, std::pair<int, int>& pos1, std::pair<int, int>& pos2,
            bool north, bool east, bool south, bool west, std::vector<std::vector<Pos>>& grid)
{
    if (north && south) {
        grid[start_pos.first][start_pos.second].dir = north_south;
        pos1 = start_pos;
        pos1.first--;
        pos2 = start_pos;
        pos2.first++;
    }
    else if (north && east) {
        grid[start_pos.first][start_pos.second].dir = north_east;
        pos1 = start_pos;
        pos1.first--;
        pos2 = start_pos;
        pos2.second++;
    }
    else if (north && west) {
        grid[start_pos.first][start_pos.second].dir = west_north;
        pos1 = start_pos;
        pos1.first--;
        pos2 = start_pos;
        pos2.second--;
    }
    else if (east && west) {
        grid[start_pos.first][start_pos.second].dir = west_east;
        pos1 = start_pos;
        pos1.second--;
        pos2 = start_pos;
        pos2.second++;
    }
    else if (east && south) {
        grid[start_pos.first][start_pos.second].dir = south_east;
        pos1 = start_pos;
        pos1.first++;
        pos2 = start_pos;
        pos2.second++;
    }
    else if (west && south) {
        grid[start_pos.first][start_pos.second].dir = west_south;
        pos1 = start_pos;
        pos1.second--;
        pos2 = start_pos;
        pos2.first++;
    }
}


int main() {
    std::string line;
    
    std::vector<std::vector<Pos>> grid {};
    std::pair<int, int> start_pos {};
    size_t y {};
    while (std::getline(std::cin, line)) 
    {
        grid.push_back(std::vector<Pos> {});
        for (size_t x = 0; x < line.length(); x++)
        {
            Direction dir {};
            switch (line[x]) {
                case '|':
                    dir = north_south;
                    break;
                case '-':
                    dir = west_east;
                    break;
                case 'L':
                    dir = north_east;
                    break;
                case 'F':
                    dir = south_east;
                    break;
                case 'J':
                    dir = west_north;
                    break;
                case '7':
                    dir = west_south;
                    break;
                case 'S':
                    dir = start;
                    start_pos = {y, x};
                    break;
                default:
                    dir = none;
            }
            grid.back().push_back(Pos {dir});
        }
        y++;
    }

    grid[start_pos.first][start_pos.second].distance = 0;

    std::pair<int, int> pos1;
    std::pair<int, int> pos2;
    {   //Fix start pos
        bool north {}, east {}, south {}, west {};
        if (grid[start_pos.first-1][start_pos.second].dir == west_south ||
            grid[start_pos.first-1][start_pos.second].dir == north_south ||
            grid[start_pos.first-1][start_pos.second].dir == south_east) 
        {
            north = true;
        };
        if (grid[start_pos.first+1][start_pos.second].dir == west_north ||
            grid[start_pos.first+1][start_pos.second].dir == north_east ||
            grid[start_pos.first+1][start_pos.second].dir == north_south) 
        {
            south = true;
        };
        if (grid[start_pos.first][start_pos.second-1].dir == west_east ||
            grid[start_pos.first][start_pos.second-1].dir == north_east ||
            grid[start_pos.first][start_pos.second-1].dir == south_east) 
        {
            west = true;
        };
        if (grid[start_pos.first][start_pos.second+1].dir == west_south ||
            grid[start_pos.first][start_pos.second+1].dir == west_north ||
            grid[start_pos.first][start_pos.second+1].dir == west_east) 
        {
            east = true;
        };

        set_start_pos(start_pos, pos1, pos2, north, east, south, west, grid);
    }

    std::cout << "start pos: " << start_pos.first << ":" << start_pos.second << std::endl;
    std::cout << "pos1: " << pos1.first << ":" << pos1.second << std::endl;
    std::cout << "pos2: " << pos2.first << ":" << pos2.second << std::endl;

    int distance1 {};
    int distance2 {};
    while (grid[pos1.first][pos1.second].distance == -1 || grid[pos2.first][pos2.second].distance == -1)
    {
        std::cout << std::endl;
        if (grid[pos1.first][pos1.second].distance == -1) {
            grid[pos1.first][pos1.second].distance = ++distance1;
            next(pos1, grid);
        }
        if (grid[pos2.first][pos2.second].distance == -1) {
            grid[pos2.first][pos2.second].distance = ++distance2;
            next(pos2, grid);
        }
        std::cout << "pos1: " << pos1.first << ":" << pos1.second << std::endl;
        std::cout << "pos2: " << pos2.first << ":" << pos2.second << std::endl;
        
    }


   std::cout << "Length: " << std::max(distance1, distance2);

    return 0;
}