#include <fstream>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int n, v;
    long long sum = 0;

    input >> n;
    for (int i = 0; i < n; ++i) {
        input >> v;
        sum += v;
    }
    output << sum << '\n';
    return 0;
}
