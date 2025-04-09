#!/bin/bash

rm -r gen
mkdir gen
python3 -m grpc_tools.protoc -I./protos --python_out=./gen --grpc_python_out=./gen algorithm.proto
protoc -I=./protos --cpp_out=./gen --grpc_out=./gen --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` algorithm.proto
touch ./gen/__init__.py
