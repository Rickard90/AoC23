#include <iostream>
#include <vector>
#include <string>
#include <sstream>

bool is_done(std::vector<int> const& v)
{
    for (int i : v)
        if (i != 0)
            return false;
    return true;
}

int main() {
    std::string line;
    std::stringstream ss {};
    std::vector<std::vector<std::vector<int>>> sequences {};
    int sum {};

    while (std::getline(std::cin, line)) 
    {
        ss.str(line);
        int val {};
        std::vector<int> numbers {};
        std::vector<std::vector<int>> reading {};
        while (ss >> val) 
        {
            numbers.push_back(val);
        }
        reading.push_back(numbers);
        sequences.push_back(reading);
        ss.str("");
        ss.clear();
    }

    for (int i {0}; i < static_cast<int>(sequences.size()); i++)
    {
        for (int j {0}; !is_done(sequences[i][j]); j++)
        {
            sequences[i].push_back(std::vector<int> {});
            for (int k {1}; k < static_cast<int>(sequences[i][j].size()); k++)
            {
                int dif = sequences[i][j][k] - sequences[i][j][k-1];
                sequences[i][j+1].push_back(dif);
            }
        }
    }

    for (int i {0}; i < static_cast<int>(sequences.size()); i++)
    {
        for (int j {static_cast<int>(sequences[i].size())-1}; j > 0; j--)
        {
            int next_val = sequences[i][j-1].back() + sequences[i][j].back();
            sequences[i][j-1].push_back(next_val);
        }
    }

    for (auto v : sequences)
    {
        sum += v.front().back();
    }

    std::cout << "Sum: " << sum;

    return 0;
}