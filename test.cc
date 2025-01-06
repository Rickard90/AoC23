#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>


int main() {
    
    std::stack<int, std::vector<int>> name {};
    name.push(1);
    std::cout << name.top() << std::endl;
    name.push(5);
    std::cout << name.top() << std::endl;
    name.pop();
    std::cout << name.top() << std::endl;
    return 0;
}