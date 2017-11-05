# edx-io
I/O routines for programming courses by ITMO on the edX platform.

These libraries support two courses:
* [How to Win Coding Competitions](https://courses.edx.org/courses/course-v1:ITMOx+I2CPx+3T2017/course/) at [edX](https://edx.org)
* [Алгоритмы программирования и структуры данных](https://openedu.ru/course/ITMOUniversity/PADS/) на платформе ["Открытое образование"](https://openedu.ru)

The libraries are enough to read and write all types of data, which are necessary to solve all problems in these courses. Please file a bug report if you suspect that it is not true.

Please **never** submit the sources of these libraries along with your code. We have the latest versions of the libraries available in the testing system.

## Library for Java, Scala and Kotlin

We have a single library for all languages based on Java Virtual Machine.

[Go to the library](https://github.com/mbuzdalov/edx-io/tree/master/src/jvm)

Download files:
* [EdxIO.java](https://raw.githubusercontent.com/mbuzdalov/edx-io/master/src/jvm/mooc/EdxIO.java). Note that it should be in the package called `mooc`.

## Library for C

This is the library for C.

[Go to the library](https://github.com/mbuzdalov/edx-io/tree/master/src/c)

Download files:
* [edx-io.h](https://raw.githubusercontent.com/mbuzdalov/edx-io/master/src/c/edx-io.h)
* [edx-io.c](https://raw.githubusercontent.com/mbuzdalov/edx-io/master/src/c/edx-io.c)

## Library for C++

This is the library for C++, which is a thin wrapper of the library for C.

[Go to the library](https://github.com/mbuzdalov/edx-io/tree/master/src/c++)

Download files:
* [edx-io.h](https://raw.githubusercontent.com/mbuzdalov/edx-io/master/src/c/edx-io.h)
* [edx-io.c](https://raw.githubusercontent.com/mbuzdalov/edx-io/master/src/c/edx-io.c)
* [edx-io.hpp](https://raw.githubusercontent.com/mbuzdalov/edx-io/master/src/c++/edx-io.hpp)
* [edx-io.cpp](https://raw.githubusercontent.com/mbuzdalov/edx-io/master/src/c++/edx-io.cpp)

Note: Visual C++ may be misleaded by the co-existing `edx-io.c` and `edx-io.cpp`, which will share the same object name. 
To make it happy, rename `edx-io.cpp` to `edx-io-plus.cpp`, for instance. Some versions would also miss the `edx-io.c` for linking,
in which case it suffices to rename `edx-io.c` to `edx-io.cpp`.

## Library for CPython and PyPy

This is the library for Python implementations (except Cython).

[Go to the library](https://github.com/mbuzdalov/edx-io/tree/master/src/python)

Download files:
* [edx_io.py](https://raw.githubusercontent.com/mbuzdalov/edx-io/master/src/python/edx_io.py)
