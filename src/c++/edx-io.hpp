#ifndef __EDX_IO_HPP__
#define __EDX_IO_HPP__

#include <string>

/**
 * This class is actually a wrapper atop static I/O routines,
 * so no matter how many instances you create, they will route the I/O
 * to the same backend.
 */
struct edx_io {
    // Constructor and destructor
    edx_io();
    ~edx_io();
    // Input
    edx_io const &operator >> (int &) const;
    edx_io const &operator >> (long long &) const;
    edx_io const &operator >> (double &) const;
    edx_io const &operator >> (std::string &) const;
    edx_io const &operator >> (char &) const;
    // Output
    edx_io const &operator << (int) const;
    edx_io const &operator << (unsigned) const;
    edx_io const &operator << (long long) const;
    edx_io const &operator << (unsigned long long) const;
    edx_io const &operator << (double) const;
    edx_io const &operator << (std::string const &) const;
    edx_io const &operator << (char const *) const;
    edx_io const &operator << (char) const;
};

extern edx_io io;

#endif
