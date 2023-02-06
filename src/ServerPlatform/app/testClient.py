import ProtocolMatch_pb2 as pb2
import socket

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
head.size = len(body);
head.state = pb2.STATE.C_LOGIN
header = head.SerializeToString()

message = head.SerializeToString() + body
byte = bytes(message);
print("send Message: ", len(body) ,"\nmessage size =", head.state)

# address family : IPv4 , Socket type : TCP(Stream)
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))
client_socket.send(byte);
print("is Done.")

while 1:
    data = client_socket.recv(1024)
    print(data)
    print('Server Received my Message~!')
    head = pb2.Header()
    head.ParseFromString(data[:4]);
    print(head.size, " ", head.state)