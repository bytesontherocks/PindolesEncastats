#!/bin/bash

sudo apt install protobuf-compiler  # Debian/Ubuntu
sudo apt install libgrpc++-dev protobuf-compiler-grpc
pip install grpcio grpcio-tools

rm -r gen
mkdir gen
python3 -m grpc_tools.protoc -I. --python_out=./gen --grpc_python_out=./gen algorithm.proto
protoc -I=. --cpp_out=./gen --grpc_out=./gen --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` algorithm.proto
