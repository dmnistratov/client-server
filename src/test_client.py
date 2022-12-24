import socket
import sys
import messages_pb2
import argparse


#Arg parser for CLI
# parser = argparse.ArgumentParser()
# g = parser.add_mutually_exclusive_group()
# g.add_argument("-f", "--fast", action='store_true')
# g.add_argument("-s", "--slow", type=int)

# args= parser.parse_args()

message = messages_pb2.WrapperMessage()

# if args.fast:
    # message.request_for_fast_response.SetInParent()
# elif args.slow is not None:
    # message.request_for_slow_response.time_in_seconds_to_sleep = args.slow

message.request_for_slow_response.time_in_seconds_to_sleep = 1
# message.request_for_fast_response.SetInParent()
#Send/recv message to/from server
HOST = "127.0.0.1"
PORT = 25555

# print(sys.getsizeof(message))
# print(str(sys.getsizeof(message)).encode('utf-8'))
# print((sys.getsizeof(message)).to_bytes(4, sys.byteorder))
size: int = len(message.SerializeToString())
# print()
# print(size)
# print(message.SerializeToString())
# print((size).to_bytes(4, byteorder='little') + message.SerializeToString())

# with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#     s.connect((HOST, PORT))
#     s.send((size).to_bytes(4, byteorder='little'))
    # byteorder='little'
    # s.send(message.SerializeToString())
    # data = s.recv(1024)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    # s.send(message.SerializeToString())
    s.send((size).to_bytes(4, byteorder='little') + message.SerializeToString())
    data = s.recv(1024)

print(data)
message.ParseFromString(data)
print(message)
