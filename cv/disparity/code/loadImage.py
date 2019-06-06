import os
from PIL import Image
import numpy as np
from color2black import color2black

def loadImage():
    path = "/home/huangzp/code/cv/disparity/teddy-png-2/teddy"
    im2 = Image.open(os.path.join(path, "im2.png")).convert('RGB')
    im6 = Image.open(os.path.join(path, "im6.png")).convert('RGB')
    disp2 = Image.open(os.path.join(path, "disp2.png")).convert('RGB')
    disp6 = Image.open(os.path.join(path, "disp6.png")).convert('RGB')
    imgs = [im2, im6, disp2, disp6]
    imgs = [np.array(x) for x in imgs]
    imgs = [color2black(x) for x in imgs]
    return imgs
'''
    command = "{} = Image.open(os.path.join({path}, \"{file}\")).convert('RGB')"
    for f in fs:
        print(command.format(path, f))
        eval(command.format(path, f))
    imgs = [np.array(eval(x)) for x in fs]
'''


if __name__ == "__main__":
    imgs = loadImage()
    print(imgs)
    print(len(imgs))
    print(np.shape(imgs[0]))