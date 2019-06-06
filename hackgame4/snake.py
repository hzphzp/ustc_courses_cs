import socket
res = ""
sed = ""
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("202.38.95.46", 12009))
data = s.recv(1024)
res = data.decode()
'''
res = res.split('\n')[1]
res.replace('\n', '')
print(res)
sed = str(eval(res))
print(sed)
s.send(sed.encode())
'''
while 1:
    data = s.recv(1024)
    res = data.decode()
    res = res.replace('\n', '')
    if res == "Your answer is wrong!":
        print(res)
        break
    print(res)
    if (not 'find' in res) and (not 'sleep' in res) and (not 'import' in res) and (not 'exit' in res):
        try:
            sed = str(eval(res))
        except Exception:
            sed = "0"
        if (not sed):
            sed = "0"
    else:
        res = res.replace("__import__('os').system('find ~')", "\'huangzp\'")
        res = res.replace("exit()", "\'huangzp\'")
        res = res.replace("__import__('time').sleep(100)", "\'huangzp\'")
        print(res)
        sed = str(eval(res))
        print("cnm")
    print(sed)
    sed += '\n'
    s.send(sed.encode())





'''
s = input()
try:
    print(eval(s))
except Exception:
    pass
'''
