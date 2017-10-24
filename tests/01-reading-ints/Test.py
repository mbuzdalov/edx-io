from edx_io import edx_io

with edx_io() as io:
    n = io.next_int()
    res = sum(map(int, io.all_tokens()))
    io.writeln(res)
