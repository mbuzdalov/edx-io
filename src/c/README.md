# I/O for C

This library provides a set of methods for efficient reading and writing necessary types of data:

## Opening and closing

* `void edx_open()` -- opens the files `input.txt` for reading and `output.txt` for writing, prepares the rest of the library to work.
* `void edx_close()` -- flushes the streams and closes the files. Should be always called at the end.

## High-level input

* `int edx_next_i32()` -- reads an `int`.
* `long long edx_next_i64()` -- reads a `long long`, a signed 64-bit integer.
* `double edx_next_double()` -- reads a `double`.
* `char *next_unbounded()` -- reads a non-whitespace token and returns it. **You must free the returned pointer when you no longer need it!**
* `int next_bounded(char *dest, int max_length)` -- reads a non-whitespace token of length at most `max_length - 1` to the buffer pointed by `dest`, puts a zero character after it, and 
returns 
the number of characters read. If the token exceeds the maximum length, the rest of it remains unread, so the subsequent calls can read it. 

## High-level output

* `void edx_print_i32(int)` -- writes an `int`.
* `void edx_println_i32(int)` -- writes an `int` and puts a newline.
* `void edx_print_i64(long long)` -- writes a `long long`.
* `void edx_println_i64(long long)` -- writes a `long long` and puts a newline.
* `void edx_print_i64(double)` -- writes a `double`.
* `void edx_println_i64(double)` -- writes a `double` and puts a newline.
* `void edx_print_i64(char)` -- writes a `char`.
* `void edx_println_i64(char)` -- writes a `char` and puts a newline.
* `void edx_print_i64(char*)` -- writes a string given as `char*`.
* `void edx_println_i64(char*)` -- writes a string given as `char*` and puts a newline.
* `int edx_printf(char *fmt_string, ...)` -- writes a variable number of arguments using the format string in the manner of `printf`, returns the number of entries written.

## Example solution of the A+B problem

```
#include "edx-io.h"

int main() {
    edx_open();
    edx_println_i32(edx_next_i32() + edx_next_i32());
    edx_close();
    return 0;
}
```
