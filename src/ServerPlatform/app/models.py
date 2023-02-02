from enum import Enum

from fastapi import Form
from pydantic.main import BaseModel
from pydantic.networks import EmailStr


# class UserRegister(BaseModel):
#     userID: str = Form(...)
#     userPW: str = Form(...)
#     reEnter: str = Form(...)
#     name: str = Form(...)
#     nickname: str = Form(...)
#     cell_phone : str = Form(...)
#     yy : str = Form(...)
#     mm : str = Form(...)
#     dd : str = Form(...)
#     sex : str = Form(...)
#     gather_agree : str = Form(None)

# class UserLogin(BaseModel):
#     logemail : str
#     logpass : str
    
# class SnsType(str, Enum):
#     email: str = "email"
#     facebook: str = "facebook"
#     google: str = "google"
#     kakao: str = "kakao"


class Token(BaseModel):
    Authorization: str = None


class UserToken(BaseModel):
    id: int
    pw: str = None
    email: str = None
    name: str = None
    phone_number: str = None
    profile_img: str = None
    sns_type: str = None

    class Config:
        orm_mode = True


class UserMe(BaseModel):
    id: int
    email: str = None
    name: str = None
    phone_number: str = None
    profile_img: str = None
    sns_type: str = None

    class Config:
        orm_mode = True
