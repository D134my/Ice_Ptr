#include "Ice_Ptr.hpp"


struct test {
    inline void print() const noexcept {
        std::cout << "Hello Ice \n";
    }
};

int main() {
    Ice::Ice_Ptr ptr_One { new int(4) };
    Ice::Ice_Ptr ptr_Two = Ice::make_Ice<int>(55);
    Ice::Ice_Ptr<test> ptr_Three = Ice::make_Ice<test>();

    std::cout << *ptr_One << '\t' << *ptr_Two << '\n';
    ptr_Three->print();

    return 0;
}
