#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

#define debug false

#define LOW_X 200000000000000
#define LOW_Y 200000000000000
#define HIGH_X 400000000000000
#define HIGH_Y 400000000000000
/*#define LOW_X 7
#define LOW_Y 7
#define HIGH_X 27
#define HIGH_Y 27*/


struct Hail
{
    long double dydx {};
    long long int x {};
    long long int y {};
    long long int dx {};
    long long int dy {};
};

/*//kx+m = jx+l

//p1
//5 = 1*3 + m
//5-1*3 = m = 2

//p2
//2 = -2*4 + m
//2+2*4 = m = 10

//p1=p2
//1*x + 2 = -2*x + 10
//(1- -2)x = 10-2
//3x = 8
//x = 8/3
// (8/3)x + 2 = y*/


bool crosses_inside(Hail const& a, Hail const& b)
{
    long long int const& x1 = a.x;
    long long int const& y1 = a.y;
    long double const& k1 = a.dydx;
    long double m1 = y1 - k1*x1;
    long long int const& x2 = b.x;
    long long int const& y2 = b.y;
    long double const& k2 = b.dydx;
    long double m2 = y2 - k2*x2;

    long double x = (m2-m1) / (k1-k2);
    long double y = k1*x + m1;
    if (debug)
    {
        std::cout << "Testing: " << a.x << " " << a.y << " " << a.dydx << std::endl;
        std::cout << "         " << b.y << " " << b.x << " " << b.dydx << std::endl;
        std::cout << "         " << x << ":" << y << std::endl;
    }

    if (LOW_X <= x && x <= HIGH_X && LOW_Y <= y && y <= HIGH_Y)
    {
        if (x > x1 && a.dx <= 0)
        {
            return false;
        }
        if (y > y1 && a.dy <= 0)
        {
            return false;
        }
        if (x < x1 && a.dx >= 0)
        {
            return false;
        }
        if (y < y1 && a.dy >= 0)
        {
            return false;
        }
        
        if (x > x2 && b.dx <= 0)
        {
            return false;
        }
        if (y > y2 && b.dy <= 0)
        {
            return false;
        }
        if (x < x2 && b.dx >= 0)
        {
            return false;
        }
        if (y < y2 && b.dy >= 0)
        {
            return false;
        }
        return true;
    }
    return false;
}

int main() {
    std::string line {};
    std::vector<Hail> hails {};
    std::stringstream ss {};
    int part1 {};

    while (std::getline(std::cin, line)) 
    {
        ss << line;
        long long int x {}, y {}, z {}, dx {}, dy {}, dz {};
        char c {};

        ss >> x >> c >> y >> c >> z >> c >> dx >> c >> dy >> c >> dz;
        if (debug)
            std::cout << dy << " " << dx << std::endl;
        hails.push_back({static_cast<long double>(dy)/static_cast<long double>(dx), x, y, dx, dy});
        ss.str("");
        ss.clear();
    }

    //std::sort(hails.begin(), hails.end(), [](Hail const& a, Hail const& b){return a.dydx < b.dydx;});
    //long double prev {hails.front().dydx};
    //std::cout << prev << std::endl;
    for (size_t i {0}; i < hails.size()-1; i++)
    {
        for (size_t j {i+1}; j < hails.size(); j++)
        {
            if (hails[i].dydx != hails[j].dydx)
            {
                if (crosses_inside(hails[i], hails[j]))
                {
                    part1++;
                    if (debug)
                    {
                        std::cout << "         true" << std::endl;
                    }
                }
                
            }
        }
    }



    std::cout << "\nPart1: " << part1 << std::endl;

    return 0;
}