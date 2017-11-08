#include "edx-io.h"
#include <math.h>

int main() {
    int n, i;
    long long a, b, c, v0, v1, v2;
    edx_open();
    n = edx_next_i32();
    a = edx_next_i64();
    b = edx_next_i64();
    c = edx_next_i64();
    v0 = edx_next_i64();
    v1 = edx_next_i64();

    edx_print_i64(v0);
    edx_print_char(' ');
    edx_print_i64(v1);
    for (i = 2; i < n; ++i) {
        v2 = a * v0 + b * v1 + c;
        edx_print_char(' ');
        edx_print_double(v2 < 0 ? -sqrt((double) (-v2)) : sqrt((double) (v2)));
        v0 = v1;
        v1 = v2;
    }
    edx_println("");
    edx_close();
    return 0;
}
