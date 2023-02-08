import socket
import sys
import messages_pb2
import argparse

message = messages_pb2.WrapperMessage()
message.request_for_slow_response.time_in_seconds_to_sleep = 1
# message.request_for_fast_response.SetInParent()


HOST = "127.0.0.1"
PORT = 25555

size: int = len(message.SerializeToString())
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.send((size).to_bytes(4, byteorder='little') + message.SerializeToString())
    data = s.recv(1024)

print(data)
message.ParseFromString(data)
print(message)
