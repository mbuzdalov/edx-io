from functools import reduce

with open("input.txt", "rt") as inf, open("output.txt", "wt") as ouf:
    n = int(inf.readline())
    result = reduce(lambda x, y: x ^ y, (int(v) for line in inf.readlines() for v in line.split()))
    ouf.write(str(result) + "\n")
