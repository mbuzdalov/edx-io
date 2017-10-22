#include "edx-io.hpp"

int main() {
    int n;
    double sum = 0, v;
    io >> n;
    for (int i = 0; i < n; ++i) {
        io >> v;
        sum += v;
    }
    io << sum << '\n';
    return 0;
}
