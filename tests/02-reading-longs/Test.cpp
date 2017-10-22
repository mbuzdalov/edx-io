#include "edx-io.hpp"

int main() {
    int n;
    long long xorv = 0, v;
    io >> n;
    for (int i = 0; i < n; ++i) {
        io >> v;
        xorv ^= v;
    }
    io << xorv << '\n';
    return 0;
}
