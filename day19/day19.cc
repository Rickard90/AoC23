#include <iostream>
#include <map>
#include <string>
#include <sstream>


struct Range
{
    long long int begin {};
    long long int end {};
};

struct Ranges
{
    Range x {};
    Range m {};
    Range a {};
    Range s {};
};

long long int rec_helper(std::string opt, std::map<std::string, std::string>& wf, Ranges r);

long long int recursive(std::string active_wf, std::map<std::string, std::string>& wf, Ranges r) 
{

    int value {};
    std::stringstream ss {};
    std::string line {};
    char category {}, compare {};
    if (active_wf.find(',') == std::string::npos)
    {
        ss.str(wf[active_wf]);    
    } else
    {
        ss.str(active_wf);
    }
    ss >> category >> compare >> value >> line;
    size_t i = line.find(',');
    std::string opt1 = line.substr(1, i-1);
    std::string opt2 = line.substr(i+1);
    if (category == 'x') 
    {
        if ((compare == '>' && r.x.begin > value) || (compare == '<' && r.x.end < value))
        {
            return rec_helper(opt1, wf, r);
        } else if ((compare == '>' && r.x.begin < value && r.x.end > value))
        {
            Ranges lower_part {{r.x.begin, value}, r.m, r.a, r.s};
            Ranges upper_part {{value+1, r.x.end}, r.m, r.a, r.s};
            return rec_helper(opt1, wf, upper_part) + rec_helper(opt2, wf, lower_part);
        } else if ((compare == '<' && r.x.begin < value && r.x.end > value))
        {
            Ranges lower_part {{r.x.begin, value-1}, r.m, r.a, r.s};
            Ranges upper_part {{value, r.x.end}, r.m, r.a, r.s};
            return rec_helper(opt1, wf, lower_part) + rec_helper(opt2, wf, upper_part);
        } else if ((compare == '>' && r.x.end <= value) || (compare == '<' && r.x.begin >= value))
        {
            return rec_helper(opt2, wf, r);
        }
    }
    if (category == 'm') 
    {
        if ((compare == '>' && r.m.begin > value) || (compare == '<' && r.m.end < value))
        {
            return rec_helper(opt1, wf, r);
        } else if ((compare == '>' && r.m.begin < value && r.m.end > value))
        {
            Ranges lower_part {r.x, {r.m.begin, value}, r.a, r.s};
            Ranges upper_part {r.x, {value+1, r.m.end}, r.a, r.s};
            return rec_helper(opt1, wf, upper_part) + rec_helper(opt2, wf, lower_part);
        } else if ((compare == '<' && r.m.begin < value && r.m.end > value))
        {
            Ranges lower_part {r.x, {r.m.begin, value-1}, r.a, r.s};
            Ranges upper_part {r.x, {value, r.m.end}, r.a, r.s};
            return rec_helper(opt1, wf, lower_part) + rec_helper(opt2, wf, upper_part);
        } else if ((compare == '>' && r.m.end <= value) || (compare == '<' && r.m.begin >= value))
        {
            return rec_helper(opt2, wf, r);
        }
    }
    if (category == 'a') 
    {
        if ((compare == '>' && r.a.begin > value) || (compare == '<' && r.a.end < value))
        {
            return rec_helper(opt1, wf, r);
        } else if ((compare == '>' && r.a.begin < value && r.a.end > value))
        {
            Ranges lower_part {r.x, r.m, {r.a.begin, value}, r.s};
            Ranges upper_part {r.x, r.m, {value+1, r.a.end}, r.s};
            return rec_helper(opt1, wf, upper_part) + rec_helper(opt2, wf, lower_part);
        } else if ((compare == '<' && r.a.begin < value && r.a.end > value))
        {
            Ranges lower_part {r.x, r.m, {r.a.begin, value-1}, r.s};
            Ranges upper_part {r.x, r.m, {value, r.a.end}, r.s};
            return rec_helper(opt1, wf, lower_part) + rec_helper(opt2, wf, upper_part);
        } else if ((compare == '>' && r.a.end <= value) || (compare == '<' && r.a.begin >= value))
        {
            return rec_helper(opt2, wf, r);
        }
    }
    if (category == 's') 
    {
        if ((compare == '>' && r.s.begin > value) || (compare == '<' && r.s.end < value))
        {
            return rec_helper(opt1, wf, r);
        } else if ((compare == '>' && r.s.begin < value && r.s.end > value))
        {
            Ranges lower_part {r.x, r.m, r.a, {r.s.begin, value}};
            Ranges upper_part {r.x, r.m, r.a, {value+1, r.s.end}};
            return rec_helper(opt1, wf, upper_part) + rec_helper(opt2, wf, lower_part);
        } else if ((compare == '<' && r.s.begin < value && r.s.end > value))
        {
            Ranges lower_part {r.x, r.m, r.a, {r.s.begin, value-1}};
            Ranges upper_part {r.x, r.m, r.a, {value, r.s.end}};
            return rec_helper(opt1, wf, lower_part) + rec_helper(opt2, wf, upper_part);
        } else if ((compare == '>' && r.s.end <= value) || (compare == '<' && r.s.begin >= value))
        {
            return rec_helper(opt2, wf, r);
        }
    }
    return 0;
}

long long int rec_helper(std::string opt, std::map<std::string, std::string>& wf, Ranges r) {
    if (opt.find(':') == std::string::npos)
    {
        if (opt == "A")
        {
            return (r.x.end-r.x.begin+1)*(r.m.end-r.m.begin+1)*(r.a.end-r.a.begin+1)*(r.s.end-r.s.begin+1);
        } else if (opt == "R")
        {
            return 0;
        }
    }
    return recursive(opt, wf, r);
}


int main() {
    std::string line;
    std::stringstream ss {};

    std::map<std::string, std::string> wf {};
    long long int sum {};
    while (std::getline(std::cin, line)) 
    {
        if (line.size() < 2) 
        {
            break;
        }
        size_t i = line.find('{');
        wf[line.substr(0, i)] = line.substr(i+1, line.size()-i-2);
    }
    
    sum = recursive("in", wf, Ranges{{1, 4000}, {1, 4000}, {1, 4000}, {1, 4000}});
    std::cout << "total sum: " << sum << std::endl;

    return 0;
}