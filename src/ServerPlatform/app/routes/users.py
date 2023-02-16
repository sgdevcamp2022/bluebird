from fastapi import APIRouter, Form
from starlette.requests import Request

from app.database.schema import Users
from app.errors.exceptions import NotFoundUserEx
from app.models import UserMe

router = APIRouter()


@router.get("/me", response_model=UserMe)
async def get_user(request: Request):
    """
    get my info
    :param request:
    :return:
    """
    user = request.state.user
    user_info = Users.get(id=user.id)
    return user_info

@router.post("/user-sign-up")
async def signUp(userID: str = Form(...), userPw: str = Form(...)):
    return {"userId": userID, "userPW" : userPw}