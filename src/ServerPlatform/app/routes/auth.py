from datetime import datetime, timedelta

import time
import bcrypt
import jwt
import aioredis
from fastapi import APIRouter, Form, Depends, Response
from fastapi.templating import Jinja2Templates

# TODO:
from sqlalchemy.orm import Session
from starlette.requests import Request
from starlette.responses import JSONResponse
from starlette.responses import RedirectResponse

from app.common.consts import JWT_SECRET, JWT_ALGORITHM
from app.database.conn import db
from app.database.schema import Users
from app.models import Token, UserToken
from app.middlewares.token_validator import AccessControl
from app.errors import exceptions as ex

router = APIRouter(prefix="/auth")
TEMPLATES = Jinja2Templates(directory='app/templates')

@router.post("/register")
async def register(
    request : Request,
    userID : str = Form(...),
    userPW : str = Form(...),
    name : str = Form(...),
    nickname : str = Form(...),
    cell_phone : str = Form(...),
    yy : str = Form(...),
    mm : str = Form(...),
    dd : str = Form(...),
    sex : int = Form(...),
    session: Session = Depends(db.session),
    ):
    """
    `회원가입 API`\n
    :param sns_type:
    :param reg_info:
    :param session:
    :return:
    """
    hash_pw = bcrypt.hashpw(userPW.encode("utf-8"), bcrypt.gensalt())
    birth = yy.zfill(4) + '-' + mm + '-' + dd.zfill(2)
    new_user = Users.create(
        session,
        auto_commit=True,
        id = userID,
        password=hash_pw,
        name = name,
        nickname = nickname,
        phone = cell_phone,
        birthday = birth,
        sex = sex,
        )
    token = dict(Authorization=f"Bearer {create_access_token(data=UserToken.from_orm(new_user).dict(exclude={'pw', 'marketing_agree'}),)}")
    response = TEMPLATES.TemplateResponse("message.html",{"request": request,"msg":"회원가입이 완료되었습니다."})
    return response
    

@router.post("/login", status_code=200, response_model=Token)
async def login(request : Request, logEmail : str = Form(...), logPass : str = Form(...)):
    # if "Authorization" not in request.cookies.keys():
    #     request.cookies.clear()
    is_exist = await is_email_exist(logEmail)
    if not logEmail or not logPass:
        return JSONResponse(status_code=400, content=dict(msg="Email and PW must be provided'"))
    if not is_exist:
        return JSONResponse(status_code=400, content=dict(msg="NO_MATCH_USER"))
    user = Users.get(id=logEmail)
    is_verified = bcrypt.checkpw(logPass.encode("utf-8"), user.password.encode("utf-8"))
    if not is_verified:
        return JSONResponse(status_code=400, content=dict(msg="NO_MATCH_USER"))
    
    userData = UserToken.from_orm(user).dict(exclude={'password'})
    token = dict(Authorization=f"Bearer {create_access_token(data = userData , expires_delta = 30)}")
    response = TEMPLATES.TemplateResponse("index.html",{"request": request, "userNo": userData['userNo'], "id": userData['id']})
    response.set_cookie(key="Authorization", value = token["Authorization"])
    print(token)
    redis = aioredis.from_url("redis://:a12b34@34.84.148.50:6379")
    await redis.hset(userData['userNo'],"nickname", userData['nickname'])
    await redis.hset(userData['userNo'],"loginTime", time.strftime('%Y-%m-%d %H:%M:%S'))

    return response

@router.get("/logout/")
async def logout(request: Request):

    # 템플릿 렌더링인 경우 쿠키에서 토큰 검사
    if "Authorization" not in request.cookies.keys():
        raise ex.NotAuthorized()
    token = request.cookies.get("Authorization")
    token_info = await AccessControl.token_decode(token)
    print(token_info)
    redis = aioredis.from_url("redis://:a12b34@34.84.148.50:6379")
    value = await redis.hget(token_info['userNo'],"nickname")
    print(value)

    await redis.delete(token_info['userNo'])

    value = await redis.hget(token_info['userNo'],"nickname")
    print(value)

    response = RedirectResponse('/')
    response.delete_cookie("Authorization")
    return response


async def is_email_exist(email: str):
    get_email = Users.get(id=email)
    if get_email:
        return True
    return False


def create_access_token(*, data: dict = None, expires_delta: int = None):
    to_encode = data.copy()
    if expires_delta:
        to_encode.update({"exp": datetime.utcnow() + timedelta(minutes=expires_delta)})
    encoded_jwt = jwt.encode(to_encode, JWT_SECRET, algorithm=JWT_ALGORITHM)
    return encoded_jwt
