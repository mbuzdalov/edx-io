#include <fstream>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int n;
    long long v, xorv = 0;
    input >> n;
    for (int i = 0; i < n; ++i) {
        input >> v;
        xorv ^= v;
    }
    output << xorv << '\n';
    return 0;
}
