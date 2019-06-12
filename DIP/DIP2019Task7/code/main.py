import Coder
import os
from PIL import Image
import numpy as np

def train() -> "Coder, rate(int)":
    path = '../data/train/'
    files = os.listdir(path)
    stat = {}
    for f in files:
        img = Image.open(path + f)
        img = img.convert('L')
        img = np.array(img)
        col, raw = img.shape
        for x in range(col):
            for y in range(raw):
                c = chr(int(img[x, y]))
                if c in stat:
                    stat[c] += 1
                else: 
                    stat[c] = 1
    # 归一化
    sum_stat = sum(stat.values())
    for c in stat.keys():
        stat[c] = stat[c] / sum_stat
    
    train_str = ''.join(stat.keys())
    train_probs = list(stat.values())

    coder = Coder.Coder(train_str, train_probs)
    compress_len = sum([len(coder.dic[c]) * stat[c] for c in train_str])
    true_len = 8 * len(train_str)
    rate = compress_len / true_len

    return coder, rate

def test(coder: Coder.Coder):
    path = '../data/test/'
    files = os.listdir(path)
    for f in files:
        coder.encode(f, f)
        coder.decode(f, f)

def debug():
    origin_files = os.listdir('../data/test/')
    for f in origin_files:
        origin_img = Image.open('../data/test/' + f)
        origin_img = origin_img.convert('L')
        origin_img = np.array(origin_img)
        new_img = Image.open('../data/reconstruction/' + f)
        new_img = np.array(new_img)
        print(origin_img == new_img)




if __name__ == "__main__":

    coder, rate = train()
    print(rate)
    test(coder)

    # debug()
    