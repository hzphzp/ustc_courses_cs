"""

mmmummm  mmmm  mmmmm          mmmm  mmmmmm   mmm  mmmmm  mmmmmmmmmmmmm
   #    m"  "m #   "#        #"   " #      m"   " #   "# #        #
   #    #    # smmm#"        "#mmm  #mmtmm #      #mmmm" cmmmmm   #
   #    #    # #                 "# #      #      #   "m #        #
   #     #mm#  #             "mmm#" #mmmmm  "mmm" #    " #mmmmm   #
   
"""

# There are two parts (TODOs) remaining to be filled. Please read through the code.

from __future__ import print_function, division
import torch
import numpy as np
from PIL import Image
import torch.nn.functional as F

from main import Net

def solve():
    model = load_model()
    image = Image.open('target.png')
    image = convert2tensor(image)
    inputs = preprocess_image(image)
    label = torch.tensor([6], dtype=torch.long)
    # TODO: Part 1
    # Add your code here. Feel free to import any modules you like.

    # Helpful info:
    # 0. Please use the **latest** version of pytorch & torchvision
    # 1. Use `torch.clamp(x, 0, 1)` to clip x's value between [0, 1]
    # 2. This function expects the pixel values of a returned image are between [0, 1]
    # 3. Set `x.requires_grad = True` if you want to get the gradient of `x`

    raise NotImplementedError('You have to implement this segment by yourself.')

    return image

def convert2tensor(image):
    return torch.from_numpy(np.array(image).astype('f') / 255.)

def convert2image(arr):
    return Image.fromarray((arr.detach().numpy() * 255).astype(np.uint8), mode='L')
    
def preprocess_image(arr):
    image = convert2image(arr)
    image = image.resize((30, 30), resample=Image.NEAREST)
    return convert2tensor(image).reshape(1, 1, 30 ,30)

def load_model():
    model = Net()
    model.load_state_dict(torch.load('model.pth'))
    model.eval()
    return model

def check():
    model = load_model()

    target = convert2tensor(Image.open('target.png'))
    sample = convert2tensor(Image.open('sample.png'))
    assert torch.sum(target != sample) < 600 * 600 * 0.002, 'Input hacking is detected! Game over.'
    assert F.l1_loss(target, sample) < 0.001, 'Input hacking is detected! Game over.'
    assert (torch.max(torch.abs(target - sample))) < 0.2, 'Input hacking is detected! Game over.'
    target = preprocess_image(target)
    sample = preprocess_image(sample)
    # TODO: Part 2
    raise NotImplementedError('Two lines of codes is lost here. Inspect `main.py` and fill them!')
    truth = torch.argmax(model(target))
    hack = torch.argmax(model(sample))
    assert int(truth) != int(hack), 'Fail to hack. Game over.'
    print('Cong! You win!!!')


if __name__ == '__main__':
    output = solve()
    convert2image(output).save('sample.png')
    # You have to pass this check!
    check()
