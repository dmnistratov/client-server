import socket
import sys
import os
sys.path.append(os.path.join(os.path.dirname(__file__), '../..'))
import proto.messages_pb2 as messages
import argparse

#Arg parser for CLI
parser = argparse.ArgumentParser()
g = parser.add_mutually_exclusive_group()
g.add_argument("-f", "--fast", action='store_true')
g.add_argument("-s", "--slow", type=int)

args= parser.parse_args()

message = messages.WrapperMessage()

if args.fast:
    message.request_for_fast_response.SetInParent()
elif args.slow is not None:
    message.request_for_slow_response.time_in_seconds_to_sleep = args.slow

#Send/recv message to/from server
HOST = "127.0.0.1"
PORT = 25555

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    print(message.SerializeToString())
    print(message.ByteSize())
    print(b'0002')
    s.send(message.ByteSize().to_bytes(4, byteorder='big') + message.SerializeToString())
    data = s.recv(1024)

message.ParseFromString(data)
print(message)
