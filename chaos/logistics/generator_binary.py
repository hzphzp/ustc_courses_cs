import math as m
import sys
import os

class generator(object):


    def __init__(self, initual_value, u):
        self.initual_value = initual_value
        self.u = u
        self.state = self.initual_value

    def next(self):
        x = self.state
        self.state = self.u * x * (1 - x)
        if x < 0.5:
            return 0
        else:
            return 1


if __name__ == "__main__":
    u = float(sys.argv[1])

    init = float(sys.argv[2])

    filename = os.path.join(os.getcwd(), "Log", sys.argv[3])
    fp = open(filename, "w")
    fp.write("#==================================================================\n")
    fp.write("# generator logistics  init = 0.71 \n")
    fp.write("#==================================================================\n")
    fp.write("type: b\n")
    fp.write("count: 1000000\n")
    fp.write("numbit: 32\n")
    G = generator(initual_value = init, u = u)
    for i in range(1000000):
        for j in range(32):
            fp.write(str(G.next()))
        fp.write("\n")

