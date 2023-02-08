pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./ProtocolMatch.proto
protoc.exe -I=./ --python_out=./ ./ProtocolMatch.proto

XCOPY /Y ProtocolMatch.pb.h "../../../../src/DummyClient"
XCOPY /Y ProtocolMatch.pb.cc "../../../../src/DummyClient"

XCOPY /Y ProtocolMatch.pb.h "../../../../src/ServerMatch"
XCOPY /Y ProtocolMatch.pb.cc "../../../../src/ServerMatch"

XCOPY /Y ProtocolMatch.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolMatch.pb.cc "../../../../src/ServerGame"

XCOPY /Y ProtocolMatch_pb2.py "../../../../src/ServerPlatform"

IF ERRORLEVEL 1 PAUSE

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.py