# camp2022_bluebird
스마일게이트 개발 캠프 2022 - 윈터 개발 캠프 2기 - Blue Bird

The project has been initialized.


# 프로젝트 개요
- 모두가 흥미롭게 개발할 수 있는 공통된 게임 분야이며 개개인의 도전 목표가 적절히 녹아 있는 폴 가이즈의 클론 프로젝트

## 팀 목표
- 더불어 성장할 수 있는 기회로 삼기
- 즐거운 개발 문화 경험하기
- 프로젝트 경험을 RAM이 아닌 ROM에 저장시키기

## 개인 목표
### 김정도
- 

### 임우영
-

### 홍지현
- 게임 콘텐츠를 설계 및 개발할 수 있는 능력을 갖추기
- C++ 초급자 탈출하기

### 김민관
- 

## 시스템 아키텍처
![image](https://user-images.githubusercontent.com/48054868/221210118-c19a660d-947e-46a3-a76d-bee3a08def3e.png)

## 각 스택
- 게임 클라이언트 : Unity
- 게임 서버 및 매치메이킹 서버 : C++ - IOCP
- 웹 플랫폼 : Python - FastAPI, TCP
- NPC 서버 : C++ - Boost::Asio
- DB : MySQL, Redis

## 포트 설정 및 IP, 패스워드
### PortNumber
- 3306 : NpcServer - MySQL
- 5000 : Server - Client
- 6000 : Loby - Match
- 6379 : Redis Server
- 7000 : Server - Match
- 8000 : Server - Npc

### Redis Server Address
- 34.84.148.50
- 임시 passward : a12b34

### MySQL Server Address(Npc Server)
- 121.145.229.137
- 임시 passward : a12b34

