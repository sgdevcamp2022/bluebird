import socket
import threading

from fastapi import APIRouter, Form
from starlette.responses import JSONResponse

import app.protobufs.ProtocolMatch_pb2 as pb2

userDict = dict()

def genThreadSocket():
    threadSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    threadSocket.connect(('127.0.0.1', 6000))

    body = pb2.Check()
    body.type = True
    body = body.SerializeToString()

    head = pb2.Header()
    head.size = len(body)
    head.state = pb2.STATE.CHECK
    
    msg = head.SerializeToString() + body
    threadSocket.send(msg)

    return threadSocket

def matchMakingThread(threadSocket):
    while True:
        result = threadSocket.recv(1024)
        head = result[:4]
        body = result[4:]
        
        header = pb2.Header()
        action = pb2.S_Match()

        header.ParseFromString(head)
        action.ParseFromString(body)

        print('header:', header)
        print('action:', action)
        print('ids:', action.ids, type(action.ids))

        userDict[action.id] = action.ids

def genClientSocket():
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket.connect(('127.0.0.1', 6000))

    body = pb2.Check()
    body.type = False
    body = body.SerializeToString()

    head = pb2.Header()
    head.size = len(body)
    head.state = pb2.STATE.CHECK
    
    msg = head.SerializeToString() + body
    clientSocket.send(msg)

    return clientSocket

router = APIRouter(prefix="/lobby")
threadSocket = genThreadSocket()
thread = threading.Thread(target=matchMakingThread, args=(threadSocket,))
thread.start()
clientSocket = genClientSocket()

@router.post("/start")
async def getMatch(userNo: int = Form(...), level: int = Form(...)):

    print("userNo:", userNo)
    print("level:", level)

    action = pb2.C_Login()
    action.id = userNo
    action.level = level
    body = action.SerializeToString()

    head = pb2.Header()
    head.size = len(body)
    head.state = pb2.STATE.C_LOGIN

    msg = head.SerializeToString() + body
    clientSocket.send(msg)
    print(msg)
    
    try:
        data = clientSocket.recv(1024)
        
        head = data[:4]
        body = data[4:]
        
        header = pb2.Header()
        action = pb2.S_Login()

        header.ParseFromString(head)
        action.ParseFromString(body)

        print('header:', header)
        print('action:', action)
        # print(userDict)

        userDict[action.id] = (None, action.level)
        print(userDict)
        return JSONResponse(content={"result": True})
    
    except:
        return JSONResponse(content={"result": False})
    

@router.post("/check")
async def checkMatch(userNo: int = Form(...)):
    # print(userDict)
    matchingRoom = userDict.get(userNo)[0]
    matchingLevel = userDict.get(userNo)[1]
    
    if matchingRoom == None:
        return JSONResponse(content={"result": -1, "level": -1})

    else:
        return JSONResponse(content={"result": matchingRoom, "level": matchingLevel})


@router.post("/cancel")
async def cancelMatch(userNo: int = Form(...)):
    print("userNo:", userNo)

    action = pb2.C_Cancle()
    action.id = userNo
    action.level = userDict.get(userNo)[1]
    body = action.SerializeToString()

    head = pb2.Header()
    head.size = len(body)
    head.state = pb2.STATE.C_CANCLE

    msg = head.SerializeToString() + body
    clientSocket.send(msg)
    
    try:
        data = clientSocket.recv(1024)
        print('Server Received my Message~!')
        
        head = data[:4]
        body = data[4:]
        
        header = pb2.Header()
        action = pb2.S_Login()

        header.ParseFromString(head)
        action.ParseFromString(body)

        print('header:', header)
        print('action:', action)
        userDict.pop(action.id)
        print(userDict)
        return JSONResponse(content={"result": True})
    
    except:
        return JSONResponse(content={"result": False})
