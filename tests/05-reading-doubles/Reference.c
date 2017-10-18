#include <stdio.h>

int main() {
    int n, i;
    double v, sum = 0;
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (fscanf(input, "%d", &n) != 1) return 1;
    for (i = 0; i < n; ++i) {
        if (fscanf(input, "%lf", &v) != 1) return 1;
        sum += v;
    }
    fprintf(output, "%.17lg\n", sum);
    fclose(input);
    fclose(output);
    return 0;
}
