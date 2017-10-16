#include "edx-io.h"

int main() {
    int i, n;
    long long xor = 0;
    edx_open();
    n = edx_next_i32();
    for (i = 0; i < n; ++i) {
        xor ^= edx_next_i64();
    }
    edx_println_i64(xor);
    edx_close();
    return 0;
}
