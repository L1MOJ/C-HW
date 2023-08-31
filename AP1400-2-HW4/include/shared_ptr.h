#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>

class SharedPtr 
{
public:
    SharedPtr(T *p): s_p(p) {
        cnt = new size_t(1);
    }

    SharedPtr() {
        s_p = nullptr;
        cnt = new size_t(0);
    }

    SharedPtr(const SharedPtr& ptr): s_p(ptr.s_p), cnt(ptr.cnt) {
        if(cnt) {
            (*cnt)++;
        }
    }

    ~SharedPtr() {
        (*cnt)--;
        if (*cnt == 0) {
            delete(s_p);
        }
        s_p = nullptr;
    }

    SharedPtr& operator= (const SharedPtr& ptr) {
        if (&ptr != this) {
            cnt = ptr.cnt;
            delete(this->s_p);
            s_p = ptr.s_p;
            (*cnt)++;
        }
        return *this;

    }

    operator bool() {
        return s_p != nullptr;
    }

    void reset() {
        if (s_p != nullptr) {
            delete(s_p);
        }
        s_p = nullptr;
        *cnt = 0;
    }

    void reset(T* p) {
        if (s_p != nullptr) {
            delete(s_p);
        }
        s_p = p;
        cnt = new size_t(1);
    }

    int use_count() {
        return *cnt;
    }

    T* operator->() const {
        return s_p;
    }

    T& operator*() const {
        return *(s_p);
    }

    T* get() const {
        return s_p;
    }

private:
    T* s_p;
    size_t* cnt;
};


template <typename T>
T* make_shared(const T& value) {
    return new T(value);
}
#endif //SHARED_PTR