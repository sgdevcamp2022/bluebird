from datetime import datetime, timedelta

import bcrypt
import jwt
from fastapi import APIRouter, Form, Depends, Response
from fastapi.templating import Jinja2Templates

# TODO:
from sqlalchemy.orm import Session
from starlette.requests import Request
from starlette.responses import JSONResponse

from app.common.consts import JWT_SECRET, JWT_ALGORITHM
from app.database.conn import db
from app.database.schema import Users
from app.models import Token, UserToken
from app.middlewares.token_validator import AccessControl
from app.errors import exceptions as ex

"""
1. 구글 로그인을 위한 구글 앱 준비 (구글 개발자 도구)
2. FB 로그인을 위한 FB 앱 준비 (FB 개발자 도구)
3. 카카오 로그인을 위한 카카오 앱준비( 카카오 개발자 도구)
4. 이메일, 비밀번호로 가입 (v)
5. 가입된 이메일, 비밀번호로 로그인, (v)
6. JWT 발급 (v)

7. 이메일 인증 실패시 이메일 변경
8. 이메일 인증 메일 발송
9. 각 SNS 에서 Unlink 
10. 회원 탈퇴
11. 탈퇴 회원 정보 저장 기간 동안 보유(법적 최대 한도 내에서, 가입 때 약관 동의 받아야 함, 재가입 방지 용도로 사용하면 가능)

400 Bad Request
401 Unauthorized
403 Forbidden
404 Not Found
405 Method not allowed
500 Internal Error
502 Bad Gateway 
504 Timeout
200 OK
201 Created

"""


router = APIRouter(prefix="/auth")
TEMPLATES = Jinja2Templates(directory='app/templates')

# @router.post("/register/{sns_type}", status_code=201, response_model=Token)
@router.post("/register/")
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
# async def register(sns_type: SnsType, reg_info : UserRegister = Depends(), session: Session = Depends(db.session)):
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
    


# @router.post("/login/{sns_type}", status_code=200, response_model=Token)
@router.post("/login", status_code=200, response_model=Token)
async def login(request : Request, logEmail : str = Form(...), logPass : str = Form(...)):
    is_exist = await is_email_exist(logEmail)
    if not logEmail or not logPass:
        return JSONResponse(status_code=400, content=dict(msg="Email and PW must be provided'"))
    if not is_exist:
        return JSONResponse(status_code=400, content=dict(msg="NO_MATCH_USER"))
    user = Users.get(id=logEmail)
    is_verified = bcrypt.checkpw(logPass.encode("utf-8"), user.password.encode("utf-8"))
    if not is_verified:
        return JSONResponse(status_code=400, content=dict(msg="NO_MATCH_USER"))
    token = dict(Authorization=f"Bearer {create_access_token(data=UserToken.from_orm(user).dict(exclude={'pw', 'marketing_agree'}),)}")
    response = TEMPLATES.TemplateResponse("index.html",{"request": request,"id": logEmail})
    response.set_cookie(key="Authorization", value = token["Authorization"])
    return response

@router.post("/logout")
async def logout(request: Request):
    # 템플릿 렌더링인 경우 쿠키에서 토큰 검사
    if "Authorization" not in request.cookies.keys():
        raise ex.NotAuthorized()
    access_token=request.cookies.get("Authorization")
    token_info = await self.token_decode(access_token=request.cookies.get("Authorization"))
    request.state.user = UserToken(**token_info)


async def is_email_exist(email: str):
    get_email = Users.get(id=email)
    if get_email:
        return True
    return False


def create_access_token(*, data: dict = None, expires_delta: int = None):
    to_encode = data.copy()
    if expires_delta:
        to_encode.update({"exp": datetime.utcnow() + timedelta(hours=expires_delta)})
    encoded_jwt = jwt.encode(to_encode, JWT_SECRET, algorithm=JWT_ALGORITHM)
    return encoded_jwt
