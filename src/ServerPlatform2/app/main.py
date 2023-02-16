from dataclasses import asdict
from typing import Optional

import uvicorn
import aioredis
from fastapi import FastAPI, Depends
from fastapi.security import APIKeyHeader
from fastapi.staticfiles import StaticFiles

from starlette.middleware.base import BaseHTTPMiddleware
from starlette.middleware.cors import CORSMiddleware

from app.common.consts import EXCEPT_PATH_LIST, EXCEPT_PATH_REGEX
from app.database.conn import db
from app.common.config import conf
from app.middlewares.token_validator import AccessControl
from app.middlewares.trusted_hosts import TrustedHostMiddleware
from app.routes import index, auth, users, lobby


API_KEY_HEADER = APIKeyHeader(name="Authorization", auto_error=False)


def create_app():
    """
    앱 함수 실행
    """
    c = conf()
    app = FastAPI()
    app.mount("/static", StaticFiles(directory="app/static"), name="static")
    # app.mount("/files",  StaticFiles(directory="app/files"), name="files")
    conf_dict = asdict(c)
    db.init_app(app, **conf_dict)
    # 데이터 베이스 이니셜라이즈

    # 레디스 이니셜라이즈
    redis = aioredis.from_url(conf_dict['REDIS_URL'])

    # 미들웨어 정의
    app.add_middleware(AccessControl, except_path_list=EXCEPT_PATH_LIST, except_path_regex=EXCEPT_PATH_REGEX)
    app.add_middleware(
        CORSMiddleware,
        allow_origins=conf().ALLOW_SITE,
        allow_credentials=True,
        allow_methods=["*"],
        allow_headers=["*"],
    )
    app.add_middleware(TrustedHostMiddleware, allowed_hosts=conf().TRUSTED_HOSTS, except_path=["/user-login"])

    # 라우터 정의
    app.include_router(index.router)
    app.include_router(auth.router, tags=["Authentication"])
    # app.include_router(users.router, tags=["Users"], dependencies=[Depends(API_KEY_HEADER)])
    app.include_router(lobby.router, tags=["Lobby"])
    return app


app = create_app()


if __name__ == "__main__":
    
    uvicorn.run("app.main:app", host="127.0.0.1", port=8000, reload=True)
