#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <numeric>


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
            return v1<v2;
        }
    }
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
            if (h1[i] == h1[j] && i != j) {
                count1[i]++;
                count1[j]++;
            }
        }   
    }
    int label1 {};
    for (int i {}; i<5; i++)
    {
        unique_counts1.insert(h1[i]);
        label1 = label1 < count1[i]? count1[i]: label1;
    }


    std::set<int> unique_counts2 {};
    int count2[5] {};
    for (int i {}; i < 5; i++)
    {
        for (int j {i+1}; j < 5; j++)
        {
            if (h2[i] == h2[j] && i != j) {
                count2[i]++;
                count2[j]++;
            }
        }   
    }
    int label2 {};
    for (int i {}; i<5; i++)
    {
        unique_counts2.insert(h2[i]);
        label2 = label2 < count2[i]? count2[i]: label2;
    }

    if (label1 >= 3 || label2 >= 3) {
        if (label1 == label2) {
            return compare_first(h1, h2);
        } else {
            return label1 < label2;
        }
    } else if (unique_counts1.size()==2 && unique_counts2.size()!=2) {
        return false;
    } else if (unique_counts1.size()!=2 && unique_counts2.size()==2) {
        return true;
    } else if (unique_counts1.size()==2 && unique_counts2.size()==2) {
        return compare_first(h1, h2);
    } else if (label1 >= 2 || label2 >= 2) {
        if (label1 == label2) {
            return compare_first(h1, h2);
        } else {
            return label1 < label2;
        }
    } else if (unique_counts1.size()==3 && unique_counts2.size()!=3) {
        return false;
    } else if (unique_counts1.size()!=3 && unique_counts2.size()==3) {
        return true;
    } else if (unique_counts1.size()==3 && unique_counts2.size()==3) {
        return compare_first(h1, h2);
    } else {
        if (label1 == label2) {
            return compare_first(h1, h2);
        } else {
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
    card_val['J'] = 210;
    card_val['T'] = 200;

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

    sum = std::accumulate(wins.begin(), wins.end(), 0);

    std::cout << "Sum: " << sum;

    return 0;
}