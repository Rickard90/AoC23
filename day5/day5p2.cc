#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <climits>

struct range {
    long long int begin {}, end {};
};

void update_best(long long int& old_best, long long int possible_new) 
{
    old_best = old_best>possible_new?possible_new:old_best;
}

int main() {
    std::string line;
    std::stringstream ss {};
    std::queue<range> unconverted {};
    long long int best {LLONG_MAX};

    std::getline(std::cin, line);
    ss.str(line.substr(line.find(':')+1));

    //read ranges
    long long int begin {}, length {};
    while (ss >> begin)
    {
        ss >> length;
        unconverted.push(range{begin, begin+length});
    }
    ss.str("");
    ss.clear();

    while (std::getline(std::cin, line))
    {
        std::vector<std::pair<range, long long int>> convesion_range {};
        if (isdigit(line[0])) {
            do {
                if (!isdigit(line[0])) {
                    break;
                } else {
                    long long int dest {};
                    long long int source {};
                    long long int amount {};

                    ss.str(line);
                    ss >> dest >> source >> amount;
                    long long int offset = dest-source;
                    convesion_range.push_back(std::pair<range, long long int>{range {source, source+amount}, offset});
                    ss.str("");
                    ss.clear();
                }
            } while (std::getline(std::cin, line));
            convesion_range.push_back(std::pair<range, long long int>{range {0, LLONG_MAX}, 0});
            
            std::queue<range> converted {};
            while (!unconverted.empty()) {
                range r1 = unconverted.front();
                unconverted.pop();
                for (auto r2 : convesion_range) 
                {
                    if (r1.begin >= r2.first.end || r1.end <= r2.first.begin) {
                        continue;
                    } else if (r1.begin >= r2.first.begin && r1.end <= r2.first.end) {
                        //r1 inside r2 -> convert all
                        converted.push(range {r1.begin+r2.second, r1.end+r2.second});
                        break;
                    } else if (r1.begin < r2.first.end && r1.begin >= r2.first.begin && r1.end > r2.first.end) {
                        //1 part of r1 inside r2 and one part outside -> convert some, leave rest
                        converted.push(range {r1.begin+r2.second, r2.first.end+r2.second});
                        r1.begin = r2.first.end;
                    } else if (r1.end > r2.first.begin && r1.end <= r2.first.end && r1.begin < r2.first.begin) {
                        //1 part of r1 inside r2 and one part outside -> convert some, leave rest
                        converted.push(range {r2.first.begin+r2.second, r1.end+r2.second});
                        r1.end = r2.first.begin;
                    } else {
                        //split into 3 parts, convert middle add the other to parts as new unconverted ranges
                        converted.push(range {r2.first.begin+r2.second, r2.first.end+r2.second});
                        unconverted.push(range {r2.first.end, r1.end});
                        r1.end = r2.first.begin;
                    }


                }
            }
            unconverted = converted;
        }
    }

    while (!unconverted.empty()) {
        update_best(best, unconverted.front().begin);
        unconverted.pop();
    }

    std::cout << "Answer: "<< best << std::endl;



    
    return 0;
}