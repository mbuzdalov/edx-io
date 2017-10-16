#include <stdio.h>

int main() {
    int n, i;
    long long v, xor = 0;
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (fscanf(input, "%d", &n) != 1) return 1;
    for (i = 0; i < n; ++i) {
        if (fscanf(input, "%lld", &v) != 1) return 1;
        xor ^= v;
    }
    fprintf(output, "%lld\n", xor);
    fclose(input);
    fclose(output);
    return 0;
}
