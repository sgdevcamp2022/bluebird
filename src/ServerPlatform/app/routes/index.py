import os
from datetime import datetime
from time import time

from fastapi import APIRouter, Depends
from fastapi.responses import HTMLResponse
from fastapi.templating import Jinja2Templates
from fastapi.responses import FileResponse
# from fastapi.staticfiles import StaticFiles

from starlette.responses import Response
from starlette.requests import Request
from starlette.responses import JSONResponse

router = APIRouter()
TEMPLATES = Jinja2Templates(directory='app/templates')

@router.get("/", response_class=HTMLResponse)
async def index(request: Request):
    req = dict()
    req['request'] = request
    response = TEMPLATES.TemplateResponse("index.html", req)
    response.delete_cookie("Authorization")
    return response


@router.get("/user-sign-up", response_class=HTMLResponse)
async def signUp(request: Request):
    req = dict()
    req['request'] = request
    return TEMPLATES.TemplateResponse("user-sign-up.html", req)


@router.get("/user-login", response_class=HTMLResponse)
async def login(request: Request):
    req = dict()
    req['request'] = request
    return TEMPLATES.TemplateResponse("myLogin.html", req)

@router.get("/game-download")
async def download():
    file_path = 'app/files/Setup.exe'
    return FileResponse(path=file_path, filename=file_path)