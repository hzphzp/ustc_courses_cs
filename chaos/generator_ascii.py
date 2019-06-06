import math as m
class generator(object):


    def __init__(self, initual_value, u):
        self.initual_value = initual_value
        self.u = u
        self.state = self.initual_value

    def next(self):
        x = self.state
        self.state = self.u * x * (1 - x)
        print(x)
        y = int(x * 100000000000000000000000000000000)
        print(str(y))
        return str(y)


if __name__ == "__main__":
    filename = "Log/ascii_log"
    fp = open(filename, "w")
    fp.write("#==================================================================\n")
    fp.write("# generator logistics  init = 0.71 \n")
    fp.write("#==================================================================\n")
    fp.write("type: d\n")
    fp.write("count: 1000000\n")
    fp.write("numbit: 32\n")
    G = generator(initual_value = 0.71, u = 3.7)

    for i in range(1000000):
        fp.write(G.next())
        fp.write("\n")
