import datetime
import messages_pb2

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