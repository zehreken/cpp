#include <iostream>
#include <stack>

// Rules: no heap allocations after construction,
// and Alloc should construct the T. Think back to
// placement new. You don’t need perfect syntax, but explain your choices.
template <typename T, size_t N> class FixedPool {
  public:
    FixedPool() : buf_(std::make_unique<std::byte[]>(sizeof(T) * N)) {
        for (size_t i = 0; i < N; ++i) {
            frees_.push(i);
        }
    }
    T* alloc() {
        if (frees_.empty())
            return nullptr;
        size_t index = frees_.top();
        frees_.pop();
        return static_cast<T*>(&(buf_[index * sizeof(T)]));
    } // O(1), returns nullptr when full
    void free(T* p) {
        size_t index = (p - buf_) / sizeof(T);
        frees_.push(index);
    }; // O(1)
  private:
    std::unique_ptr<std::byte[]> buf_;
    std::stack<size_t> frees_;
};

class Foo {
  public:
    Foo() : a_(5), b_(42) {};
    const int a_;
    int b_;
};

void bump_r(int& x) { x++; }

// void bump_p(int* x) { ++*x; } // works
// void bump_p(int* x) { *x++; } // does not work
// void bump_p(int* x) { *x = *x + 1; } // works
void bump_p(int* x) { // works
    int a = *x;
    *x = a + 1;
}

int main() {
    std::cout << "fixed_pool" << std::endl;

    {
        Foo a;
        std::cout << a.a_ << " size(Foo): " << sizeof(Foo)
                  << " align(Foo): " << alignof(Foo) << std::endl;
    }

    {
        int a = 0;
        int* p_a = &a;
        std::cout << a << " " << p_a << std::endl;
    }

    {
        int a = 42;
        std::cout << a << std::endl;
        bump_r(a);
        std::cout << a << std::endl;
        bump_p(&a);
        std::cout << a << std::endl;
    }

    {
        class T {
            int a_;
            int b_;
        };
        const size_t n = 16;
        std::unique_ptr<std::byte[]> buf =
            std::make_unique<std::byte[]>(n * sizeof(T));
        std::cout << "buf: " << buf << " sizeof(T): " << sizeof(T) << std::endl;

        T* t = (T*)(buf.get() + sizeof(T) * 8);

        std::cout << t << " " << buf.get() << std::endl;
    }

    return 0;
}
