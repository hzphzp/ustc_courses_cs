import numpy as np
import base64
import array
map = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_'
i = np.identity(10)
i = i.reshape(100)
l = [int(x) for x in i]
def test(x):
    if x == 0:
        return 'A'
    elif x == 1:
        return 'B'
    return ''
s = "".join(test(x) for x in l)

biso = "CGIIDFFHEJCGIIDFFHEJCGIIDFFHEJCGIIDFFHEJ"
b = np.array([map.index(x) for x in biso]).reshape(4, 10)


out1 = "Z0dYmWnaQvHJYjZFUt7XquHNF4P7t0_8p9uz5PIE"
out2 = "xlEtHqg4rAXdiZnxYOCTA8vgGQrr07LRoFZSUvFb"
out3 = "UG4f9MjDZtTLv6oXJ0GW"
out = out1 + out2 + out3
l = [map.index(x) for x in out]
l = np.array(l).reshape(10,10)
l = l - b[0]
print(l)
def add(x):
    if x < 0:
        return x + 64
    else:
        return x
l = [add(x) for x in l.reshape(100)]
l = np.array(l).reshape(10, 10)
print(l)

'''
non-bios
k = "31	41	23	54	33	32	41	17	16	5\t\
63	28	45	10	40	14	0	5\t30\t44\t\
22	59	10	50	48	16	40	8	39	61\t\
31	15	28	9	17	10	48	46	50	40\t\
31	56	47	15	2	11	1	25	32	8\t\
62	23	56	46	10	18	40	53	16	0\t\
28	47	42	10	15	62	17	33	5	59\t\
62	29	51	14	37	0	6	47	54	7\t\
2	18	41	2	3	5	48	21	12	57\t\
54	61	35	16	4	40	50	38	2	57"
'''
#biso
k = "2	17	34	57	17	45	15	61	45	24\t\
0	20	38	43	56	29	34	41	29	61\t\
29	3	25	25	32	57	22	4	32	52\t\
41	63	22	19	49	32	4	22	40	18\t\
27	24	11	11	2	15	57	9	36	4\t\
26	55	52	10	10	54	32	37	52	28\t\
14	31	12	60	47	44	53	41	19	13\t\
3	53	16	51	53	11	48	35	49	28\t\
25	26	8	57	51	30	62	17	53	0\t\
25	37	46	19	52	53	24	18	31	12"

k = [int(x) for x in k.split("\t")]
print(k)
k = np.array(k).reshape(10,10)
result = np.dot(l, k).reshape(100)
result = [x%64 for x in result]
print(result)

output = "p9dJ4Jsrj3oDy_KxMJ1N750NvUBtXVUGNPVALq5l"
input = "quick-brown-foxes-jump-over-the-lazy-dog"
#input = "AAAAAAAABAAAAAAAAAABAAAAAAAABAAAAAAAAAAB"
#input = "huanghuanghuanghuanghuanghuanghuanghuang"

def enc(s):
    s = [map.index(x) for x in s]
    s = np.array(s).reshape(4,10)
    s = np.dot(s, l) 
    s = s + b
    s = s.reshape(40)
    s = [int(x) % 64 for x in s]
    s = "".join(map[x] for x in s)
    return s

def dec(s):
    s = [map.index(x) for x in s]
    s = np.array(s).reshape(4, 10)
    s = s - b
    s = np.dot(s, k)
    s = s.reshape(40)
    s = [int(x) % 64 for x in s]
    s = "".join(map[x] for x in s)
    return s

print(dec(output) == input)
print(dec("JzRVPiVpqo4iDM8celyueIs4ff4DKeG3EMKihzuH"))
