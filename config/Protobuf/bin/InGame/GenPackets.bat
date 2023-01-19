pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./ProtocolGame.proto

XCOPY /Y ProtocolGame.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolGame.pb.cc "../../../../src/ServerGame"

IF ERRORLEVEL 1 PAUSE

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc