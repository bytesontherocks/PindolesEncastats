#!/bin/bash

#sudo apt install protobuf-compiler  # Debian/Ubuntu
#sudo apt install libgrpc++-dev protobuf-compiler-grpc

python3 -m venv .venv
. .venv/bin/activate
pip install -r requirements.txt