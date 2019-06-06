import numpy as np
f = open("seq.txt", "r")
s = f.readline()
m = np.zeros([150, 550])
loc = [0, 0]
x, y = loc
m[x][y] = 1
step = 0
print(len(s))
for d in s:
    if d == 'R':
        y += 1        
        m[x][y] = 1
    if d == 'L':
        y -= 1
        m[x][y] = 1
    if d == 'U':
        x -= 1
        m[x][y] = 1
    if d == 'D':
        x += 1
        m[x][y] = 1
print(m)
print(m.nonzero())
x_non, y_non = m.nonzero()
print(x_non)
print(max(x_non))
print(min(x_non))
print(max(y_non))
print(min(y_non))
import numpy as np
import scipy.misc as smp
'''
# Create a 1024x1024x3 array of 8 bit unsigned integers
data = np.zeros((150, 550, 3), dtype=np.uint8 )

data[512,512] = [254,0,0]       # Makes the middle pixel red
data[512,513] = [0,0,255]       # Makes the next pixel blue
'''

img = smp.toimage(m * 255)       # Create a PIL image
img.show()                      # View in default viewer