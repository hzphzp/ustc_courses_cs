import Tree
import math
import numpy as np
from PIL import Image

def is_repeat(s: str):
    d = {}
    for i, char in enumerate(s):
        if char in d:
            return True
        d[char] = 1
    return False

def to_dic(T: Tree.Node, dic: dict, path: list):
    if T.left == None and T.right == None:
        dic[T.char] = path.copy()
        return
    if T.left != None:
        path.append(0)
        to_dic(T.left, dic, path)
        path.pop(-1)
    if T.right != None:
        path.append(1)
        to_dic(T.right, dic, path)
        path.pop(-1)


class Coder:
    def __init__(self, train_str: str, probs: list):
        if len(train_str) != len(probs):
            print("输入长度没有对应")
            return None
        if is_repeat(train_str):
            print("不能有重复的字符")
            return None
        train_data = [x for x in train_str]
        data = [Tree.Node(train_str[i], probs[i]) for i in range(len(probs))]
        while len(data) > 1:
            data.sort(key=lambda x: x.prob, reverse=True)
            parent = Tree.Node('', data[-1].prob + data[-2].prob)
            parent.right = data.pop(-1)
            parent.left = data.pop(-1)
            data.append(parent)
        self.tree = data[0]
        self.dic = {}
        to_dic(self.tree, self.dic, [])


    def encode(self, read_filename: str, write_filename: str):
        img = Image.open('../data/test/' + read_filename)
        img = img.convert('L')

        img = np.array(img)
        size = img.shape
        img = img.flatten()
        assert(len(img) == size[1] * size[0])
        test_str = ''.join(chr(x) for x in img)



        result = []
        for i, char in enumerate(test_str):
            result += self.dic[char]
        size_x = [int(x) for x in '{0:010b}'.format(size[0])]
        size_y = [int(y) for y in '{0:010b}'.format(size[1])]
        padding_len = math.ceil((len(result) + 3 + 10 * 2) / 8) * 8 - (len(result) + 3 + 10 * 2)
        result = [int(x) for x in '{0:03b}'.format(padding_len)] \
            + size_x + size_y + result + [0] * padding_len

        # convert bit list into bytearray and write it into file
        result_str = ''.join([chr(int(''.join(str(x) 
                    for x in result[i * 8: i * 8 + 8]), 2)) for i in range(len(result) // 8)])
        f = open('../data/compress/' + write_filename, mode='wb')
        f.write(str.encode(result_str))
        f.close()


    
    def decode(self, read_filename, write_img_filename): 
        # read bytearray from file and convert bytearray into bit list
        f = open('../data/compress/' + read_filename, mode='rb')
        data_str = f.read().decode()
        f.close()
        data = []
        for c in data_str:
            data += [int(x) for x in '{0:08b}'.format(ord(c))]


        padding_len = int(''.join([str(x) for x in data[: 3]]), 2)
        size_x = data[3: 3 + 10]
        size_y = data[3 + 10: 3 + 2 * 10]
        data = data[3 + 2 * 10: len(data) - padding_len].copy()
        result = []
        T = self.tree
        for i, bit in enumerate(data):
            if bit == 0:
                T = T.left
            else:
                T = T.right
            if T.left == None and T.right == None:
                result.append(T.char)
                T = self.tree

        # TODO: convert to img and save to file
        size_x = int(''.join([str(x) for x in size_x]), 2)
        size_y = int(''.join([str(x) for x in size_y]), 2)
        result = [ord(x) for x in result]
        result = np.array(result)
        assert(len(result) == size_x * size_y)
        result = result.reshape([size_x, size_y])
        result = np.uint8(result)
        img = Image.fromarray(result)
        img.show()

        img.save('../data/reconstruction/' + write_img_filename)


