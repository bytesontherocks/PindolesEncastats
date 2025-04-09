import grpc

import sys,os
sys.path.append(os.path.abspath('./gen'))
import algorithm_pb2_grpc, algorithm_pb2

def run():
    channel = grpc.insecure_channel("localhost:50051")
    stub = algorithm_pb2_grpc.AlgoStub(channel)

    request = algorithm_pb2.CalcRequest(a=3, b=5)
    response = stub.Calculate(request)

    print("Result:", response.result)

if __name__ == "__main__":
    run()
