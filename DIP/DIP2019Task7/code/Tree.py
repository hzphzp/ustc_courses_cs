class Node:
    def __init__(self, char: chr, prob: float):
        self.char = char
        self.prob = prob
        self.left = None
        self.right = None


class Tree:
    def __init__(self):
        self.neo = Node('T', 0)
        