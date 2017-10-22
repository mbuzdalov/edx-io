#include "edx-io.hpp"

int main() {
    int n;
    long long xor = 0, v;
    io >> n;
    for (int i = 0; i < n; ++i) {
        io >> v;
        xor ^= v;
    }
    io << xor << '\n';
    return 0;
}
