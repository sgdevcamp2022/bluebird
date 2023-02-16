[ 플랫폼 서버 사용법 ]

1. git pull origin develop
2. 파이썬 설치
3. 파이썬 가상환경 생성 python -m venv myVenv // ( 경로 : bluebird > src > ServerPlatform )
4. 가상환경 실행 // ( 경로 : bluebird > src > ServerPlatform > venv > Scripts > activate.bat )
5. Dependency 설치 pip install -r requirements.txt // ( 경로: bluebird > src > ServerPlatform )
6. 먼저 게임 서버, 매치메이킹 서버 실행 // ( 경로: bluebird > binary > server > Debug > ServerGame.exe, ServerMatch.exe )
7. uvicorn app.main:app --reload 명령어로 웹 서버 실행 // ( 경로: bluebird > src > ServerPlatform )
8. localhost 127.0.0.1로 접속 후 회원가입 및 로그인, 게임 설치, 게임 실행
