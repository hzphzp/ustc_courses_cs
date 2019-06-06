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
import torchvision

from main import Net

def solve():
    model = load_model()
    image = Image.open('target.png')
    image = convert2tensor(image)
    inputs = preprocess_image(image)  # inputs size (1, 1, 30, 30)
    label = torch.tensor([6], dtype=torch.long)  # label size (1)
    # TODO: Part 1
    # Add your code here. Feel free to import any modules you like.

    # Helpful info:
    # 0. Please use the **latest** version of pytorch & torchvision
    # 1. Use `torch.clamp(x, 0, 1)` to clip x's value between [0, 1]
    # 2. This function expects the pixel values of a returned image are between [0, 1]
    # 3. Set `x.requires_grad = True` if you want to get the gradient of `x`


    to_tensor = torchvision.transforms.Compose([
                           torchvision.transforms.Resize((30, 30)),
                           torchvision.transforms.ToTensor(),
                           torchvision.transforms.Normalize((0.1307,), (0.3081,)),
                       ])
                       
    image = to_tensor(Image.open('target.png'))
    image = image.reshape(1, 1, 30, 30)
    pre = model(image)
    # the size here is probably wrong
    r = torch.nn.Parameter(data=torch.random.([1, 1, 30, 30]), requires_grad=True)
    optimizer = torch.optim.Adam(model.parameters(), lr=0.02, weight_decay=1e-5)
    for i in range(1000):

        optimizer.zero_grad()
        hack = model(inputs + r)
        print(torch.argmax(hack))
        origin = model(inputs)
        print(torch.argmax(origin))
        label_target = torch.tensor([2], dtype=torch.long)
        loss = F.nll_loss(hack, label_target) + torch.sum(torch.abs(r / (torch.abs(r) + 0.01))) + torch.sum(torch.abs(r))
        loss.backward()
        optimizer.step()

    print(torch.max(r))
    print(torch.min(r))

    image = image + r
    image = image.reshape(30, 30)

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

    target = convert2tensor(Image.open('target.png')) # (600, 600)
    sample = convert2tensor(Image.open('sample.png')) # (600, 600)
    assert torch.sum(target != sample) < 600 * 600 * 0.002, 'Input hacking is detected! Game over.'
    assert F.l1_loss(target, sample) < 0.001, 'Input hacking is detected! Game over.'
    assert (torch.max(torch.abs(target - sample))) < 0.2, 'Input hacking is detected! Game over.'
    target = preprocess_image(target)  # (1, 1, 30, 30)
    sample = preprocess_image(sample)  # (1, 1, 30, 30)
    # TODO: Part 2
    nom = torchvision.transforms.Normalize((0.1307,), (0.3081,))
    target = nom(target)
    sample = nom(sample)
    truth = torch.argmax(model(target))
    hack = torch.argmax(model(sample))
    assert int(truth) != int(hack), 'Fail to hack. Game over.'
    print('Cong! You win!!!')


if __name__ == '__main__':
    output = solve() # return a picture 600*600
    convert2image(output).save('sample.png')
    # You have to pass this check!
    check()
