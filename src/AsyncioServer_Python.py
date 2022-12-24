import asyncio
import messages_pb2
import Common


class AsyncioServer:
    _countClient: int
    _host: str
    _port: int

    def __init__(self, host: str, port: int):
        self._countClient = 0
        self._host = host
        self._port = port

    def start(self):
        asyncio.run(self._start())

    async def _start(self):
        server = await asyncio.start_server(
        self._session, self._host, self._port)

        addrs = ', '.join(str(sock.getsockname()) for sock in server.sockets)
        Common.write_log(f'Server started {addrs}')

        async with server:
            await server.serve_forever()

    async def _session(self, reader, writer):
        self._countClient += 1
        Common.write_log('Client connected.')

        # self.do_accept() # NOT WORK !!!

        size: int = int.from_bytes(await reader.read(4), byteorder='little')
        requestMessage: messages_pb2.WrapperMessage = messages_pb2.WrapperMessage()

        if size > 0:
            requestMessage.ParseFromString(await reader.read(size))

        if requestMessage.HasField('request_for_slow_response'):
            timeSleep: int = requestMessage.request_for_slow_response.time_in_seconds_to_sleep
            await self._slow_response(writer, timeSleep)

        if requestMessage.HasField('request_for_fast_response'):
            await self._fast_response(writer)

        writer.close()

    async def _slow_response(self, writer: asyncio.StreamWriter, timeSleep: int):
        Common.write_log(f'Received slow response: wait time {timeSleep} second.')
        responseMessage = Common.get_slow_response_message(self._countClient)
        await asyncio.sleep(timeSleep)
        await self._send_message(writer, responseMessage.SerializeToString())
        Common.write_log(f'Send slow response: {self._countClient} clients connected.')

    async def _fast_response(self, writer: asyncio.StreamWriter):
        Common.write_log('Received fast response.')
        responseMessage = Common.get_fast_response_message()
        await self._send_message(writer, responseMessage.SerializeToString())
        Common.write_log('Send fast response.')

    async def _send_message(self, writer: asyncio.StreamWriter, msg: str):
        writer.write(msg)
        await writer.drain()


    # @asyncio.coroutine
    # def do_connect():
    #    global tcp_server  # Make sure we use the global tcp_server
    #     while True:
    #         try:
    #             loop = asyncio.get_event_loop()
    #             tcp_server = yield from loop.create_connection(TcpClient, 
    #                                                            'localhost', 8000)
    #         except OSError:
    #             print("5 sec...")
    #             yield from asyncio.sleep(5)
    #         else:
    #             break

server: AsyncioServer = AsyncioServer('127.0.0.1', Common.get_port_from_file())
server.start()
