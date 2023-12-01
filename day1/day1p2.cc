#include <iostream>
#include <string>

std::string words[9] {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char value[] {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

char is_spelled(std::string const& line, size_t pos)
{
    char c {};
    bool possible[9] {true, true, true, true, true, true, true, true, true};
    int possible_count {9};
    for (size_t letter_pos {}; pos+letter_pos < line.length(); letter_pos++)
    {
        for (size_t number {}; number < 9 && possible_count > 0; number++)
        {
            if (possible[number] && letter_pos < words[number].length() && words[number][letter_pos] != line[pos+letter_pos])
            {
                possible[number] = false;
                possible_count--;
            } else if (letter_pos+1 == words[number].length() && possible[number])
            {
                return value[number];
            }
        }
        
    }
    return c;
}

int main() {
    std::string line;
    int sum {};
    while (std::getline(std::cin, line))
    {
        char first_int {}, last_int {};
        for (int i {}; i < static_cast<int>(line.length()); i++)
        {
            char c = is_spelled(line, i);
            if (!isdigit(c)){
                c = line[i];
            }
            if (isdigit(c))
            {
                if (first_int == 0)
                {
                    first_int = c;
                }
                last_int = c;
            }
        }

        std::string value = {first_int, last_int};
        sum += std::stoi(value);
    }
    std::cout << sum;
    return 0;
}