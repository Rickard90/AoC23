#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

void trim_extra_dots(std::string& s) 
{
    char prev {' '};
    std::string s_copy;
    for (size_t i {}; i < s.size(); i++)
    {
        if (!(s[i] == '.' && prev == '.')) {
            s_copy.push_back(s[i]);
        }
        prev = s[i];
    }
    s = s_copy;
}

bool possible_split(std::string springs, int length) 
{
    int max_possible_length {};
    int min_possible_length {};

    //make '?' that are between '#' into '#'
    int first {-1};
    int last {-1};
    for (size_t i {}; i < springs.size(); i++)
    {
        if (springs[i] == '#') {
            first = i;
            break;
        }
    }
    for (int i {static_cast<int>(springs.size()-1)}; i >= 0; i--)
    {
        if (springs[i] == '#') {
            last = i;
            break;
        }
    }

    if (first != -1 && last != -1) { //if '#'
        for (int i {first}; i <= last; i++) {
            if (springs[i] == '.')
                return false;
            springs[i] = '#';
        }
        min_possible_length = last-first + 1;
        max_possible_length = min_possible_length;
        for (int i {first}; i >= 0 && springs[i] != '.'; i--) {
            if (springs[i] == '?')
                max_possible_length++;
        }
        for (int i {last}; i < static_cast<int>(springs.size()) && springs[i] != '.'; i++) {
            if (springs[i] == '?')
                max_possible_length++;
        }
    } else //no '#':
    {
        
        for (int i {1}; i <= static_cast<int>(springs.size()); i++)
        {
            std::string search (i, '?');
            if (springs.find(search) != std::string::npos)
            {
                max_possible_length = i;
            } else {
                break;
            }
        }
    }
    if (length <= max_possible_length && length >= min_possible_length) {
        std::cout << "possible" << std::endl;
        return true;
    }
    std::cout << "impossible" << std::endl;
    return false;
}

int count_possible(std::string springs, std::vector<int> values)
{
    //std::cout << "count_possible string: " << springs << std::endl;

    int sum {};
    for (int i {1}; i < static_cast<int>(springs.size()); i++) 
    {
        /*if (springs[i] == '.' || springs[i] == '?') {
            std::cout << "      string to possible_split: " << springs.substr(0, i) << " value " << values.front() << std::endl;
            std::cout << "         rest is: " << springs.substr(i+1) << std::endl;
        }*/
        if (springs[i] != '#') {
            std::string test = springs.substr(0, i);
            std::string rest = springs.substr(i);
            if (test[i-1] != '.') 
            {
                if (rest[0] != '.') 
                    test.at(i-1) = '.';
                std::cout << "\ntest:" << std::endl;
                std::cout << test << std::endl;
                std::cout << "rest:" << std::endl;
                std::cout << rest << std::endl;
                std::cout << "values.size():" << values.size() << std::endl;
                if (possible_split(test, values.front())) 
                {
                    if (static_cast<int>(springs.size()) > i+1 && values.size() > 2 ) {
                        std::vector<int> value_copy {};
                        //std::cout << 1 << std::endl;
                        std::copy(values.begin()+1, values.end(), std::back_inserter(value_copy));
                        std::cout << "calling possible_split med " << rest << " " << value_copy.size() << std::endl;
                        sum += count_possible(rest, value_copy);
                    } else {
                        if (static_cast<int>(springs.size()) > i+1 && possible_split(rest, values[1]))
                        {
                            std::cout << "sum++ string is " << springs << std::endl;
                            sum++;
                        }
                        
                    }
                }
            }
        }
    }
    //##.
    //012 i
    //123
    return sum;
}


int main() {
    std::string line;
    int sum {};
    std::stringstream ss {};
    
    while (std::getline(std::cin, line)) 
    {
        std::string springs = line.substr(0, line.find(' '));
        springs += '.';
        trim_extra_dots(springs);
        //std::cout << springs << std::endl;
        ss.str(line.substr(line.find(' ')));
        std::vector<int> values {};
        int val {};
        while (ss >> val)
        {
            char c{};
            ss >> c;
            values.push_back(val);
            //std::cout << val << " ";
        }
        //std::cout << std::endl;
        ss.str("");
        ss.clear();
        std::cout << "line sum: \n" << count_possible(springs, values) << std::endl;
    }

    std::cout << "total sum: "<< sum << std::endl;



    return 0;
}