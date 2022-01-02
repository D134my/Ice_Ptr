#include "Ice_Ptr.hpp"


struct test {
    inline void print() const noexcept {
        std::cout << "Hello Ice \n";
    }
};

int main() {

    Ice::Ice_Ptr ptr_One = Ice::make_Ice(4);
    Ice::Ice_Ptr ptr_Two { new double(6.01) };
    std::cout << *ptr_One << '\t'<< *ptr_Two << '\n';
    std::cout << "ptr_One.get() : " << ptr_One.get() << '\n';

    Ice::Ice_Ptr ptr_Three = Ice::make_Ice<test>();
    ptr_Three->print();
    return 0;
}
