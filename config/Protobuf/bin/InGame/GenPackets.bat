pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./CProtocol.proto
protoc.exe -I=./ --csharp_out=./ ./C#Protocol.proto

IF ERRORLEVEL 1 PAUSE

# DEL /Q /F *.pb.h
# DEL /Q /F *.pb.cc
# DEL /Q /F *.h