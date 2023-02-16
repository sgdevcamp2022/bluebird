import json
import struct
import socket
import protobufs.ProtocolMatch_pb2 as pb2

HOST = '127.0.0.1'
PORT = 6000

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# bind 
server_socket.bind((HOST, PORT))

# listen 
server_socket.listen()

# accept
client_socket, addr = server_socket.accept()

print('Connect~!')

data = client_socket.recv(1024)

print ("Raw data: ", data)

head = data[:4]
body = data[4:]

print("head", head)
print("body", body)
print("header type: ", data[0])
print("message leng: ", 256 * data[1] + data[2])

header = pb2.Header()
action = pb2.Data()
header.ParseFromString(head)
action.ParseFromString(body)

print("head : \n", header)
print("read-bodylen: ", len(data[2:]))
print("body : \n", action)
client_socket.sendall(bytes("OK", 'utf-8'))

client_socket.close()
server_socket.close()
exit(0)