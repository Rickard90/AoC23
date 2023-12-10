#include <iostream>
#include <vector>
#include <string>

struct Pos {
    char dir = '.';
    int distance = -1;
};


void set_char(char c, std::pair<int, int> pos, std::vector<std::vector<Pos>>& grid)
{
    if (grid[pos.first][pos.second].dir == '.') {
        grid[pos.first][pos.second].dir = c;
        if (pos.first+1 < static_cast<int>(grid.size()))
            set_char(c, std::pair<int, int> {pos.first+1, pos.second}, grid);
        if (pos.first > 0)
            set_char(c, std::pair<int, int> {pos.first-1, pos.second}, grid);
        if (pos.second+1 < static_cast<int>(grid[0].size()))
            set_char(c, std::pair<int, int> {pos.first, pos.second+1}, grid);
        if (pos.second > 0)
            set_char(c, std::pair<int, int> {pos.first, pos.second-1}, grid);
    }

}

void next(std::pair<int, int>& from, std::vector<std::vector<Pos>>& grid) 
{
    int size_x = static_cast<int>(grid[0].size())-1;
    int size_y = static_cast<int>(grid.size())-1;

    if (grid[from.first][from.second].dir == '|') {
        if (from.first > 0 && grid[from.first-1][from.second].distance == -1) {
            if (from.second < size_x && grid[from.first][from.second+1].dir == '.') 
            {
                set_char('@', std::pair<int,int>{from.first,from.second+1}, grid);
            }
            from.first--;
        } 
        else if (from.first < size_x && grid[from.first+1][from.second].distance == -1) {
            if (from.second > 0 && grid[from.first][from.second-1].dir == '.') {
                set_char('@', std::pair<int,int>{from.first,from.second-1}, grid);
            }
            from.first++;
        }
    }
    else if (grid[from.first][from.second].dir == 'J') {
        if (from.first > 0 && grid[from.first-1][from.second].distance == -1) {
            if (from.second < size_x && grid[from.first][from.second+1].dir == '.') 
            {
                set_char('@', std::pair<int,int>{from.first,from.second+1}, grid);
            }
            if (from.first < size_y && grid[from.first+1][from.second].dir == '.') 
            {
                set_char('@', std::pair<int,int>{from.first+1,from.second}, grid);
            }
            from.first--;
        }
        else if (from.second > 0 && grid[from.first][from.second-1].distance == -1) {
            from.second--;
        }
    }
    else if (grid[from.first][from.second].dir == 'L') {
        if (from.first > 0 && grid[from.first-1][from.second].distance == -1) {
            from.first--;
        }
        else if (grid[from.first][from.second+1].distance == -1) {
            if (from.second > 0 && grid[from.first][from.second-1].dir == '.') 
            {
                set_char('@', std::pair<int,int>{from.first,from.second-1}, grid);
            }
            if (from.first < size_x && grid[from.first+1][from.second].dir == '.') 
            {
                set_char('@', std::pair<int,int>{from.first+1,from.second}, grid);
            }
            from.second++;
        }
    }
    else if (grid[from.first][from.second].dir == '-') {
        if (grid[from.first][from.second-1].distance == -1) {
            if (from.first > 0 && grid[from.first-1][from.second].dir == '.') 
            {
                set_char('@', std::pair<int,int>{from.first-1,from.second}, grid);
            }
            from.second--;
        }
        else if (grid[from.first][from.second+1].distance == -1) {
            if (from.first < size_y && grid[from.first+1][from.second].dir == '.') 
            {
                set_char('@', std::pair<int,int>{from.first+1,from.second}, grid);
            }
            from.second++;
        }
    }
    else if (grid[from.first][from.second].dir == '7') {
        if (grid[from.first][from.second-1].distance == -1) {
            if (from.first > 0 && grid[from.first-1][from.second].dir == '.') 
            {
                set_char('@', std::pair<int,int>{from.first-1,from.second}, grid);
            }
            if (from.second < size_x && grid[from.first][from.second+1].dir == '.') 
            {
                set_char('@', std::pair<int,int>{from.first,from.second+1}, grid);
            }
            from.second--;
        }
        else if (grid[from.first+1][from.second].distance == -1) {
            from.first++;
        }
        
    }
    else if (grid[from.first][from.second].dir == 'F') {
        if (from.second < size_x && grid[from.first][from.second+1].distance == -1) {
            if (from.first < size_y && from.second < size_x && grid[from.first+1][from.second+1].dir == '.') 
            {
                grid[from.first+1][from.second+1].dir = '@';
            }
            from.second++;
        }
        else if (grid[from.first+1][from.second].distance == -1) {
            if (from.first > 0 && grid[from.first-1][from.second].dir == '.') 
            {
                grid[from.first-1][from.second].dir = '@';
            }
            if (from.second > 0 && grid[from.first][from.second-1].dir == '.') 
            {
                grid[from.first][from.second-1].dir = '@';
            }
            from.first++;
        }
    }
}

void set_start_pos(std::pair<int, int> const& start_pos, std::pair<int, int>& pos1,
                   std::vector<std::vector<Pos>>& grid)
{
    bool north {}, east {}, south {}, west {};
    if (grid[start_pos.first-1][start_pos.second].dir == '7' ||
        grid[start_pos.first-1][start_pos.second].dir == '|' ||
        grid[start_pos.first-1][start_pos.second].dir == 'F') 
    {
        north = true;
    };
    if (grid[start_pos.first+1][start_pos.second].dir == 'J' ||
        grid[start_pos.first+1][start_pos.second].dir == 'L' ||
        grid[start_pos.first+1][start_pos.second].dir == '|') 
    {
        south = true;
    };
    if (grid[start_pos.first][start_pos.second-1].dir == '-' ||
        grid[start_pos.first][start_pos.second-1].dir == 'L' ||
        grid[start_pos.first][start_pos.second-1].dir == 'F') 
    {
        west = true;
    };
    if (grid[start_pos.first][start_pos.second+1].dir == '7' ||
        grid[start_pos.first][start_pos.second+1].dir == 'J' ||
        grid[start_pos.first][start_pos.second+1].dir == '-') 
    {
        east = true;
    };

    if (north && south) {
        grid[start_pos.first][start_pos.second].dir = '|';
        pos1 = start_pos;
        pos1.first--;
    }
    else if (north && east) {
        grid[start_pos.first][start_pos.second].dir = 'L';
        pos1 = start_pos;
        pos1.first--;
    }
    else if (north && west) {
        grid[start_pos.first][start_pos.second].dir = 'J';
        pos1 = start_pos;
        pos1.first--;
    }
    else if (east && west) {
        grid[start_pos.first][start_pos.second].dir = '-';
        pos1 = start_pos;
        pos1.second--;
    }
    else if (east && south) {
        grid[start_pos.first][start_pos.second].dir = 'F';
        pos1 = start_pos;
        pos1.first++;
    }
    else if (west && south) {
        grid[start_pos.first][start_pos.second].dir = '7';
        pos1 = start_pos;
        pos1.second--;
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
            if (line[x] == 'S')
                start_pos = {y, x};
            grid.back().push_back(Pos {line[x]});
        }
        y++;
    }

    grid[start_pos.first][start_pos.second].distance = 0;
    std::pair<int, int> pos1;
    set_start_pos(start_pos, pos1, grid);

    //find loop
    int distance {};
    while (grid[pos1.first][pos1.second].distance == -1)
    {
        if (grid[pos1.first][pos1.second].distance == -1) {
            grid[pos1.first][pos1.second].distance = ++distance;
            next(pos1, grid);
        }
    }
    std::cout << "Answer Part1 : " << (distance/2)+1 << std::endl;

    //remove irrelevant pipes
    for (size_t y {}; y < grid.size(); y++)
    {
        for (size_t x {}; x < grid[y].size(); x++)
        {
            if (grid[y][x].distance == -1) {
                grid[y][x].dir = '.';
            } else {
                grid[y][x].distance = -1;
            }
        }
    }
    
    distance = 0;
    grid[start_pos.first][start_pos.second].distance = 0;
    set_start_pos(start_pos, pos1, grid);
    while (grid[pos1.first][pos1.second].distance == -1)
    {
        if (grid[pos1.first][pos1.second].distance == -1) {
            grid[pos1.first][pos1.second].distance = ++distance;
            next(pos1, grid);
        }
    }

    int sum {};
    for (size_t y {}; y < grid.size(); y++)
    {
        for (size_t x {}; x < grid[y].size(); x++)
        {
            std::cout << grid[y][x].dir;
            if (grid[y][x].dir == '@')
                sum++;
        }
        std::cout << std::endl;
    }
    std::cout << sum << std::endl;

    return 0;
}