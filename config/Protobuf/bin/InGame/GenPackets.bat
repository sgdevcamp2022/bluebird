pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./ProtocolServer.proto
protoc.exe -I=./ --csharp_out=./ ./ProtocolClient.proto

XCOPY /Y ProtocolServer.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolServer.pb.cc "../../../../src/ServerGame"

XCOPY /Y ProtocolServer.pb.h "../../../../src/DummyClient"
XCOPY /Y ProtocolServer.pb.cc "../../../../src/DummyClient"

XCOPY /Y ProtocolClient.cs "../../../../src/GameClient/InGame/NetworkTest/Assets/Scripts/Network"
XCOPY /Y ProtocolClient.cs "../../../../src/GameClient/InGame_Progressing/InGame/Assets/Scripts/Packet"

IF ERRORLEVEL 1 PAUSE

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.cs

