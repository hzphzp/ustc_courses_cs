import cv2
from down_sample import down_sample
from shuangsanci import interpolation
from matplotlib import pyplot as plt
################################################################################
imgFile = 'data/demo-1.jpg'
# load an original image
img = cv2.imread(imgFile)
################################################################################
# color value range
cRange = 256
# convert color space from bgr to gray
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
imgGray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
################################################################################
# pyramid level
level = 5
# original image at the bottom of gaussian pyramid
higherResoGauss = img
plt.subplot(
    2, 1 + level,
    1), plt.imshow(higherResoGauss), plt.title('Gaussian Level ' +
                                               '%d' % level), plt.xticks(
                                                   []), plt.yticks([])
for l in range(level):
    rows, cols, channels = higherResoGauss.shape
    print((rows, cols, channels))
    # delete last odd row of gaussian image
    if rows % 2 == 1:
        higherResoGauss = higherResoGauss[:rows - 1, :]
    # delete last odd column of gaussian image
    if cols % 2 == 1:
        higherResoGauss = higherResoGauss[:, :cols - 1]
    # gaussian image
    # TODO:
    # lowerResoGauss = cv2.pyrDown(higherResoGauss)
    lowerResoGauss = down_sample(higherResoGauss, rows // 2, cols // 2)
    # even rows and cols in up-sampled image
    # TODO:
    # temp = cv2.pyrUp(lowerResoGauss)
    temp = interpolation(lowerResoGauss, rows, cols)
    print(higherResoGauss.shape, temp.shape)
    # laplacian image
    lowerResoLap = higherResoGauss - temp
    # display gaussian and laplacian pyramid
    plt.subplot(
        2, 1 + level, l +
        2), plt.imshow(lowerResoGauss), plt.title('Gaussian Level ' + '%d' %
                                                  (level - l - 1)), plt.xticks(
                                                      []), plt.yticks([])
    plt.subplot(
        2, 1 + level, 1 + level + l +
        2), plt.imshow(lowerResoLap), plt.title('Laplacian Level ' + '%d' %
                                                (level - l - 1)), plt.xticks(
                                                    []), plt.yticks([])
    higherResoGauss = lowerResoGauss
################################################################################
# display original image and gray image
plt.show()
################################################################################
