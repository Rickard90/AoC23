#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <sstream>



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
        std::cout << "Added component " << component << " type " << type << std::endl;

        std::string receiver {};
        while (ss >> receiver)
        {
            if (receiver.back() == ',')
                receiver.pop_back();
            components[component].connections.push_back(receiver);
            std::cout << "  Pushed " << receiver << " as receiver to " << component << std::endl;
        }
        ss.str("");
        ss.clear();
    }

    for (std::pair<const std::string, Component>& c : components)
    {
        for (std::string const& receiver : c.second.connections)
        {
            if (components[receiver].type == '&')
            {
                components[receiver].last_received[c.first] = false;
                std::cout << "Added " << c.first << " as sender to " << components[receiver].type << receiver << std::endl;
            }
        }
    }

    int high_pulses {};
    int low_pulses {};
    for (int n {}; n < 1000; n++)
    {
        signals.push({"button", "broadcaster", false});
        while (!signals.empty())
        {
            Signal signal = signals.front();
            signals.pop();

            if (signal.signal)
                high_pulses++;
            else
                low_pulses++;

            std::cout << signal.sender << " -" << (signal.signal?"hig-> ":"low-> ") << signal.target << std::endl;
            Component& receiver = components[signal.target];
            if ( receiver.type == '%' )
            {
                if ( !signal.signal ) //is low
                {
                    receiver.binary = !receiver.binary; //flip
                    for (auto receiversreceiver : receiver.connections)
                    {
                        signals.push({receiver.name, receiversreceiver, receiver.binary}); //sends high
                    }
                }
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
                if (all_high)
                {
                    for (auto receiversreceiver : receiver.connections)
                    {
                        signals.push({receiver.name, receiversreceiver, false}); //sends low
                    }
                } else 
                {
                    for (auto receiversreceiver : receiver.connections)
                    {
                        signals.push({receiver.name, receiversreceiver, true}); //sends high
                    }
                }

            } 
            else if ( receiver.type == '!' )
            {
                for (auto receiversreceiver : receiver.connections)
                {
                    signals.push({receiver.name, receiversreceiver, false}); //sends low
                }
            }
        }
    }

    
    std::cout << "total low: " << low_pulses << " total high " << high_pulses << " Multiplied: " << low_pulses*high_pulses << std::endl;

    return 0;
}