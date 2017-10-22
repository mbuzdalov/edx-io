#include <fstream>
#include <cmath>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int n;
    long long a, b, c, v0, v1, v2;
    input >> n >> a >> b >> c >> v0 >> v1;
    output << v0 << ' ' << v1;
    output.precision(17);
    for (int i = 2; i < n; ++i) {
        v2 = a * v0 + b * v1 + c;
        output << ' ' << (v2 < 0 ? -sqrt(-v2) : sqrt(v2));
        v0 = v1;
        v1 = v2;
    }
    output << '\n';
    return 0;
}
