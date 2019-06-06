import cv2
import numpy as np


def S(x):
    x = np.abs(x)
    if 0 <= x < 1:
        return 1 - 2 * x * x + x * x * x
    if 1 <= x < 2:
        return 4 - 8 * x + 5 * x * x - x * x * x
    else:
        return 0


def interpolation(img, m, n):
    height, width, channels = img.shape
    emptyImage = np.zeros((m, n, channels), np.uint8)
    sh = m / height
    sw = n / width
    for i in range(m):
        for j in range(n):
            x = i / sh
            y = j / sw
            p = (i + 0.0) / sh - x
            q = (j + 0.0) / sw - y
            x = int(x) - 2
            y = int(y) - 2
            A = np.array([[S(1 + p), S(p), S(1 - p), S(2 - p)]])
            if x >= m - 3:
                m - 1
            if y >= n - 3:
                n - 1
            if x >= 1 and x <= (m - 3) and y >= 1 and y <= (n - 3):
                B = np.array([
                    [
                        img[x - 1, y - 1], img[x - 1, y], img[x - 1, y + 1],
                        img[x - 1, y + 1]
                    ],
                    [img[x, y - 1], img[x, y], img[x, y + 1], img[x, y + 2]],
                    [
                        img[x + 1, y - 1], img[x + 1, y], img[x + 1, y + 1],
                        img[x + 1, y + 2]
                    ],
                    [
                        img[x + 2, y - 1], img[x + 2, y], img[x + 2, y + 1],
                        img[x + 2, y + 1]
                    ],
                ])
                C = np.array([[S(1 + q)], [S(q)], [S(1 - q)], [S(2 - q)]])
                blue = np.dot(np.dot(A, B[:, :, 0]), C)[0, 0]
                green = np.dot(np.dot(A, B[:, :, 1]), C)[0, 0]
                red = np.dot(np.dot(A, B[:, :, 2]), C)[0, 0]

                # ajust the value to be in [0,255]
                def adjust(value):
                    if value > 255:
                        value = 255
                    elif value < 0:
                        value = 0
                    return value

                blue = adjust(blue)
                green = adjust(green)
                red = adjust(red)
                emptyImage[i, j] = np.array([blue, green, red], dtype=np.uint8)

    return emptyImage


if __name__ == "__main__":
    img = cv2.imread("data/demo-1.jpg")
    zoom = interpolation(img, 256, 256)
    cv2.imshow("cubic", zoom)
    cv2.imshow("image", img)
    cv2.waitKey(0)
