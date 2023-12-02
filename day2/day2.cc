#include <iostream>
#include <sstream>


int main() {
    std::string line;
    std::stringstream ss;
    int game_nr {};
    int sum1 {}, sum2 {};

    while (std::getline(std::cin, line)) //each game
    {
        game_nr++;
        int red {}, green {}, blue {};
        int next {};

        line = line.substr(line.find(':')+1);

        while (next != -1) //each reveal
        {
            ss.str("");
            next = line.find(';');
            if (next != -1) {
                ss.str(line.substr(0, next));
                line = line.substr(next+1);
            } else {
                ss.str(line);
            }
            int value;
            std::string color;
            while (ss >> value) 
            {
                ss >> color;
                if (color.back() == ',') {
                    color = color.substr(0, color.length()-1);
                }
                std::cout << color << std::endl;
                if (color == "red") {
                    red = std::max(red, value);
                } else if (color == "green") {
                    green = std::max(green, value);
                } else { //"blue"
                    blue = std::max(blue, value);
                }
            }
            ss.clear();
        }

        //part 1:
        if (red <= 12 && green <= 13 && blue <= 14 ) {
            sum1 += game_nr;
        }

        //part 2:
        sum2 += red*green*blue;
    }
    std::cout << "sum for part 1: " << sum1 << std::endl;
    std::cout << "sum for part 2: " << sum2 << std::endl;
    return 0;
}