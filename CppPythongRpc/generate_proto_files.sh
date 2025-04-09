#!/bin/bash

rm -r gen
mkdir gen
python3 -m grpc_tools.protoc -I. --python_out=./gen --grpc_python_out=./gen algorithm.proto
protoc -I=. --cpp_out=./gen --grpc_out=./gen --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` algorithm.proto

g++ gen/algorithm.pb.cc gen/algorithm.grpc.pb.cc algorithm_server.cpp -o ./bin/rpc_server `pkg-config --cflags --libs grpc++ grpc protobuf`
