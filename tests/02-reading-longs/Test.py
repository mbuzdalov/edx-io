from edx_io import edx_io
from functools import reduce

with edx_io() as io:
    n = io.next_int()
    res = reduce(lambda x, y: x ^ y, map(int, io.all_tokens()))
    io.writeln(res)
