#include "Ice_Ptr.hpp"

int main()
{
    Ice::Ice_Ptr p1 = Ice::make_Ice('c');
    Ice::Ice_Ptr p2 { new char('b') };

    std::cout << std::boolalpha <<
        " p1 != p2 : "  << (p1 != p2) <<
        " p1 < p2  : "  << (p1 < p2)  << '\n';

    return 0;
}
