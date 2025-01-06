#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <algorithm>


struct Path {
    size_t x {};
    size_t y {};
    int dist {};
    std::set<std::pair<int, int>> visited {};
};



int main() {
    std::string line {};
    std::vector<std::string> grid {};
    //std::vector<std::vector<bool>> visited {};

    while (std::getline(std::cin, line)) 
    {
        grid.push_back(line);
    }
    

    for (size_t y {}; y < grid.size(); y++)
    {
        for (size_t x {}; x < grid[y].size(); x++)
        {
            if (x == 1 && y == 0)
            {
                std::cout << 'S';
            }
            else if (x == grid.size()-2 && y == grid[grid.size()-1].size()-1)
            {
                std::cout << 'G';
            }
            else
            {
                std::cout << grid[y][x];
            }
        }
        std::cout << std::endl;
    }


    Path path;
    Path new_path {};
    std::vector<Path> data {};
    std::priority_queue search (data.begin(), data.end(), [](Path a, Path b){
        return a.dist > b.dist;
    });

    Path start {1, 0};
    search.push(start);
    Path goal {grid.size()-2, grid[grid.size()-1].size()-1};
    Path longest {};

    int sum {};
    do {
        path = search.top();
        search.pop();
        path.dist++;
        size_t& x = path.x;
        size_t& y = path.y;
        std::cout << path.x << " " << path.y << std::endl;
        
        if ((path.x == goal.x && path.y == goal.y))
        {
            path.visited.insert({x, y});
            longest = path;
        }
        else 
        if (std::count(path.visited.begin(), path.visited.end(), std::pair<int, int>{x, y}) == 0)
        {
            path.visited.insert({x, y});

            if (grid[y][x] == '<')
            {
                new_path = path;
                new_path.x--;
                search.push(new_path);
            }
            else if (grid[y][x] == '>')
            {
                new_path = path;
                new_path.x++;
                search.push(new_path);
            }
            else if (grid[y][x] == '^')
            {
                new_path = path;
                new_path.y--;
                search.push(new_path);
            }
            else if (grid[y][x] == 'v')
            {
                new_path = path;
                new_path.y++;
                search.push(new_path);
            }
            else {
                if ( x > 0 && (grid[y][x-1] != '#' && grid[y][x-1] != '>') )
                {
                    new_path = path;
                    new_path.x--;
                    search.push(new_path);
                }
                if ( x < grid[y].size()-1  && (grid[y][x+1] != '#' && grid[y][x+1] != '<') )
                {
                    new_path = path;
                    new_path.x++;
                    search.push(new_path);
                }
                if ( y > 0  && (grid[y-1][x] != '#' && grid[y-1][x] != 'v') )
                {
                    new_path = path;
                    new_path.y--;
                    search.push(new_path);
                }
                if ( y < grid.size()-1  && (grid[y+1][x] != '#' && grid[y+1][x] != '^') )
                {
                    new_path = path;
                    new_path.y++;
                    search.push(new_path);
                }
            }
        }
    } while (!search.empty());


    for (size_t y {}; y < grid.size(); y++)
    {
        for (size_t x {}; x < grid[y].size(); x++)
        {
            if (std::count(longest.visited.begin(), longest.visited.end(), std::pair<int, int>{x, y}) > 0 )
            {
                std::cout << "+";
            } else
            {
                std::cout << grid[y][x];
            }
        }
        std::cout << std::endl;
    }

    std::cout << "\nSum: " << longest.visited.size()-1 << std::endl;

    return 0;
}