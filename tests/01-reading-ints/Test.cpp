#include "edx-io.hpp"

int main() {
    int n, v;
    long long sum = 0;
    io >> n;
    for (int i = 0; i < n; ++i) {
        io >> v;
        sum += v;
    }
    io << sum << '\n';
    return 0;
}
