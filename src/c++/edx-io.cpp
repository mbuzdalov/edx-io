#include "edx-io.h"
#include "edx-io.hpp"
#include <cstdlib>

char string_input_buffer[8192];

edx_io io;

edx_io::edx_io() {
    edx_open();
}

edx_io::~edx_io() {
    edx_close();
}

// Input

edx_io const &edx_io::operator >> (int &value) const {
    value = edx_next_i32();
    return *this;
}

edx_io const &edx_io::operator >> (long long &value) const {
    value = edx_next_i64();
    return *this;
}

edx_io const &edx_io::operator >> (double &value) const {
    value = edx_next_double();
    return *this;
}

edx_io const &edx_io::operator >> (std::string &value) const {
    value.resize(0);
    int length;
    int must_be_freed;
    char *str = edx_unsafe_read_token(&length, NULL, &must_be_freed);
    value.append(str, length);
    if (must_be_freed) {
        free(str);
    }
    return *this;
}

edx_io const &edx_io::operator >> (char &value) const {
    char tmp[2];
    edx_next_bounded(tmp, 2);
    value = tmp[0];
    return *this;
}

// Output

edx_io const &edx_io::operator << (int value) const {
    edx_print_i32(value);
    return *this;
}

edx_io const &edx_io::operator << (long long value) const {
    edx_print_i64(value);
    return *this;
}

edx_io const &edx_io::operator << (double value) const {
    edx_print_double(value);
    return *this;
}

edx_io const &edx_io::operator << (std::string const &value) const {
    edx_print(value.c_str());
    return *this;
}

edx_io const &edx_io::operator << (char const *value) const {
    edx_print(value);
    return *this;
}

edx_io const &edx_io::operator << (char value) const {
    edx_print_char(value);
    return *this;
}
