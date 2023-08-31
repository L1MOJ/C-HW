#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <ostream>

template <typename T>
class UniquePtr 
{

public:
    UniquePtr(T *p): u_p(p) {}

    UniquePtr() {
        u_p = nullptr;
    }

    UniquePtr(const UniquePtr& ptr) = delete;

    ~UniquePtr() {
        delete(u_p);
        u_p = nullptr;
    }
    T* get() const {
        return u_p;
    }

    UniquePtr& operator=(const UniquePtr& ptr) = delete;

    T& operator*() const {
        return *(u_p);
    }

    T* operator->() const {
        return u_p;
    }

    void reset() {
        u_p = nullptr;
    }

    void reset(T *p) {
        delete(u_p);
        u_p = p;
    }

    operator bool() const {
        return u_p != nullptr;
    }

    T* release() {
        T* temp = u_p;
        u_p = nullptr;
        return temp;
    }
private:
    T* u_p;
};

template <typename T>
T* make_unique(const T& i) {
    return new T(i);
}


#endif //UNIQUE_PTR