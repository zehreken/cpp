#include "ring_buffer.h"
#include <bitset>
#include <iostream>

int main() {
    RingBuffer<int> rb(128);

    std::cout << rb.empty() << " " << rb.capacity() << std::endl;

    size_t h = 12;
    size_t N = 16;
    size_t w = h & (N - 1);

    std::cout << std::bitset<8>(h) << " " << std::bitset<8>(N - 1) << " "
              << std::bitset<8>(w) << std::endl;
    return 0;
}