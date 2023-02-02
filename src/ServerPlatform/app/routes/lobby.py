import socket

from fastapi import APIRouter
from starlette.requests import Request

router = APIRouter(prefix="/lobby")

@router.get("/")
async def m(request: Request):
    
    server_ip = 'localhost'
    server_port = 6000

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((server_ip, server_port))

    msg = input('msg:')
    s.sendall(msg.encode(encoding='utf-8'))

    data = socket.recv(100)
    msg = data.decode()
    print('echo msg:', msg)

    socket.close()

    return msg

