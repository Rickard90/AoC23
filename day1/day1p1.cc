#include <iostream>
#include <vector>
#include <sstream>


int main() {
    std::string line;
    int sum {};

    while (std::getline(std::cin, line))
    {
        char first_int {}, last_int {};
        for (char c : line)
        {
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