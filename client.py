import socket
import sys

HOST = "127.0.0.1"
PORT = 25555

print(sys.argv[1])

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.send(str.encode(sys.argv[1]))
