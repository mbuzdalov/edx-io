#include "edx-io.h"

int main() {
    int i, n;
    long long sum = 0;
    edx_open();
    n = edx_next_i32();
    for (i = 0; i < n; ++i) {
        sum += edx_next_i32();
    }
    edx_println_i64(sum);
    edx_close();
    return 0;
}
