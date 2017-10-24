import inspect, io, mmap, platform

class edx_io:
    def create_tokenizer(self):
        for line in iter(self.mm.readline, b""):
            for token in line.split():
                yield token

    def __enter__(self):
        self.inf = open("input.txt", "rt", 1)
        self.mm = mmap.mmap(self.inf.fileno(), 0, access = mmap.ACCESS_READ)
        self.ouf = io.StringIO()
        self.tokens = self.create_tokenizer()
        self.is_cpython = platform.python_implementation() == "CPython"
        return self

    def __exit__(self, type, value, traceback):
        self.mm.close()
        self.inf.close()
        ouf = open("output.txt", "wt", 1)
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
        if isinstance(arg, str):
            self.ouf.write(arg)
        elif isinstance(arg, bytes):
            self.ouf.write(arg.decode())
        elif hasattr(arg, "__iter__"):
            if self.is_cpython:
                self.ouf.write(" ".join(str(i) for i in arg))
            else:
                sep = ""
                for i in arg:
                    self.ouf.write(sep)
                    self.ouf.write(str(i))
                    sep = " "
        else:
            self.ouf.write(str(arg))

    def writeln(self, arg):
        self.write(arg)
        self.write("\n")
