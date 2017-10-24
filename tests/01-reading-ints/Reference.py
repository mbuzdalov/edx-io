with open("input.txt", "rt") as inf, open("output.txt", "wt") as ouf:
    n = int(inf.readline())
    result = sum(int(v) for line in inf.readlines() for v in line.split())
    ouf.write(str(result) + "\n")
