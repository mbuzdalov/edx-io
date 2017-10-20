#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edx-io.h"

FILE *inf = NULL, *ouf = NULL;

char number_buffer[256];

int int_to_buffer(int value, int pos);
int long_long_to_buffer(long long value, int pos);

void edx_open() {
    inf = fopen("input.txt", "rt");
    if (inf == NULL) {
        perror("Cannot open file 'input.txt' for reading");
        exit(1);
    }
    ouf = fopen("output.txt", "wt");
    if (ouf == NULL) {
        perror("Cannot open file 'output.txt' for writing");
        exit(1);
    }
}

void edx_close() {
    fclose(inf);
    fclose(ouf);
}

int edx_next_i32() {
    int rv;
    if (fscanf(inf, "%d", &rv) == 1) {
        return rv;
    } else {
        fputs("edx_next_i32: Unable to parse value\n", stderr);
        exit(1);
        return 0;
    }
}

long long edx_next_i64() {
    long long rv;
    if (fscanf(inf, "%lld", &rv) == 1) {
        return rv;
    } else {
        fputs("edx_next_i64: Unable to parse value\n", stderr);
        exit(1);
        return 0;
    }
}

double edx_next_double() {
    double rv;
    if (fscanf(inf, "%lf", &rv) == 1) {
        return rv;
    } else {
        fputs("edx_next_double: Unable to parse value\n", stderr);
        exit(1);
        return 0;
    }
}

int next_bounded_impl(char *dest, int capacity, int skip_initial_ws) {
    int i, curr;
    if (capacity == 0) {
        return 0;
    }
    for (i = 0; i + 1 < capacity; ++i) {
        curr = fgetc(inf);
        if (i == 0 && skip_initial_ws) {
            while (curr <= ' ' && curr != EOF) {
                curr = fgetc(inf);
            }
        }
        if (curr == EOF || curr <= ' ') {
            dest[i] = '\0';
            return i;
        }
        dest[i] = (char) (curr);
    }
    dest[capacity - 1] = '\0';
    return capacity - 1;
}

int edx_next_bounded(char *dest, int capacity) {
    return next_bounded_impl(dest, capacity, 1);
}

char *edx_next_unbounded() {
    char stackbuf[16];
    int scan_size = next_bounded_impl(stackbuf, 16, 1);
    char *rv;
    if (scan_size < 15) {
        // don't forget to fit the '\0'
        rv = (char*) malloc(sizeof(char) * (scan_size + 1));
        memcpy(rv, stackbuf, sizeof(char) * (scan_size + 1));
        return rv;
    } else {
        int rv_size = (scan_size + 1) * 2;
        rv = (char*) malloc(sizeof(char) * rv_size);
        // not copying '\0'
        memcpy(rv, stackbuf, sizeof(char) * scan_size);
        while (1) {
            scan_size = scan_size + next_bounded_impl(rv + scan_size, rv_size - scan_size, 0);
            if (scan_size + 1 < rv_size) {
                return (char*) realloc(rv, scan_size + 1);
            }
            rv_size *= 2;
            rv = (char*) realloc(rv, rv_size);
        }
    }
}

int edx_printf(char *fmt_string, ...) {
    int rv;
    va_list args;
    va_start(args, fmt_string);
    rv = vfprintf(ouf, fmt_string, args);
    va_end(args);
    return rv;
}

void edx_print(char *string) {
    fputs(string, ouf);
}

void edx_println(char *string) {
    fputs(string, ouf);
    fputc('\n', ouf);
}

void edx_print_char(char value) {
    fputc(value, ouf);
}

void edx_println_char(char value) {
    fputc(value, ouf);
    fputc('\n', ouf);
}

void edx_print_i32(int value) {
#ifdef PRIMITIVES_THROUGH_PRINTF
    fprintf(ouf, "%d", value);
#else
    if (value == -2147483648) {
        edx_print("-2147483648");
    } else {
        if (value < 0) {
            edx_print_char('-');
            value = -value;
        }
        int pos = int_to_buffer(value, 255);
        edx_print(number_buffer + pos);
    }
#endif
}

void edx_println_i32(int value) {
    edx_print_i32(value);
    fputc('\n', ouf);
}

void edx_print_i64(long long value) {
#ifdef PRIMITIVES_THROUGH_PRINTF
    fprintf(ouf, "%lld", value);
#else
    if (value == 1LL << 63) {
        edx_print("-9223372036854775808");
    } else {
        if (value < 0) {
            edx_print_char('-');
            value = -value;
        }
        int pos = long_long_to_buffer(value, 255);
        edx_print(number_buffer + pos);
    }
#endif
}

void edx_println_i64(long long value) {
    edx_print_i64(value);
    fputc('\n', ouf);
}

void edx_print_double(double value) {
    fprintf(ouf, "%.17lg", value);
}

void edx_println_double(double value) {
    edx_print_double(value);
    fputc('\n', ouf);
}

char digit_tens[] = {
        48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
        49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
        50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
        51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
        52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
        53, 53, 53, 53, 53, 53, 53, 53, 53, 53,
        54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
        55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
        56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
        57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
};

char digit_ones[] = {
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
};

int int_to_buffer(int value, int pos) {
    while (value >= 65536) {
        int q = value / 100;
        int r = value - ((q << 6) + (q << 5) + (q << 2));
        value = q;
        number_buffer[--pos] = digit_ones[r];
        number_buffer[--pos] = digit_tens[r];
    }
    while (1) {
        int q = (int) ((unsigned) (value * 52429) >> (16+3));
        int r = value - ((q << 3) + (q << 1));
        number_buffer[--pos] = digit_ones[r];
        value = q;
        if (value == 0) {
            break;
        }
    }
    return pos;
}

int long_long_to_buffer(long long value, int pos) {
    while (value > 2147483647LL) {
        long long q = value / 100;
        int r = (int) (value - ((q << 6) + (q << 5) + (q << 2)));
        value = q;
        number_buffer[--pos] = digit_ones[r];
        number_buffer[--pos] = digit_tens[r];
    }
    return int_to_buffer((int) value, pos);
}
