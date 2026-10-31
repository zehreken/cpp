#include "ring_buffer.h"
#include <bitset>
#include <iostream>

int main() {
    RingBuffer<int> rb(128);

    std::cout << rb.empty() << " " << rb.capacity() << std::endl;

    return 0;
}