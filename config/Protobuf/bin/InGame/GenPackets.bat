pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./ProtocolServer.proto
protoc.exe -I=./ --cpp_out=./ ./ProtocolTest.proto
protoc.exe -I=./ --csharp_out=./ ./ProtocolClient.proto

XCOPY /Y ProtocolServer.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolServer.pb.cc "../../../../src/ServerGame"

XCOPY /Y ProtocolTest.pb.h "../../../../src/DummyClient"
XCOPY /Y ProtocolTest.pb.cc "../../../../src/DummyClient"


XCOPY /Y ProtocolClient.cs "../../../../src/GameClient\InGame\NetworkTest\Assets\Scripts\Network"

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.cs

IF ERRORLEVEL 1 PAUSE