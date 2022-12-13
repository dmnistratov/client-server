## Setup
Compile protobuf
```
$ protoc -I="./proto" --cpp_out="./proto" --python_out="./proto" proto/messages.proto
```
Compile server
```
$ g++ src/boost_server.cpp proto/messages.pb.cc -lboost_system -lprotobuf
```
Run server
```
$ ./a.out 
```
Run client
```
$ python3 src/client.py
```