import numpy as np
import socket
import protobufs.ProtocolMatch_pb2 as pb2

# server IP, PORT
HOST = '127.0.0.1'
PORT = 6000

# body
action = pb2.Data()
action.id = 1
action.level = 2
action.room = 3
action.state = True
body = action.SerializeToString()

# header
head = pb2.Header()
head.size = np.uint32(len(body))
head.state = pb2.STATE.C_LOGIN
header = head.SerializeToString()
# print("header content =", header)
# print("body content =", body)
# print("header size =",len(header))
# print("body size =",len(body))
message = header
message += body
print("send Message: ", message, "\nmessage size =",len(message))

# address family : IPv4 , Socket type : TCP(Stream)
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))
client_socket.sendall(message)
print("is Done.")

data = client_socket.recv(1024)
print(data)
msg = data.decode()
print('echo msg:', msg)
print('Server Received my Message~!')
client_socket.close()