import socket

import numpy as np
from fastapi import APIRouter
from starlette.requests import Request

import app.protobufs.ProtocolMatch_pb2 as pb2

router = APIRouter(prefix="/lobby")

@router.get("/")
async def m(request: Request):

    requestAction = 1
    requestId = 1
    requestLevel = 2
    requestRoom = 3
    requestState = True
    # server IP, PORT
    server_ip = '127.0.0.1'
    server_port = 6000

    # body
    action = pb2.Data()
    action.id = requestId
    action.level = requestLevel
    action.room = requestRoom
    action.state = requestState
    body = action.SerializeToString()

    # header
    head = pb2.Header()
    head.size = np.uint32(len(body))
    if requestAction == 1 :
        head.state = pb2.STATE.C_LOGIN
    
    header = head.SerializeToString()

    # print("header content =", header)
    # print("body content =", body)
    # print("header size =",len(header))
    # print("body size =",len(body))

    message = header
    message += body

    # print("send Message: ", message, "\nmessage size =",len(message))

    # address family : IPv4 , Socket type : TCP(Stream)
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((server_ip, server_port))
    client_socket.sendall(message)

    data = client_socket.recv(1024)
    print('Server Received my Message~!')
    msg = data.decode()
    print('echo msg:', msg)
    client_socket.close()

    return msg

