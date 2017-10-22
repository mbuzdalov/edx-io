#include <iomanip>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int n;
    double v, sum = 0;
    input >> n;
    for (int i = 0; i < n; ++i) {
        input >> v;
        sum += v;
    }
    output << std::setprecision(17) << sum << '\n';
    return 0;
}
