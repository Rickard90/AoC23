#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <numeric>



struct Component {
    char type {};
    std::string name {};
    bool binary {};
    std::vector<std::string> connections {};
    std::map<std::string, bool> last_received {}; //only used by junctions
};

struct Signal {
    std::string sender {};
    std::string target {};
    bool signal {};
};

long long int zl {-1};
long long int qn {-1};
long long int xf {-1};
long long int xn {-1};


void send(std::queue<Signal>& signals, std::string sender, std::vector<std::string> const& connections, bool signal, long long int n)
{
    for (auto receiver : connections)
    {
        signals.push({sender, receiver, signal});
        if (signal == true)
        {
            if (sender == "xn")
            {
                if (xn == -1)
                    xn = n;
            }
            if (sender == "qn")
            {
                if (qn == -1)
                    qn = n;
            }
            if (sender == "xf")
            {
                if (xf == -1)
                    xf = n;
            }
            if (sender == "zl")
            {
                if (zl == -1)
                    zl = n;
            }
        }
    }
}

int main() {
    std::string line;
    std::stringstream ss {};
    std::map<std::string, Component> components {};
    std::queue<Signal> signals {};

    while (std::getline(std::cin, line)) 
    {
        size_t i = line.find('-');

        ss << line.substr(i+2);
        std::string component {};
        char type {};
        if (line.substr(0, i) != "broadcaster ")
        {
            component = line.substr(1, i-2);
            type = line[0];
            
        } else {
            component = "broadcaster";
            type ='!';
        }
        components[component] = {type, component};
        std::string receiver {};
        while (ss >> receiver)
        {
            if (receiver.back() == ',')
                receiver.pop_back();
            components[component].connections.push_back(receiver);
        }
        ss.str("");
        ss.clear();
    }

    for (std::pair<const std::string, Component>& c : components)
    {
        for (std::string const& receiver : c.second.connections)
        {
            if (components[receiver].type == '&')
                components[receiver].last_received[c.first] = false;
        }
    }

    int high_pulses {};
    int low_pulses {};
    for (long long int n {1}; n <= 10000; n++)
    {
        signals.push({"button", "broadcaster", false});
        while (!signals.empty())
        {
            Signal signal = signals.front();
            signals.pop();

            if (n < 1000)
            {
                if (signal.signal)
                    high_pulses++;
                else
                    low_pulses++;
            }

            //std::cout << signal.sender << " -" << (signal.signal?"hig-> ":"low-> ") << signal.target << std::endl;
            Component& receiver = components[signal.target];
            if ( receiver.type == '%' && !signal.signal )
            {
                receiver.binary = !receiver.binary;
                send(signals, receiver.name, receiver.connections, receiver.binary, n);
            } 
            else if ( receiver.type == '&' )
            {
                receiver.last_received[signal.sender] = signal.signal;
                bool all_high = true;
                for (auto remembered_input : receiver.last_received)
                {
                    if (!remembered_input.second)
                    {
                        all_high = false;
                    }
                }
                send(signals, receiver.name, receiver.connections, !all_high, n);
            } 
            else if ( receiver.type == '!' )
            {
                send(signals, receiver.name, receiver.connections, false, n);
            }
        }
    }
    std::cout << "Part1: " << low_pulses*high_pulses << std::endl;
    long long int part2 = zl*qn*xf*xn;
    std::cout << "multiply " << part2 << std::endl;

    return 0;
}
