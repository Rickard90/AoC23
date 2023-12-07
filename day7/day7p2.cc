#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>


std::map<char, int> card_val {};


bool compare_first(std::string const& h1, std::string const& h2)
{
    
    for (int i {}; i < 5; i++)
    {
        int v1 {}, v2 {};
        if (isdigit(h1[i])) {
            v1 = h1[i];
        } else {
            v1 = card_val[h1[i]];
        }
        if (isdigit(h2[i])) {
            v2 = h2[i];
        } else {
            v2 = card_val[h2[i]];
        }
        if (v1 != v2) {
            if (v1<v2) {
                //std::cout << 31 << std::endl;
            } else {
                //std::cout << 30 << std::endl;
            }
            return v1<v2;
        }
    }
    std::cout << "same?" << std::endl;
    return false;
}


bool compare(std::string const& h1, std::string const& h2)
{
    std::set<char> unique_counts1 {};
    int count1[5] {};
    for (int i {}; i < 5; i++)
    {
        for (int j {i+1}; j < 5; j++)
        {
            if (h1[i] == h1[j] && h1[i] != 'J' && h1[j] == 'J' && i != j) {
                count1[i]++;
                count1[j]++;
            }
            if (h1[i] == 'J') {
                count1[j]++;
            }
            if (h1[j] == 'J') {
                count1[i]++;
            }
        }   
    }
    int label1 {};
    for (int i {}; i<5; i++)
    {
        if (h1[i] != 'J') {
            unique_counts1.insert(h1[i]);
            label1 = label1 < count1[i]? count1[i]: label1;
        }
    }


    std::set<int> unique_counts2 {};
    int count2[5] {};
    for (int i {}; i < 5; i++)
    {
        for (int j {i+1}; j < 5; j++)
        {
            if (h2[i] == h2[j] && h2[i] != 'J' && h2[j] == 'J' && i != j) {
                count2[i]++;
                count2[j]++;
            }
            if (h2[i] == 'J') {
                count2[j]++;
            }
            if (h2[j] == 'J') {
                count2[i]++;
            }
        }   
    }
    int label2 {};
    for (int i {}; i<5; i++)
    {
        if (h2[i] != 'J') {
            unique_counts2.insert(h2[i]);
            label2 = label2 < count2[i]? count2[i]: label2;
        }
    }

    std::cout << h1 << " label " << label1+1 << " counts: " << unique_counts1.size() << std::endl;
    std::cout << h2 << " label " << label2+1 << " counts: " << unique_counts2.size() << std::endl;

    if (label1 >= 3 || label2 >= 3) {
        if (label1 == label2) {
            return compare_first(h1, h2);
        } else {
            //std::cout << "<" << std::endl;
            return label1 < label2;
        }
    } else if (unique_counts1.size()==2 && unique_counts2.size()!=2) {
        //std::cout << 10 << std::endl;
        return false;
    } else if (unique_counts1.size()!=2 && unique_counts2.size()==2) {
        //std::cout << 11 << std::endl;
        return true;
    } else if (unique_counts1.size()==2 && unique_counts2.size()==2) {
        return compare_first(h1, h2);
    } else if (label1 >= 2 || label2 >= 2) {
        if (label1 == label2) {
            return compare_first(h1, h2);
        } else {
            //std::cout << "<" << std::endl;
            return label1 < label2;
        }
    } else if (unique_counts1.size()==3 && unique_counts2.size()!=3) {
        //std::cout << 20 << std::endl;
        return false;
    } else if (unique_counts1.size()!=3 && unique_counts2.size()==3) {
        //std::cout << 21 << std::endl;
        return true;
    } else if (unique_counts1.size()==3 && unique_counts2.size()==3) {
        return compare_first(h1, h2);
    } else {
        //std::cout << "<" << std::endl;
        if (label1 == label2) {
            return compare_first(h1, h2);
        } else {
            //std::cout << "<" << std::endl;
            return label1 < label2;
        }
    }
}

int main() {
    std::string line;
    std::stringstream ss {};
    std::vector<std::string> hands {};
    std::vector<long long int> wins {};
    std::vector<long long int> bids {};
    long long int sum {};

    while (std::getline(std::cin, line)) 
    {
        ss.str(line);
        std::string hand {};
        long long int bid {};
        ss >> hand >> bid;
        hands.push_back(hand);
        bids.push_back(bid);
        wins.push_back(bid);
        ss.str("");
        ss.clear();
    }

    card_val['A'] = 240;
    card_val['K'] = 230;
    card_val['Q'] = 220;
    card_val['J'] = 0;
    card_val['T'] = 200;

    //std::cout << "test1 " << (compare("QQQJA", "32T3K")? "true":"false") << std::endl;
    //std::cout << "test1 " << std::endl << (compare("T55J5", "KTJJT")? "true":"false") << std::endl;

    for (size_t i {}; i < hands.size(); i++)
    {
        for (size_t j {i+1}; j < hands.size(); j++)
        {
            if (i != j) {
                if (compare(hands[i], hands[j])) {
                    wins[j]+=bids[j];
                } else {
                    wins[i]+=bids[i];
                }
            }
        }   
    }

    for (long long int v : wins)
    {
        sum+= v;
    }





    std::cout << "Sum: " << sum;

    return 0;
}