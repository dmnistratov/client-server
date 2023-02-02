import unittest
import messages_pb2
from DelimitedMessagesStreamParser import DelimitedMessagesStreamParser

class Test_TestStreamParser(unittest.TestCase):
    def setUp(self):
        self._parser = DelimitedMessagesStreamParser()
    def test_Empty(self):
        byteStr = b''
        self.assertEqual(self._parser.parse(byteStr), [])

    def test_FastResponse(self):
        message = messages_pb2.WrapperMessage()
        message.request_for_fast_response.SetInParent()

        size: int = len(message.SerializeToString())
        byteStr = (size).to_bytes(4, byteorder='little') + message.SerializeToString()

        self.assertEqual(self._parser.parse(byteStr), [message])

    def test_SlowResponse(self):
        message = messages_pb2.WrapperMessage()
        message.request_for_slow_response.time_in_seconds_to_sleep = 5

        size: int = len(message.SerializeToString())
        byteStr = (size).to_bytes(4, byteorder='little') + message.SerializeToString()

        self.assertEqual(self._parser.parse(byteStr), [message])


    def test_FastAndSlowResponse(self):
        # message one
        message1 = messages_pb2.WrapperMessage()
        message1.request_for_fast_response.SetInParent()

        size: int = len(message1.SerializeToString())
        byteStr = (size).to_bytes(4, byteorder='little') + message1.SerializeToString()

        # message two
        message2 = messages_pb2.WrapperMessage()
        message2.request_for_slow_response.time_in_seconds_to_sleep = 5

        size: int = len(message2.SerializeToString())
        byteStr += (size).to_bytes(4, byteorder='little') + message2.SerializeToString()

        self.assertEqual(self._parser.parse(byteStr), [message1, message2])

    def test_moreByte(self):
        # message one
        message1 = messages_pb2.WrapperMessage()
        message1.request_for_fast_response.SetInParent()

        size: int = len(message1.SerializeToString())
        byteStr = (size).to_bytes(4, byteorder='little') + message1.SerializeToString()

        # message two
        message2 = messages_pb2.WrapperMessage()
        message2.request_for_slow_response.time_in_seconds_to_sleep = 5

        size: int = len(message2.SerializeToString())
        byteStr += (size).to_bytes(4, byteorder='little') + message2.SerializeToString()

        # and more 
        byteStr += b'\x00\x12\x33'

        self.assertEqual(self._parser.parse(byteStr), [message1, message2])

    def test_lessByte(self):
        # message one
        message1 = messages_pb2.WrapperMessage()
        message1.request_for_fast_response.SetInParent()

        size: int = len(message1.SerializeToString())
        byteStr = (size).to_bytes(4, byteorder='little') + message1.SerializeToString()

        # message two
        message2 = messages_pb2.WrapperMessage()
        message2.request_for_slow_response.time_in_seconds_to_sleep = 5

        size: int = len(message2.SerializeToString())
        byteStr += (size).to_bytes(4, byteorder='little') + message2.SerializeToString()

        # and less 
        byteStr = byteStr[0: len(byteStr) - 2]

        self.assertEqual(self._parser.parse(byteStr), [message1])

if __name__ == '__main__':
    unittest.main()
