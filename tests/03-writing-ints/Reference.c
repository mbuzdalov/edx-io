#include <stdio.h>

int main() {
    int n, i, a, b, c, v0, v1, v2;
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (fscanf(input, "%d%d%d%d%d%d", &n, &a, &b, &c, &v0, &v1) != 6) {
        return 1;
    }
    fprintf(output, "%d %d", v0, v1);
    for (i = 2; i < n; ++i) {
        v2 = a * v0 + b * v1 + c;
        fprintf(output, " %d", v2);
        v0 = v1;
        v1 = v2;
    }
    fputs("\n", output);
    fclose(output);
    fclose(input);
    return 0;
}
