# I/O for Python

This library provides a set of methods for efficient reading and writing necessary types of data:

## Modules and classes

The Python module is called `edx_io`. The class containing all I/O routines is also called `edx_io`.

For performance reasons, I/O is done at byte level, not at character level. Additionally, input is done
using memory mapping, which has quite a large impact on performance especially for PyPy.

## Input

* `next_int()` -- reads an `int`.
* `next_float()` -- reads a `float`.
* `next_token()` -- reads a non-whitespace token and returns it as `bytes`.
* `all_tokens()` -- returns an iterable over all non-whitespace tokens which have not yet been read.

## Output

* `write(a)` -- writes the argument. If it is an iterable, then all contained values are written and separated by single whitespace characters.
* `writeln(a)` -- writes the argument and puts a newline.

## Example solution of the A+B problem

```
from edx_io import edx_io

with edx_io() as io:
    io.writeln(io.next_int() + io.next_int())
```
