import cv2
from PIL import Image
import numpy as np
import loadImage

def color2black(img:np.ndarray):
    img = np.mean(img, axis=2)
    img = np.array(img)
    return img

if __name__ == "__main__":
    imgs = loadImage.loadImage()
    imgs = [color2black(i) for i in imgs]
    
