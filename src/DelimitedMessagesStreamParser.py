import messages_pb2

class DelimitedMessagesStreamParser:
    def parse(self, bytes_: bytes) -> list:
        offset: int = 0
        messages_ = list()
        currentMessage = messages_pb2.WrapperMessage()
        tupleMsg: tuple = self._DecodeVarint32(bytes_, 0)

        while tupleMsg is not None:
            currentMessage.ParseFromString(bytes_[tupleMsg[1] + 4:(tupleMsg[0] + tupleMsg[1] + 4)])
            messages_.append(currentMessage.__deepcopy__())
            offset += tupleMsg[0] + 4
            tupleMsg = self._DecodeVarint32(bytes_, offset)

        return messages_
    
    def _DecodeVarint32(self, bytes_: str, start: int) -> tuple:
        if len(bytes_) < 4:
            return None

        sizeMsg = int.from_bytes(bytes_[start: start + 4], byteorder='little')

        if sizeMsg == 0 or sizeMsg > 8:
            return None

        if sizeMsg > len(bytes_) - start - 4:
            return None

        return sizeMsg, start
