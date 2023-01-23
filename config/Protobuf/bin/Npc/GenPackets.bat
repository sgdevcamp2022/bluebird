pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./ProtocolNpc.proto

XCOPY /Y ProtocolNpc.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolNpc.pb.cc "../../../../src/ServerGame"

IF ERRORLEVEL 1 PAUSE

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc