#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edx-io.h"

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"
#define INPUT_FILE_OPEN_ERROR "Cannot open file '" INPUT_FILE_NAME "' for reading"
#define OUTPUT_FILE_OPEN_ERROR "Cannot open file '" OUTPUT_FILE_NAME "' for writing"

#ifdef EDX_IO_INPUT_MMAP
    char *mmap_buf;
    char *mmap_end;
    char *mmap_ptr;

    #ifdef _WIN32
        #include <windows.h>

        void print_windows_error_and_exit() {
            DWORD err = GetLastError();
            LPTSTR msg;
            DWORD symbol_cnt = FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                0, // the optional message
                err,
                0, // the language: 0 means "guess on your own"
                (LPTSTR) &msg,
                0, // nSize which is ignored
                NULL // varargs which are not used
            );
            if (symbol_cnt == 0) {
                print_windows_error_and_exit();
            }
            fputs(msg, stderr);
            HeapFree(GetProcessHeap(), 0, msg);
            exit(1);
        }

        HANDLE input_file_handle;
        HANDLE mapping;
        LARGE_INTEGER input_file_size;

        void edx_open_input() {
            input_file_handle = CreateFileA(INPUT_FILE_NAME, GENERIC_READ,
                    FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (input_file_handle == INVALID_HANDLE_VALUE) {
                print_windows_error_and_exit();
            }
            if (!GetFileSizeEx(input_file_handle, &input_file_size)) {
                print_windows_error_and_exit();
            }
            mapping = CreateFileMapping(input_file_handle, NULL, PAGE_READONLY,
                    input_file_size.HighPart, input_file_size.LowPart, NULL);
            if (mapping == INVALID_HANDLE_VALUE) {
                print_windows_error_and_exit();
            }
            mmap_buf = (char*) (MapViewOfFile(mapping, FILE_MAP_READ, 0, 0,
                    (SIZE_T) input_file_size.QuadPart));
            if (!mmap_buf) {
                print_windows_error_and_exit();
            }
            mmap_ptr = mmap_buf;
            mmap_end = mmap_buf + input_file_size.QuadPart;
        }

        void edx_close_input() {
            UnmapViewOfFile(mmap_buf);
            CloseHandle(mapping);
            CloseHandle(input_file_handle);
        }
    #else
        #include <fcntl.h>
        #include <sys/mman.h>
        #include <sys/stat.h>
        #include <sys/types.h>
        #include <unistd.h>

        int input_file_descriptor;

        void edx_open_input() {
            input_file_descriptor = open(INPUT_FILE_NAME, O_RDONLY);
            if (input_file_descriptor != -1) {
                struct stat fstat_buffer;
                if (fstat(input_file_descriptor, &fstat_buffer) != -1) {
                    int mmap_size = fstat_buffer.st_size;
                    mmap_buf = (char*) (mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE,
                            input_file_descriptor, 0));
                    if (mmap_buf != MAP_FAILED) {
                        if (madvise(mmap_buf, mmap_size, MADV_SEQUENTIAL) != -1) {
                            mmap_end = mmap_buf + mmap_size;
                            mmap_ptr = mmap_buf;
                            return;
                        }
                    }
                }
            }
            perror(INPUT_FILE_OPEN_ERROR);
            exit(1);
        }

        void edx_close_input() {
            munmap(mmap_buf, mmap_end - mmap_buf);
            close(input_file_descriptor);
        }
    #endif

    void skip_whitespace() {
        while (mmap_ptr < mmap_end && *mmap_ptr <= ' ') {
            ++mmap_ptr;
        }
    }

    char *copy_string_contents(char *source, int length) {
        char *rv = (char*) (malloc(sizeof(char) * (length + 1)));
        memcpy(rv, source, sizeof(char) * length);
        rv[length] = 0;
        return rv;
    }

    char *consume_token(int *copy_was_made, int *length) {
        char *rv;
        int size;
        skip_whitespace();
        rv = mmap_ptr;
        while (mmap_ptr < mmap_end && *mmap_ptr > ' ') {
            ++mmap_ptr;
        }
        size = mmap_ptr - rv;
        if (length) *length = size;
        if (mmap_ptr == mmap_end) {
            // We cannot write an extra '\0' after the token,
            // since it will be outside the mapped region
            if (copy_was_made) *copy_was_made = 1;
            return copy_string_contents(rv, size);
        } else {
            // We can write an extra '\0' after the token.
            // For this, we used the private mapping and R/W pages.
            if (copy_was_made) *copy_was_made = 0;
            *mmap_ptr++ = 0;
            return rv;
        }
    }

    void check_erange(char *message) {
        if (errno == ERANGE) {
            perror(message);
            exit(1);
        }
    }

    int i32_impl_safe(int value, int add, int is_negative) {
        if (value < 214748364) {
            return 1;
        }
        if (value > 214748364) {
            return 0;
        }
        return is_negative ? add <= 8 : add < 8;
    }

    int i64_impl_safe(int value, int add, int is_negative) {
        if (value < 922337203685477580LL) {
            return 1;
        }
        if (value > 922337203685477580LL) {
            return 0;
        }
        return is_negative ? add <= 8 : add < 8;
    }

    int edx_next_i32() {
        int is_negative = 0, value = 0, count_digits = 0, add;
        char symbol;
        skip_whitespace();
        if (mmap_ptr < mmap_end && *mmap_ptr == '-') {
            is_negative = 1;
            ++mmap_ptr;
        }
        while (mmap_ptr < mmap_end) {
            symbol = *mmap_ptr;
            if ('0' <= symbol && symbol <= '9') {
                ++count_digits;
                ++mmap_ptr;
                add = symbol - '0';
                if (i32_impl_safe(value, add, is_negative)) {
                    value = value * 10 + add;
                } else {
                    fputs("[edx_next_i32] number too large", stderr);
                }
            } else {
                if (count_digits == 0) {
                    fputs("[edx_next_i32] incomplete number", stderr);
                } else {
                    return is_negative ? -value : value;
                }
            }
        }
        fputs("[edx_next_i32] Unexpected end-of-file", stderr);
        exit(1);
        return 0;
    }

    long long edx_next_i64() {
        int is_negative = 0, count_digits = 0, add;
        long long value = 0;
        char symbol;
        skip_whitespace();
        if (mmap_ptr < mmap_end && *mmap_ptr == '-') {
            is_negative = 1;
            ++mmap_ptr;
        }
        while (mmap_ptr < mmap_end) {
            symbol = *mmap_ptr;
            if ('0' <= symbol && symbol <= '9') {
                ++count_digits;
                ++mmap_ptr;
                add = symbol - '0';
                if (i64_impl_safe(value, add, is_negative)) {
                    value = value * 10 + add;
                } else {
                    fputs("[edx_next_i64] number too large", stderr);
                }
            } else {
                if (count_digits == 0) {
                    fputs("[edx_next_i64] incomplete number", stderr);
                } else {
                    return is_negative ? -value : value;
                }
            }
        }
        fputs("[edx_next_i64] Unexpected end-of-file", stderr);
        exit(1);
        return 0;
    }

    double edx_next_double() {
        int copy_was_made;
        char *token = consume_token(&copy_was_made, NULL);
        double rv = strtod(token, NULL);
        check_erange("Error while running edx_next_double");
        if (copy_was_made) {
            free(token);
        }
        return rv;
    }

    int edx_next_bounded(char *dest, int capacity) {
        skip_whitespace();
        int length_plus_one = 1;
        while (length_plus_one < capacity
                && mmap_ptr < mmap_end
                && *mmap_ptr > ' ') {
            *dest++ = *mmap_ptr++;
            ++length_plus_one;
        }
        *dest = 0;
        return length_plus_one - 1;
    }

    char *edx_next_unbounded() {
        int copy_was_made;
        int length;
        char *token = consume_token(&copy_was_made, &length);
        if (copy_was_made) {
            return token;
        } else {
            return copy_string_contents(token, length);
        }
    }
#else
    FILE *inf = NULL;

    void edx_open_input() {
        inf = fopen(INPUT_FILE_NAME, "rt");
        if (inf == NULL) {
            perror(INPUT_FILE_OPEN_ERROR);
            exit(1);
        }
    }

    void edx_close_input() {
        fclose(inf);
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
#endif

FILE *ouf = NULL;
char number_buffer[256];
int int_to_buffer(int value, int pos);
int long_long_to_buffer(long long value, int pos);

void edx_open() {
    edx_open_input();
    ouf = fopen(OUTPUT_FILE_NAME, "wt");
    if (ouf == NULL) {
        perror(OUTPUT_FILE_OPEN_ERROR);
        exit(1);
    }
}

void edx_close() {
    edx_close_input();
    fclose(ouf);
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
