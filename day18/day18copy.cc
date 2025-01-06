#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>

//works for clockwise tests: test1 and test2

struct Pos {
    int x {};
    int y {};
};

int dir_last {};
int dir_prev {};

Pos next_pos(Pos prev, char dir, int steps)
{
    dir_prev = dir_last;
    Pos ret {prev};   
    if (dir == 'U')
    {
        dir_last = 3;
        ret.y-=steps;
    } else if (dir == 'D')
    {
        dir_last = 1;
        ret.y+=steps;
    } else if (dir == 'L')
    {
        dir_last = 2;
        ret.x-=steps;
    } else if (dir == 'R')
    {
        dir_last = 0;
        ret.x+=steps;
    }
    return ret;
}


int main() {
    std::string line;
    std::stringstream ss {};
    int sum {};
    std::vector<std::pair<Pos, Pos>> vertical {};
    std::set<int> horizontal {};


    Pos pos {};
    Pos new_pos {};
    std::pair<Pos, Pos> vert_line {};
    horizontal.insert(pos.y);
    while (std::getline(std::cin, line)) 
    {
        pos = new_pos;
        ss.str(line);
        if (line.size() > 2) 
        {
            std::pair<char, int> dir_steps {};
            ss >> dir_steps.first >> dir_steps.second;
            new_pos = next_pos(pos, dir_steps.first, dir_steps.second);
            //horizontal.insert(new_pos.y);
            if (new_pos.y > pos.y)
            {//ner
                if (dir_prev == 0) //höger
                {
                    vert_line = {pos, new_pos};
                }
                else if (dir_prev == 2) //vänster
                {
                    vert_line = {{pos.x, pos.y+1}, new_pos};
                }
            }
            else if (new_pos.y < pos.y)
            { //upp
                if (dir_prev == 0) //höger
                {
                    vert_line = {new_pos, {pos.x, pos.y-1}};
                }
                else if (dir_prev == 2) //vänster
                {
                    vert_line = {new_pos, pos};
                }
            }
            else if (new_pos.x > pos.x)
            {//höger
                if (dir_prev == 1) 
                {  //down
                    vert_line.second.y--;
                    vertical.push_back(vert_line);
                }
                else if (dir_prev == 3) 
                { //upp
                    vertical.push_back(vert_line);
                }
            }
            else if (new_pos.x < pos.x)
            {//vänster
                if (dir_prev == 1) 
                {  //down
                    vertical.push_back(vert_line);
                }
                else if (dir_prev == 3) 
                { //upp
                    vert_line.first.y++;
                    vertical.push_back(vert_line);
                }
            }
            

        }
        ss.str("");
        ss.clear();
    }
    vertical.push_back(vert_line);

    std::sort(vertical.begin(), vertical.end(), [](std::pair<Pos, Pos> const& a, std::pair<Pos, Pos> const& b)
    {return a.first.x < b.first.x;});

    for (auto line : vertical)
    {
        horizontal.insert(line.first.y);
        horizontal.insert(line.second.y+1);
    }
    horizontal.insert(vertical.back().second.y+1);

    int range_start {-1};
    for (int i : horizontal)
    {
        if (range_start == -1)
        {
            range_start = 0;
        }
        else 
        {
            int heigth = i - range_start;
            int width {};
            int start_inside {};
            bool inside = false;

            for (auto line : vertical) {
                if (line.first.y <= range_start && range_start <= line.second.y)
                {
                    std::cout << "    crossing line: " << line.first.x << std::endl;
                    if (!inside)
                    {
                        inside = true;
                        start_inside = line.first.x;
                    }
                    else
                    {
                        inside = false;
                        width += line.first.x - start_inside + 1;
                        std::cout << "      width: " << width << std::endl;
                    }

                }
            }
            std::cout << "      heigth: " << heigth << " width*heith=" << width*heigth << std::endl;


            sum += heigth * width;
        }
        std::cout << "i: " << i << std::endl;
        range_start = i;
    }



    for (auto line : vertical)
    {
        std::cout << line.first.x << ":" << line.first.y << " - " << line.second.x << ":" << line.second.y << std::endl;
    }


    std::cout << "total sum: " << sum << std::endl;

    return 0;
}


/*
#####.....
#...#.###.
#...#.#.#.
#...###.#.
#.......#.
####..###.
...#..#...
...####...*/