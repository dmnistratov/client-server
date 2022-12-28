import datetime
import messages_pb2
import asyncio

def get_fast_response_message():
    msg: messages_pb2.WrapperMessage = messages_pb2.WrapperMessage()
    msg.fast_response.current_date_time = datetime.datetime.now().strftime("%Y%m%dT%H%M%S.%f")[:-3]
    return msg

def get_slow_response_message(count: int):
    msg: messages_pb2.WrapperMessage = messages_pb2.WrapperMessage()
    msg.slow_response.connected_client_count = count
    return msg

def write_log(msg: str):
    print(datetime.datetime.now().strftime("%Y-%m-%d-%H.%M.%S") + " [LOG]: " + msg)
    _file = open('log.log', 'a')
    _file.write(datetime.datetime.now().strftime("%Y-%m-%d-%H.%M.%S") + " [LOG]: " + msg + '\n')
    _file.close()

def get_port_from_file(fileName: str = 'port.ini'):
    _file = open(fileName, 'r')
    port = int(_file.readline())
    return port

# @types.coroutine
async def read_data(reader: asyncio.StreamReader):
    data_ = bytearray()
    # data_ = reader.read()

    # data_ = bytearray()
    while not reader.at_eof():
        data_ += await reader.read(1024)

    # data_: str = b''
    # while True:
    #     chunk = yield from reader.read(4)
    #     if not chunk:
    #         break
    #     data_ += chunk
    return data_    