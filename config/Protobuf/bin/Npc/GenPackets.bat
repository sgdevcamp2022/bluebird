pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./ProtocolNpc.proto

XCOPY /Y ProtocolNpc.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolNpc.pb.cc "../../../../src/ServerGame"
XCOPY /Y ProtocolNpc.pb.h "../../../../src/ServerNpc"
XCOPY /Y ProtocolNpc.pb.cc "../../../../src/ServerNpc"

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc

PAUSE