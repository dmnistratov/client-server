import asyncio
import Common
from DelimitedMessagesStreamParser import DelimitedMessagesStreamParser


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
        server = await asyncio.start_server(self._session, self._host, self._port)

        addrs = ', '.join(str(sock.getsockname()) for sock in server.sockets)
        Common.write_log(f'Server started {addrs}')

        async with server:
            await server.serve_forever()

    async def _session(self, reader, writer):
        self._countClient += 1
        Common.write_log('Client connected.')

        data_ = await self.readAll(reader)
        parser: DelimitedMessagesStreamParser = DelimitedMessagesStreamParser()
        messages = parser.parse(data_)

        for message in messages:
            if message.HasField('request_for_slow_response'):
                timeSleep: int = message.request_for_slow_response.time_in_seconds_to_sleep
                await self._slow_response(writer, timeSleep)

            if message.HasField('request_for_fast_response'):
                await self._fast_response(writer)

        await writer.drain()
        writer.close()

        await self.do_accept(reader)

    async def readAll(self, reader: asyncio.StreamReader):
        data_ = b''
        block = await reader.read(1024)

        while block != b'':
            data_ += block

            if len(block) < 1024:
                break
            
            block = await reader.read(1024)

        return data_

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

    async def do_accept(self, reader):
        _data = await reader.read(1)
        if (not _data):
            self._countClient -= 1
            Common.write_log('Client disconnect.')
        else:
            self.do_accept(reader)


server: AsyncioServer = AsyncioServer('127.0.0.1', Common.get_port_from_file())
server.start()
