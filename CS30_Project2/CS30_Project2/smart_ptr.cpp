#pragma once
#include <iostream>
#include <stdexcept>
#include <new>
#include <set>
#include <cassert>

using namespace std;

class null_ptr_exception : public std::exception {
public:
    null_ptr_exception(const char* msg) : exception(msg) {}

};

template <typename T>
class smart_ptr {
public:
    smart_ptr()noexcept;
    // Create a smart_ptr that is initialized to nullptr. The reference count
    // should be initialized to nullptr.

    explicit smart_ptr(T*& raw_ptr) ;
    // Create a smart_ptr that is initialized to raw_ptr. The reference count
    // should be one. No change is made to raw_ptr.

    explicit smart_ptr(T*&& raw_ptr);
    // Create a smart_ptr that is initialized to raw_ptr. The reference count
    // should be one. If the constructor fails raw_ptr is deleted.	

    smart_ptr(const smart_ptr& rhs) noexcept;
    // Copy construct a pointer from rhs. The reference count should be 
    // incremented by one.

    smart_ptr(smart_ptr&& rhs) noexcept;
    // Move construct a pointer from rhs.

    smart_ptr& operator=(const smart_ptr& rhs);
    // This assignment should make a shallow copy of the right-hand side's
    // pointer data. The reference count should be incremented as appropriate.

    smart_ptr& operator=(smart_ptr&& rhs) noexcept;
    // This move assignment should steal the right-hand side's pointer data.

    bool clone();
    // If the smart_ptr is either nullptr or has a reference count of one, this
    // function will do nothing and return false. Otherwise, the referred to
    // object's reference count will be decreased and a new deep copy of the
    // object will be created. This new copy will be the object that this
    // smart_ptr points and its reference count will be one. 

    int ref_count() const noexcept{

        if (ref_ == nullptr) { return 0; }
        return *ref_;

    }
    // Returns the reference count of the pointed to data.

    T& operator*();
    // The dereference operator shall return a reference to the referred object.
    // Throws null_ptr_exception on invalid access. 

    T* operator->();
    // The arrow operator shall return the pointer ptr_. Throws null_ptr_exception
    // on invalid access.
    
    ~smart_ptr();          // deallocate all dynamic memory

private:
    T* ptr_;               // pointer to the referred object
    int* ref_;             // pointer to a reference count
};

template<typename T>    
smart_ptr<T>::smart_ptr() noexcept{

    ptr_ = nullptr;
    ref_ = nullptr;

}

template<typename T>
smart_ptr<T>::smart_ptr(T*& raw_ptr){

    if (raw_ptr == nullptr) {       //if raw_ptr is null, initialize all to null

        ptr_ = nullptr;
        ref_ = nullptr;

    }
    else {
        try {
            ptr_ = raw_ptr;
            ref_ = new int{ 1 };
        }
        catch (bad_alloc) {
        
             throw;

        }

    }

}

template<typename T>
smart_ptr<T>::smart_ptr(T*&& raw_ptr) {

    try {
        ptr_ = raw_ptr;
        ref_ = new int{ 1 };
    }
    catch (bad_alloc) {

        delete ptr_;
        throw;

    }

}

template<typename T>
smart_ptr<T>::smart_ptr(const smart_ptr& rhs) noexcept{

    ptr_ = rhs.ptr_;
    ref_ = rhs.ref_;

    if (ref_ != nullptr) {      //check if ref_ points to a value that can be incremented

        (*ref_)++;

    }

}

template<typename T>
smart_ptr<T>::smart_ptr(smart_ptr&& rhs) noexcept {

    ptr_ = rhs.ptr_;            
    ref_ = rhs.ref_;

    rhs.ptr_ = nullptr;
    rhs.ref_ = nullptr;
}

template<typename T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr& rhs) {
    if (ref_ != nullptr) { (*ref_)--; }      //start by decrementing lhs data to take rhs

    ptr_ = rhs.ptr_;       
    ref_ = rhs.ref_;
    
    if (ref_ != nullptr) { 
        (*ref_)++; 
    } //check if ref_ is nullptr before trying to increment

    return *this;
}

template<typename T>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr&& rhs) noexcept {

    delete(ptr_);
    delete(ref_);

    ptr_ = rhs.ptr_;
    ref_ = rhs.ref_;
    
    rhs.ptr_ = nullptr;
    rhs.ref_ = new int{ 0 };
    
    return *this;

}

template<typename T>
bool smart_ptr<T>::clone() {

    if (ptr_ == nullptr || *ref_ == 1) {

        return false;

    } 
    try {

        (*ref_)--;

        ptr_ = new T(*ptr_);
        ref_ = new int{ 1 };

        return true;
    }
    catch (bad_alloc) {
        (*ref_)++;
        throw;
    }
}

template<typename T>
T& smart_ptr<T>::operator*() {
        
    if (ptr_ == nullptr) {          //check if *ptr_ is null before trying to return it
       
        throw null_ptr_exception("null ptr exception");
    }

    return *ptr_;

}

template<typename T>
T* smart_ptr<T>::operator->() {

    if (ptr_ == nullptr) {          //check if ptr_ is null before trying to return it

        throw null_ptr_exception("null ptr exception");
    }

    return ptr_;

}

template<typename T>
smart_ptr<T>::~smart_ptr() {

    if (ref_ != nullptr) { (*ref_)--; }                      //don't delete until ref_ count is 0

    if (ref_ == nullptr || *ref_ <= 0) {               //once ref count is 0, delete ref_ and ptr_

         delete(ptr_);
         delete(ref_);

    }
    else {

        ptr_ = nullptr;
        ref_ = nullptr;
        

    }



}

struct OurType
{
    explicit OurType(int v = 0) : m_value(v) { m_count++; }
    OurType(const OurType& other) : m_value(other.m_value)
    {
        m_count++; m_asstcopycount++;
    }
    ~OurType() { m_count--; }
    OurType& operator=(const OurType& rhs)
    {
        m_value = rhs.m_value; m_asstcopycount++; return *this;
    }

    int m_value;
    static int m_count;
    static int m_asstcopycount;
};

inline
bool operator==(const OurType& lhs, const OurType& rhs)
{
    return lhs.m_value == rhs.m_value;
}

inline
bool operator<(const OurType& lhs, const OurType& rhs)
{
    return lhs.m_value < rhs.m_value;
}

inline
bool operator!=(const OurType& lhs, const OurType& rhs)
{
    return !(lhs == rhs);
}

inline
bool operator<=(const OurType& lhs, const OurType& rhs)
{
    return !(rhs < lhs);
}

inline
bool operator>=(const OurType& lhs, const OurType& rhs)
{
    return !(lhs < rhs);
}

inline
bool operator>(const OurType& lhs, const OurType& rhs)
{
    return rhs < lhs;
}

inline
bool operator==(const OurType& lhs, int rhs)
{
    return lhs.m_value == rhs;
}

inline
bool operator!=(const OurType& lhs, int rhs)
{
    return !(lhs == rhs);
}

#include <iostream>

inline
std::ostream& operator<<(std::ostream& lhs, const OurType& rhs)
{
    return lhs << rhs.m_value;
}

int OurType::m_count = 0;
int OurType::m_asstcopycount = 0;

inline int itemcount()
{
    return OurType::m_count;
}

inline int nasstcopys()
{
    return OurType::m_asstcopycount;
}

std::set<void*> addrs;
bool recordaddrs = false;

int throwBadAlloc = 0;
// value of 0 means allocations don't throw
// value of 1 means 1st allocation throws
// value of 2 means 2nd allocation throws
// value of n means nth allocation throws

void* operator new(size_t n)
{
    if (recordaddrs || throwBadAlloc) {
        if (throwBadAlloc == 1)
            throw std::bad_alloc();
        else if (throwBadAlloc > 1)
            throwBadAlloc--;
    }
    void* p = malloc(n);
    if (recordaddrs)
    {
        recordaddrs = false;
        addrs.insert(p);
        recordaddrs = true;
    }
    return p;
}

void operator delete(void* p) noexcept
{
    if (recordaddrs)
    {
        recordaddrs = false;
        std::set<void*>::iterator it = addrs.find(p);
        if (it != addrs.end())
            addrs.erase(it);
        recordaddrs = true;
    }
    free(p);
}

void testone(int n)
{
    smart_ptr<double> dsp0;
    smart_ptr<double> dsp1{ new double {3.14} };
    smart_ptr<double> dsp2, dsp3;

    switch (n)
    {
    default: {
        assert(false);
    } break; case  1: {
        assert(dsp0.ref_count() == 0);
    } break; case  2: {
        assert(dsp1.ref_count() == 1);
    } break; case  3: {
        dsp0 = dsp1;
        assert(dsp0.ref_count() == 2);
    } break; case  4: {
        dsp3 = dsp2 = dsp1;
        assert(dsp3.ref_count() == dsp2.ref_count() &&
            dsp1.ref_count() == dsp2.ref_count() &&
            dsp1.ref_count() == 3);
    } break; case  5: {
        dsp1 = dsp0;
        assert(dsp1.ref_count() == 0 && dsp2.ref_count() == 0);
    } break; case  6: {
        assert(std::is_nothrow_constructible<smart_ptr<int>>::value);
        assert(std::is_nothrow_copy_constructible<smart_ptr<int>>::value);
        // possible XCode compiler bug for following two asserts
        //assert(std::is_nothrow_constructible<smart_ptr<int>,int*>::value);
        //assert(std::is_nothrow_assignable<A,A>::value);
        assert(std::is_nothrow_move_assignable<smart_ptr<int>>::value);
        assert(std::is_nothrow_move_constructible<smart_ptr<int>>::value);
        assert(!noexcept(std::declval<smart_ptr<int>>().clone()));
        assert(!noexcept(std::declval<smart_ptr<int>>().operator*()));
        assert(!noexcept(std::declval<smart_ptr<int>>().operator->()));
        assert(noexcept(std::declval<smart_ptr<int>>().ref_count()));
    } break; case  7: {
        {
            // testing constructor
            smart_ptr<OurType> osp0{ new OurType{0} };
            assert(itemcount() == 1);
        }
        assert(itemcount() == 0);
    } break; case  8: {
        {
            // testing assignment operator
            smart_ptr<OurType> osp0{ new OurType{0} };
            assert(itemcount() == 1);
            smart_ptr<OurType> osp1;
            osp1 = osp0;
            assert(itemcount() == 1);
        }
        assert(itemcount() == 0);
    } break; case  9: {
        {
            // testing copy constructor
            smart_ptr<OurType> osp0{ new OurType{0} };
            assert(itemcount() == 1);
            smart_ptr<OurType> osp1{ osp0 };
            assert(osp0.ref_count() == 2);
            assert(osp1.ref_count() == 2);
            assert(itemcount() == 1);
        }
        assert(itemcount() == 0);
    } break; case 10: {
        {
            // testing move constructor
            smart_ptr<OurType> osp0{ new OurType{0} };
            assert(itemcount() == 1);
            smart_ptr<OurType> osp1{ std::move(osp0) };
            assert(itemcount() == 1);
        }
        assert(itemcount() == 0);
    } break; case 11: {
        {
            // testing move assignment
            smart_ptr<OurType> osp0{ new OurType{0} };
            assert(osp0.ref_count() == 1);
            assert(itemcount() == 1);
            smart_ptr<OurType> osp1;
            osp1 = std::move(osp0);
            assert(osp1.ref_count() == 1);
            assert(osp0.ref_count() == 0);
            assert(itemcount() == 1);
        }
        assert(itemcount() == 0);
    } break; case 12: {
        {
            // testing move constructor
            smart_ptr<OurType> osp0{ new OurType{0} };
            assert(osp0.ref_count() == 1);
            assert(itemcount() == 1);
            smart_ptr<OurType> osp1{ std::move(osp0) };
            assert(osp1.ref_count() == 1);
            assert(osp0.ref_count() == 0);
            assert(itemcount() == 1);
        }
        assert(itemcount() == 0);
    } break; case 13: {
        {
            // testing move assignment
            smart_ptr<OurType> osp0{ new OurType{0} };
            assert(osp0.ref_count() == 1);
            assert(itemcount() == 1);
            smart_ptr<OurType> osp1;
            osp1 = std::move(osp0);
            assert(osp1.ref_count() == 1);
            assert(osp0.ref_count() == 0);
            assert(itemcount() == 1);
        }
        assert(itemcount() == 0);
    } break; case 14: {
        {
            // testing assignment operator
            smart_ptr<OurType> osp0;
            assert(itemcount() == 0);
            smart_ptr<OurType> osp1;
            osp1 = osp0;
            assert(itemcount() == 0);
        }
        assert(itemcount() == 0);
    } break; case 15: {
        try {
            *dsp0;
            assert(0);
        }
        catch (...) {}
    } break; case 16: {
        smart_ptr<OurType> osp{ new OurType{42} };
        try {
            assert((*osp).m_value == 42);
        }
        catch (...) {
            assert(0);
        }
    } break; case 17: {
        smart_ptr<OurType> osp;
        try {
            (*osp).m_value;     // should throw
            assert(0);
        }
        catch (...) {}
    } break; case 18: {
        smart_ptr<OurType> osp{ new OurType{42} };
        try {
            assert(osp->m_value == 42);
        }
        catch (...) {
            assert(0);
        }
    } break; case 19: {
        smart_ptr<OurType> osp;
        try {
            osp->m_value;       // should throw
            assert(0);
        }
        catch (...) {}
    } break; case 20: {
        assert(!dsp0.clone());
        assert(!dsp1.clone());
    } break; case 21: {
        dsp3 = dsp2 = dsp1;
        assert(dsp1.clone());
        assert(dsp1.ref_count() == 1 && dsp2.ref_count() == 2 && dsp3.ref_count() == 2);
        assert(*dsp1 == 3.14 && *dsp2 == 3.14 && *dsp3 == 3.14);
    } break; case 22: {
        dsp3 = dsp2 = dsp1;
        recordaddrs = true;
        throwBadAlloc = 1;      // first allocation throws exception
        size_t oldSize = addrs.size();
        try {
            dsp1.clone();
            assert(0);
        }
        catch (std::bad_alloc) {}
        // test for strong guarantee, no change to dsp1
        assert(*dsp1 == *dsp2 && dsp1.ref_count() == dsp2.ref_count());
        assert(addrs.size() == oldSize);
        recordaddrs = false;
        throwBadAlloc = 0;
    } break; case 23: {
        dsp3 = dsp2 = dsp1;
        recordaddrs = true;
        throwBadAlloc = 2;      // second alocation throws exception
        size_t oldSize = addrs.size();
        try {
            dsp1.clone();
            assert(0);
        }
        catch (std::bad_alloc) {}
        // test for strong guarantee, no change to dsp1
        assert(*dsp1 == *dsp2 && dsp1.ref_count() == dsp2.ref_count());
        assert(addrs.size() == oldSize);
        recordaddrs = false;
        throwBadAlloc = 0;
    } break; case 24: {
        dsp3 = dsp2 = dsp1;
        assert(*dsp1 == *dsp2 && *dsp2 == *dsp3 && *dsp1 == 3.14);
        assert(dsp1.ref_count() == dsp2.ref_count() &&
            dsp2.ref_count() == dsp3.ref_count() &&
            dsp1.ref_count() == 3);
    } break; case 25: {
        dsp3 = dsp2 = dsp1;
        dsp3 = dsp0;
        assert(*dsp1 == *dsp2 && *dsp1 == 3.14);
        assert(dsp1.ref_count() == dsp2.ref_count() &&
            dsp1.ref_count() == 2 &&
            dsp3.ref_count() == 0);
    } break; case 26: {
        // testing L-value ref constructor
        OurType* p = new OurType{ 0 };
        OurType* saved = p;
        try {
            throwBadAlloc = 1;            // next allocation throws
            smart_ptr<OurType> osp0{ p };  // throws exception
            assert(0);
        }
        catch (...) {
            assert(itemcount() == 1);
            assert(saved == p);
            throwBadAlloc = 0;
            delete p;
        }
    } break; case 27: {
        // testing R-value ref constructor
        try {
            throwBadAlloc = 2;       // second allocation throws
            // throws exception inside ctor
            smart_ptr<OurType> osp0{ new OurType{0} };
            assert(0);
        }
        catch (...) {
            assert(itemcount() == 0);
        }
        throwBadAlloc = 0;
    }
    }
}

int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed" << endl;
}
