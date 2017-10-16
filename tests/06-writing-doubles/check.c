#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *answer = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "r");
    double va, vo;
    while (1) {
        if (fscanf(answer, "%lf", &va) != 1) {
            // All numbers are read.
            printf("OK\n");
            return 0;
        }
        if (fscanf(output, "%lf", &vo) != 1) {
            fprintf(stderr, "FAILED: Cannot read a double from '%s'\n", argv[2]);
            return 1;
        }
        if (va != vo) {
            printf("FAILED: expected %lf, found %lf\n", va, vo);
            return 1;
        }
    }
}
