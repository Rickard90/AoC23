#include <iostream>
#include <vector>
#include <map>
#include <map>
#include <string>


int get_hash(std::string const& word)
{
    int value {};
    for (size_t i {}; i<word.size(); i++)
    {
        value += word[i];
        value *= 17;
        value = value%256;
    }
    return value;
}


void add(std::vector<std::pair<int, std::pair<std::string, int>>>& box, std::string name, int value, int index)
{
    bool found = false;
    for (std::pair<int, std::pair<std::string, int>>& element : box)
    {
        if (element.second.first == name)
        {
            element.second.second = value;
            found = true;
        }
    }
    if (!found)
    {
        box.push_back(std::pair<int, std::pair<std::string, int>>{index, {name, value}});
    }
}


void remove(std::vector<std::pair<int, std::pair<std::string, int>>>& box, std::string name)
{
    for (size_t i {}; i < box.size(); i++)
    {

        if (box[i].second.first == name)
        {
            box.erase(box.begin()+i);
            break;
        }
    }
}


int main() {
    std::string line;
    int part1_sum {};
    std::map<int, std::vector<std::pair<int, std::pair<std::string, int>>>> box {};
    for (int i {}; i <= 256; i++)
    {
        box[i] = {};
    }
    
    int index {};
    while (std::getline(std::cin, line)) 
    {
        for (size_t pos {}; line.find(',', pos) != std::string::npos; pos = line.find(',', pos+1)) 
        {
            std::string word;
            size_t next = line.find(',', pos+1);
            
            if (pos == 0)
                word = line.substr(pos, next-pos);
            else 
                word = line.substr(pos+1, next-pos-1);
            int hash = get_hash(word);
            part1_sum += hash;

            if (word.find('=') != std::string::npos)
            {
                size_t split = word.find('=');
                std::string name = word.substr(0, split);
                int value = stoi(word.substr(split+1));
                add(box[get_hash(name)], name, value, index);
            } else  // contains '-'
            {
                size_t split = word.find('-');
                std::string name = word.substr(0, split);
                remove(box[get_hash(name)], name);
            }



        }
    }

    int part2_sum {};
    for (size_t box_nr {}; box_nr < box.size(); box_nr++)
    {
        for (size_t slot_nr {}; slot_nr < box[box_nr].size(); slot_nr++)
        {
            part2_sum += (box_nr+1) * (slot_nr+1) * box[box_nr][slot_nr].second.second;
        }
    }

    

   std::cout << "part 1:" << part1_sum << std::endl;
   std::cout << "part 2:" << part2_sum << std::endl;

    return 0;
}