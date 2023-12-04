#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>


int main() {
    std::string line;
    std::stringstream ss;
    
    int sum {};

    while (std::getline(std::cin, line)) //each card
    {
        std::vector<int> winning_nr {}, your_nr {};
        std::string p1, p2; 

        p1 = line.substr(line.find(':')+1, line.find('|'));
        p2 = line.substr(line.find('|')+1);
        
        int value;
        ss.str(p1);
        while (ss >> value) 
        {
            winning_nr.push_back(value);
        }

        ss.clear();
        ss.str(p2);
        while (ss >> value) 
        {
            your_nr.push_back(value);
        }

        int card_score {};
        for (int number : your_nr) 
        {
            if (std::find(winning_nr.begin(), winning_nr.end(), number) != winning_nr.end()) {
                card_score = card_score==0?1:card_score*2;
            }
        }
        sum += card_score;
        ss.clear();
    }
    std::cout << sum;
    
    
    return 0;
}