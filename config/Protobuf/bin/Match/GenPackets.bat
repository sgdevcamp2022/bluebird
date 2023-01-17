pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./ProtocolMatch.proto
protoc.exe -I=./ --cpp_out=./ ./ProtocolServer.proto

XCOPY /Y ProtocolMatch.pb.h "../../../../src/DummyClient"
XCOPY /Y ProtocolMatch.pb.cc "../../../../src/DummyClient"

XCOPY /Y ProtocolMatch.pb.h "../../../../src/ServerMatch"
XCOPY /Y ProtocolMatch.pb.cc "../../../../src/ServerMatch"

XCOPY /Y ProtocolMatch.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolMatch.pb.cc "../../../../src/ServerGame"

XCOPY /Y ProtocolServer.pb.h "../../../../src/ServerMatch"
XCOPY /Y ProtocolServer.pb.cc "../../../../src/ServerMatch"

XCOPY /Y ProtocolServer.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolServer.pb.cc "../../../../src/ServerGame"
IF ERRORLEVEL 1 PAUSE

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc