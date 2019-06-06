import numpy as np
from loadImage import loadImage
from PIL import Image
import scipy.misc
import sys

def disparityMap(imgL:np.ndarray, imgR:np.ndarray, winSize):
    m = np.zeros((imgL.shape[0], imgL.shape[1] - 60))
    d = np.zeros((imgL.shape[0], imgL.shape[1] - 60))
    for x in range(imgL.shape[0]):
        for y in range(imgL.shape[1]):
            print((x, y))
            try:
                m[x][y] = disparity_x_y(x, y, imgL, imgR, winSize)
            except ZeroDivisionError:
                m[x][y] = 0
            except IndexError:
                continue
            print(m[x][y])
    print(m)
    mmin = m.min()
    mmax = m.max()
    # m = (m-mmin)/(mmax-mmin)*255 # (矩阵元素-最小值)/(最大值-最小值)
    m = (m)/(mmax)*255 # (矩阵元素-最小值)/(最大值-最小值)
    scipy.misc.imsave("outfile_m{0}.jpg".format(winSize[0]), m)

    for x in range(m.shape[0]):
        for y in range(m.shape[1]):
            if m[x][y] != 0:
                d[x][y] = 255 / m[x][y]
            else:
                d[x][y] = 0
    dmin = d.min()
    dmax = d.max()
    d = (d-dmin)/(dmax-dmin)*255 # (矩阵元素-最小值)/(最大值-最小值)
    scipy.misc.imsave('outfile_d{0}.jpg'.format(winSize[0]), d)


    

def disparity_x_y(x:int, y:int, imgL:np.ndarray, imgR:np.ndarray, winSize):
    winL = getWindow(x, y, imgL, winSize)
    ssdMin = 9999999999
    d = 0
    for j in range(1, 40):
        if y + j + winSize[1] > imgL.shape[1]:
            return 0
        winR = getWindow(x, y + j, imgR, winSize)
        ssdNow = ssd(winL, winR)
        if ssdNow < ssdMin:
            ssdMin = ssdNow
            d = j
    return d


def getWindow(x:int, y:int, img:np.ndarray, winSize):
    # img2 = np.pad(img, ((0, winSize[0] - 1), (0, winSize[1] - 1)), "constant", constant_values=-1)
    win = img[x: x + winSize[0], y: y + winSize[1]]
    win = np.array(win)
    return win

    
def ssd(winL, winR):
    s = np.sum((winL[:,:]-winR[:,:])**2)
    return s


if __name__ == "__main__":
    if (len(sys.argv) != 2):
        print("input winSize")
        exit(1)
    
    winSize = [sys.argv[1], sys.argv[1]]
    print(winSize)
    winSize = [int(x) for x in winSize]

    imgs = loadImage()
    imgL = imgs[1] # im6
    imgR = imgs[0] # im2
    disparityMap(imgL, imgR, winSize)
