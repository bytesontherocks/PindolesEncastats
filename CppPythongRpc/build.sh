#!/bin/bash

mkdir -p bin
g++ gen/algorithm.pb.cc gen/algorithm.grpc.pb.cc algorithm_server.cpp -o ./bin/rpc_server `pkg-config --cflags --libs grpc++ grpc protobuf`
