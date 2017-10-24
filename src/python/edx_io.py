import inspect, io, mmap, platform

def convert_to_bytes(arg):
    if isinstance(arg, bytes):
        return arg
    elif isinstance(arg, str):
        return arg.encode("ascii")
    elif hasattr(arg, "__iter__"):
        return b" ".join(map(convert_to_bytes, arg))
    else:
        return str(arg).encode("ascii")

class edx_io:
    def create_tokenizer(self):
        for line in iter(self.mm.readline, b""):
            for token in line.split():
                yield token

    def __enter__(self):
        self.is_cpython = platform.python_implementation() == "CPython"
        self.inf = open("input.txt", "rb", 1)
        self.mm = mmap.mmap(self.inf.fileno(), 0, access = mmap.ACCESS_READ)
        if self.is_cpython:
            self.ouf = open("output.txt", "wb", 1)
        else:
            self.ouf = io.BytesIO()
        self.tokens = self.create_tokenizer()
        return self

    def __exit__(self, type, value, traceback):
        self.mm.close()
        self.inf.close()
        if self.is_cpython:
            self.ouf.close()
        else:
            ouf = open("output.txt", "wb", 1)
            ouf.write(self.ouf.getvalue())
            ouf.close()
            self.ouf.close()

    def next_int(self):
        return int(self.next_token())

    def next_float(self):
        return float(self.next_token())

    def next_token(self):
        return self.tokens.__next__()

    def all_tokens(self):
        return self.tokens

    def write(self, arg):
        self.ouf.write(convert_to_bytes(arg))

    def writeln(self, arg):
        self.write(arg)
        self.ouf.write(b"\n")
