#include <iostream>
#include <string>

#include "imp_vector.h"
#include "vector.h"

int main() {
    Vector<std::string> v(0);
    for (int i = 0; i < 1000; i++) {
        std::string s = std::string(40, 'x') +
                        std::to_string(i); // long enough to heap-allocate
        v.push_back(s);
    }

    std::cout << v.size() << ' ' << v.capacity() << std::endl;
    return 0;
}
