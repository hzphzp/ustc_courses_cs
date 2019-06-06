from generator_binary import generator
import os



def myopen(filename):
    fp = open(filename, "w")
    fp.write("#==================================================================\n")
    fp.write("# generator logistics  init = 0.71 u = " + str(u) + "\n")
    fp.write("#==================================================================\n")
    fp.write("type: b\n")
    fp.write("count: 1000000\n")
    fp.write("numbit: 32\n")
    return fp

# 这个用来记录dieharder的结果
result_file = "binary_result_u"
# 这个用来记录生成的混乱序列
seq_file = "binary_seq_u"
list = (x/100 for x in range(340, 405, 5))
print(list)
for u in list:
    '''
    下面生成随机序列
    '''
    G = generator(0.71, u)
    # 这里生成seqfile的路径
    seq_filename = os.path.join(os.getcwd(), "Log", seq_file+str(u))
    fp = myopen(seq_filename)
    for i in range(1000000):
        for j in range(32):
            fp.write(str(G.next()))
        fp.write("\n")
    '''
    下面测试随机序列
    '''
    result_filename = os.path.join(os.getcwd(), "result", result_file+str(u))
    tmp = os.popen("dieharder -g 202 -f "+seq_filename+" -a > "+result_filename)
    

    