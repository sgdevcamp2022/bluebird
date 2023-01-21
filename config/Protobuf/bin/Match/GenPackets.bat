pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./ProtocolMatch.proto
protoc.exe -I=./ --cpp_out=./ ./ProtocolConnect.proto

XCOPY /Y ProtocolMatch.pb.h "../../../../src/DummyClient"
XCOPY /Y ProtocolMatch.pb.cc "../../../../src/DummyClient"

XCOPY /Y ProtocolMatch.pb.h "../../../../src/ServerMatch"
XCOPY /Y ProtocolMatch.pb.cc "../../../../src/ServerMatch"

XCOPY /Y ProtocolMatch.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolMatch.pb.cc "../../../../src/ServerGame"

XCOPY /Y ProtocolConnect.pb.h "../../../../src/ServerMatch"
XCOPY /Y ProtocolConnect.pb.cc "../../../../src/ServerMatch"

XCOPY /Y ProtocolConnect.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolConnect.pb.cc "../../../../src/ServerGame"

IF ERRORLEVEL 1 PAUSE

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc