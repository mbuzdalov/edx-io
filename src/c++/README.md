# I/O for C++

This library provides a class with a set of methods for efficient reading and writing necessary types of data.

This library is a thin wrapper around the C library, so you need to also download the files of the C library:

* [edx-io.h](https://raw.githubusercontent.com/mbuzdalov/edx-io/master/src/c/edx-io.h)
* [edx-io.c](https://raw.githubusercontent.com/mbuzdalov/edx-io/master/src/c/edx-io.c)

**Note for Visual C++ users:** you may need to change all files with `*.c` extensions to `*.cpp` extensions, and make sure you have different
names for both `*.cpp` files: for example, `edx-io.cpp` and `edx-io-plus.cpp`.

## Globals

* `struct edx_io` -- a class containing a constructor (which opens the files), a destructor (which closes them), and the following methods:
* `edx_io io` -- a global variable of type `edx_io` which is pre-initialized for you.

## Input

* `edx_io const &operator >> (int &) const;` -- reads the next `int`.
* `edx_io const &operator >> (long long &) const;` -- reads the next `long long`.
* `edx_io const &operator >> (double &) const;` -- reads the next `double`.
* `edx_io const &operator >> (std::string &) const;` -- reads the next non-whitespace token and puts it into the given `std::string`.
* `edx_io const &operator >> (char &) const;` -- reads the next non-whitespace `char`.

## Output

* `edx_io const &operator << (int) const;` -- writes an `int`.
* `edx_io const &operator << (unsigned) const;` -- writes an `unsigned int`.
* `edx_io const &operator << (long long) const;` -- writes a `long long`.
* `edx_io const &operator << (unsigned long long) const;` -- writes an `unsigned long long`.
* `edx_io const &operator << (double) const;` -- writes a `double`.
* `edx_io const &operator << (std::string const &) const;` -- writes an `std::string`.
* `edx_io const &operator << (char const *) const;` -- writes a null-terminated C-string.
* `edx_io const &operator << (char) const;` -- writes a single character.


## Example solution of the A+B problem

```
#include "edx-io.hpp"

int main() {
    int a, b;
    io >> a >> b;
    io << a + b << '\n';
    return 0;
}
```
