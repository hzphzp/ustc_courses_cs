import numpy as np
import cv2
import pysnooper


def down_sample(img, m, n):
    height, width, channels = img.shape
    emptyImage = np.zeros((m, n, channels), np.uint8)
    for i in range(m):
        for j in range(n):
            x = round(i * height / m)
            y = round(j * width / n)
            # print((x, y))
            if x >= height or y >= width:
                continue
            emptyImage[i, j] = img[x, y]
    return emptyImage


if __name__ == "__main__":
    img = cv2.imread("data/demo-1.jpg")
    cv2.imshow("512", img)
    cv2.waitKey(0)
    zoom = down_sample(img, 256, 256)
    cv2.imshow("256", zoom)
    cv2.waitKey(0)
    zoom = down_sample(img, 512, 512)
    cv2.imshow("re512", zoom)
    cv2.waitKey(0)
