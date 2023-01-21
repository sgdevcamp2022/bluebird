pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./ProtocolServer.proto
protoc.exe -I=./ --csharp_out=./ ./ProtocolClient.proto

XCOPY /Y ProtocolServer.pb.h "../../../../src/ServerGame"
XCOPY /Y ProtocolServer.pb.cc "../../../../src/ServerGame"

IF ERRORLEVEL 1 PAUSE