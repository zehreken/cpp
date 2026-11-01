#include <iostream>

// Rules: no heap allocations after construction,
// and Alloc should construct the T. Think back to
// placement new. You don’t need perfect syntax, but explain your choices.
template <typename T, size_t N> class FixedPool {
  public:
    FixedPool();
    T* alloc();      // O(1), returns nullptr when full
    void free(T* p); // O(1)
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

    return 0;
}
