#include <cmath>
#include "edx-io.hpp"

int main() {
    int n;
    long long a, b, c, v0, v1, v2;
    io >> n >> a >> b >> c >> v0 >> v1;
    io << v0 << ' ' << v1;
    for (int i = 2; i < n; ++i) {
        v2 = a * v0 + b * v1 + c;
        io << ' ' << (v2 < 0 ? -sqrt((double) (-v2)) : sqrt((double) (v2)));
        v0 = v1;
        v1 = v2;
    }
    io << '\n';
    return 0;
}
