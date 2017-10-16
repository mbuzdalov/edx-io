#include <stdio.h>
#include <math.h>

int main() {
    int n, i;
    long long a, b, c, v0, v1, v2;
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (fscanf(input, "%d%lld%lld%lld%lld%lld", &n, &a, &b, &c, &v0, &v1) != 6) {
        return 1;
    }
    fprintf(output, "%lld %lld", v0, v1);
    for (i = 2; i < n; ++i) {
        v2 = a * v0 + b * v1 + c;
        fprintf(output, " %.17lf", v2 < 0 ? -sqrt(-v2) : sqrt(v2));
        v0 = v1;
        v1 = v2;
    }
    fputs("\n", output);
    fclose(output);
    fclose(input);
    return 0;
}
