#include <iostream>
#include <map>
#include <string>
#include <sstream>


int rec_helper(std::string& opt, std::map<std::string, std::string>& wf, int x, int m, int a, int s);

int recursive(std::string active_wf, std::map<std::string, std::string>& wf, int x, int m, int a, int s) 
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
        if ((compare == '>' && x > value) || (compare == '<' && x < value))
        {
            return rec_helper(opt1, wf, x, m, a, s);
        } else 
        {
            return rec_helper(opt2, wf, x, m, a, s);
        }
    }
    if (category == 'm') 
    {
        if ((compare == '>' && m > value) || (compare == '<' && m < value))
        {
            return rec_helper(opt1, wf, x, m, a, s);
        } else 
        {
            return rec_helper(opt2, wf, x, m, a, s);
        }
    }
    if (category == 'a') 
    {
        if ((compare == '>' && a > value) || (compare == '<' && a < value))
        {
            return rec_helper(opt1, wf, x, m, a, s);
        } else 
        {
            return rec_helper(opt2, wf, x, m, a, s);
        }
    }
    if (category == 's') 
    {
        if ((compare == '>' && s > value) || (compare == '<' && s < value))
        {
            return rec_helper(opt1, wf, x, m, a, s);
        } else 
        {
            return rec_helper(opt2, wf, x, m, a, s);
        }
    }
    return 0;
}


int rec_helper(std::string& opt, std::map<std::string, std::string>& wf, int x, int m, int a, int s) {
    if (opt.find(':') == std::string::npos)
    {
        if (opt == "A")
        {
            return x+m+a+s;
        } else if (opt == "R")
        {
            return 0;
        }
    }
    return recursive(opt, wf, x, m, a, s);
}

int main() {
    std::string line;
    std::stringstream ss {};

    std::map<std::string, std::string> wf {};
    int sum {};
    bool reading_workflows = true;
    while (std::getline(std::cin, line)) 
    {
        if (line.size() < 2) 
        {
            reading_workflows = false;
        } else 
        {
            if (reading_workflows)
            {
                size_t i = line.find('{');
                wf[line.substr(0, i)] = line.substr(i+1, line.size()-i-2);
            } else
            {
                ss.str(line);
                int x {}, m {}, a {}, s {};
                char c {};
                ss >> c >> c >> c >> x >> c >> c >> c >> m
                   >> c >> c >> c >> a >> c >> c >> c >> s;

                sum += recursive("in", wf, x, m, a, s);

                ss.str("");
                ss.clear();
            }
        }
    }

   std::cout << "total sum: " << sum << std::endl;

    return 0;
}