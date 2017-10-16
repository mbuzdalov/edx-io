#include "edx-io.h"

int main() {
    int i, n;
    double sum = 0;
    edx_open();
    n = edx_next_i32();
    for (i = 0; i < n; ++i) {
        sum += edx_next_double();
    }
    edx_println_double(sum);
    edx_close();
    return 0;
}
