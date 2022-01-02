#ifndef __ICE__
#define __ICE__

/*
** created by Ice with ♥
*/

#include <exception>
#include <iostream>
#include <compare>
#include <string_view>
#include <type_traits>
#include <concepts>

namespace Ice {

    template<typename Type>
    class Ice_Ptr final {
        public:
// I know constructors are already inline and constexpr has no effect on program but it's cool to make everything constexpr
            constexpr inline Ice_Ptr() = default;
            explicit constexpr inline Ice_Ptr(Type* ) noexcept;
            explicit constexpr inline Ice_Ptr(Type const& ) noexcept;
            inline ~Ice_Ptr();

            constexpr inline Ice_Ptr(Ice_Ptr const& );
            constexpr inline Ice_Ptr(Ice_Ptr &&) noexcept;

            constexpr inline Ice_Ptr& operator=(Ice_Ptr const&) noexcept;
            constexpr inline Ice_Ptr& operator=(Ice_Ptr &&) noexcept;

            //access operators
            constexpr inline Type operator*() const noexcept;
            constexpr inline Type* operator->() const noexcept;

            //spaceship operator

             constexpr inline auto operator<=>(Ice_Ptr const&) const noexcept;
             constexpr inline bool operator==(Ice_Ptr const&)  const noexcept;

            //get types of pointers method version
            constexpr inline std::string_view what_type() const noexcept;

            //retrun the address which _ptr points to
            constexpr inline auto* get() const noexcept;

        private:
            Type *_ptr;
    };

//this is gonna be std::make_shared but shit version of it ^^
template<typename Type>
requires (!std::is_same_v<Type, const char*>) //don't use const char plz -><-
constexpr inline Ice_Ptr<Type> make_Ice(Type const& value = {}) noexcept  {
    return Ice_Ptr<Type>(value);
}


//Ice_Ptr(const char*) -> Ice_Ptr<std::string_view>; // eh I tried to make const char* to std::string
//which helps to add arithmetic operations feature
//could you fix it for me

}// end of Ice namespace


template<typename Type>
constexpr inline Ice::Ice_Ptr<Type>::Ice_Ptr(Type* mem) noexcept {
    _ptr = mem;
}

template<typename Type>
constexpr inline Ice::Ice_Ptr<Type>::Ice_Ptr(Type const& val) noexcept {
    _ptr = new Type(val);
}


//copy constructor
template<typename Type>
constexpr inline Ice::Ice_Ptr<Type>::Ice_Ptr(Ice_Ptr<Type> const& obj) {
    try { //this is c++20 feature ^^
        _ptr = new(std::nothrow) Type(*obj._ptr);
        if(_ptr == nullptr)
            throw _ptr; //heh heh I khow this never fail and only makes my program slower but Ice likes exceptions

    }catch(std::bad_alloc& ba) { std::cerr << " Bad_Alloc caught : " <<
            __FILE__ << " : " << __LINE__ << '\n' << ba.what() << std::endl;}
}


//move constructor
template<typename Type>
constexpr inline Ice::Ice_Ptr<Type>::Ice_Ptr(Ice_Ptr &&obj) noexcept {
    _ptr = std::move(obj._ptr);
    obj._ptr = nullptr;

}

//destructor
template<typename Type>
Ice::Ice_Ptr<Type>::~Ice_Ptr() {
    try{
        if(_ptr != nullptr)
            throw _ptr;

    }catch(...) {
        delete _ptr;
    }
    _ptr = nullptr;
}

//copy assignment
template<typename Type>
constexpr inline Ice::Ice_Ptr<Type>& Ice::Ice_Ptr<Type>::operator=(Ice_Ptr<Type> const& obj) noexcept {
    if(this == &obj)
        return this;

    _ptr = new Type(*obj._ptr);
    return *this;
}

//move assignment
template<typename Type>
constexpr inline Ice::Ice_Ptr<Type>& Ice::Ice_Ptr<Type>::operator=(Ice_Ptr<Type> &&obj)  noexcept {
    if(this == &obj)
        return *this;

    try{
        if(_ptr != nullptr)
            throw _ptr;
    }catch(...) {
        delete _ptr;
    }

    _ptr = std::move(obj._ptr);
    obj._ptr = nullptr;
    return *this;
}

//access operators

template<typename Type>
constexpr inline Type Ice::Ice_Ptr<Type>::operator*() const noexcept {
   return *_ptr;
}


template<typename Type>
constexpr inline Type* Ice::Ice_Ptr<Type>::operator->() const noexcept {
   return _ptr;
}

template<typename Type>
constexpr inline std::string_view Ice::Ice_Ptr<Type>::what_type() const noexcept {
    return std::string_view{ typeid(*_ptr).name() };
}

//compare pointers plz
template<typename Type>
constexpr inline auto Ice::Ice_Ptr<Type>::operator<=>(Ice_Ptr<Type> const& obj) const noexcept {
    return *_ptr <=> *obj._ptr;
}

template<typename Type>
constexpr inline bool Ice::Ice_Ptr<Type>::operator==(Ice_Ptr<Type> const& obj) const noexcept {
    return *_ptr == *obj._ptr;
}

// get address

template<typename Type>
constexpr inline auto* Ice::Ice_Ptr<Type>::get() const noexcept {
    return _ptr;
}

#endif
