#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <sstream>


struct Block {
    size_t x1 {};
    size_t y1 {};
    size_t z1 {};
    size_t x2 {};
    size_t y2 {};
    size_t z2 {};
    std::set<int> resting_on {};
};

void fill(std::vector<std::vector<std::vector<int>>>& grid, Block const& block, int value) 
{
    for (size_t z = block.z1; z <= block.z2; z++)
        for (size_t y = block.y1; y <= block.y2; y++)
            for (size_t x = block.x1; x <= block.x2; x++)
                grid[z][y][x] = value;
}


bool drop_one(std::vector<std::vector<std::vector<int>>>& grid, std::vector<Block>& blocks, int const block_nr)
{
    Block& block = blocks[block_nr];
    block.resting_on.clear();
    fill(grid, block, -1);
    size_t z {};
    for (z = std::min(block.z1, block.z2); z > 1; z--)
    {
        for (size_t y = block.y1; y <= block.y2; y++)
        {
            for (size_t x = block.x1; x <= block.x2; x++)
            {
                int under = grid[z-1][y][x];
                if (under != -1)
                    block.resting_on.insert(under);
            }
        }
        if (!block.resting_on.empty())
            break;
    }
    int change = std::min(block.z1, block.z2) - z;
    block.z1 -= change;
    block.z2 -= change;

    fill(grid, block, block_nr);
    return change != 0;
}


int simulate(std::vector<std::vector<std::vector<int>>>& grid, std::vector<Block>& blocks)
{
    int ret {};
    for (size_t z {}; z < grid.size(); z++)
    {
        for (size_t y {}; y < 10; y++)
        {
            for (size_t x {}; x < 10; x++)
            {
                int block_nr = grid[z][y][x];
                if (block_nr != -1)
                    ret += drop_one(grid, blocks, block_nr);
            }
        }
    }
    return ret;
}


int disintegrate(std::vector<std::vector<std::vector<int>>> grid, std::vector<Block> blocks, int const block_nr)
{
    fill(grid, blocks[block_nr], -1);
    return simulate(grid, blocks);
}

int main() {
    std::string line;
    std::stringstream ss {};
    std::vector<std::vector<std::vector<int>>> grid {}; //z, y, x
    std::vector<Block> blocks {};
    
    int block_nr = 0;
    while (std::getline(std::cin, line)) 
    {
        ss << line;
        Block block {};
        char c {};
        ss >> block.x1 >> c >> block.y1 >> c  >> block.z1 >> c ;
        ss >> block.x2 >> c  >> block.y2 >> c  >> block.z2;
        blocks.push_back(block);

        std::vector<std::vector<int>> layer (10, std::vector<int> (10, -1));
        if (std::max(block.z1, block.z2) > grid.size())
            grid.resize(std::max(block.z1, block.z2)+1, layer);

        for (size_t z = block.z1; z <= block.z2; z++)
            for (size_t y = block.y1; y <= block.y2; y++)
                for (size_t x = block.x1; x <= block.x2; x++)
                    grid[z][y][x] = block_nr;
        
        block_nr++;

        ss.str("");
        ss.clear();
    }

    simulate(grid, blocks);
    
    std::set<int> important {};
    for (Block const& b : blocks)
    {
        if (b.resting_on.size() == 1)
        {
            for (int i : b.resting_on)
                important.insert(i);
        }
    }
    int part1 = blocks.size() - important.size();

    int part2 {};
    for (size_t block {}; block < blocks.size(); block++)
    {
        part2 += disintegrate(grid, blocks, block);
    }

    std::cout << "Part 1 Sum: " << part1 << std::endl;
    std::cout << "Part 2 Sum: " << part2 << std::endl;

    return 0;
}