#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>


int main() {
    std::string line;
    std::stringstream ss;
    
    int sum {}, card_number {};
    std::vector<int> nr_of_cards {};

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
                card_score++;
            }
        }

        if (nr_of_cards.size() <= card_number) {
            nr_of_cards.push_back(1);
        }
        for (int i {1}; i <= card_score; i++) 
        {
            if (nr_of_cards.size() <= card_number+i) {
                nr_of_cards.push_back(1);
            }
            nr_of_cards.at(card_number+i) += nr_of_cards.at(card_number);
        }
        
        ss.clear();
        card_number++;
    }
    
    sum = std::accumulate(nr_of_cards.begin(), nr_of_cards.end(), 0);
    
    std::cout << "Sum: " << sum;
    
    return 0;
}