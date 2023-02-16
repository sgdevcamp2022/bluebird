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
    body.type = 1
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

        for id in action.ids:
            userDict[id]["room"] = action.room
        

def genClientSocket():
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket.connect(('127.0.0.1', 6000))

    body = pb2.Check()
    body.type = -1
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

    action = pb2.C_Login()
    action.id = userNo
    action.level = level
    body = action.SerializeToString()

    head = pb2.Header()
    head.size = len(body)
    head.state = pb2.STATE.C_LOGIN

    msg = head.SerializeToString() + body
    clientSocket.send(msg)
    
    try:
        data = clientSocket.recv(1024)
        
        head = data[:4]
        body = data[4:]
        
        header = pb2.Header()
        action = pb2.S_Login()

        header.ParseFromString(head)
        action.ParseFromString(body)

        userDict[action.id] = {"room" : None, "level" : action.level}

        return JSONResponse(content={"result": True})
    
    except:
        return JSONResponse(content={"result": False})
    

@router.post("/check")
async def checkMatch(userNo: int = Form(...)):
    isMatch = userDict[userNo]["room"]
    
    if isMatch == None:
        return JSONResponse(content={"result": -1, "level": -1})

    else:
        return JSONResponse(content={"result": isMatch, "level": userDict[userNo]["level"]})


@router.post("/cancel")
async def cancelMatch(userNo: int = Form(...)):

    action = pb2.C_Cancel()
    action.id = userNo
    action.level = userDict[userNo]["level"]
    body = action.SerializeToString()

    head = pb2.Header()
    head.size = len(body)
    head.state = pb2.STATE.C_CANCEL

    msg = head.SerializeToString() + body
    clientSocket.send(msg)
    
    try:
        data = clientSocket.recv(1024)

        head = data[:4]
        body = data[4:]
        
        header = pb2.Header()
        action = pb2.S_Cancel()

        header.ParseFromString(head)
        action.ParseFromString(body)

        userDict.pop(action.id)

        return JSONResponse(content={"result": True})
    
    except:
        return JSONResponse(content={"result": False})
