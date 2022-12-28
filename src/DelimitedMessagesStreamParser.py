class DelimitedMessagesStreamParser:
    # Get first message from buffer if exist
    def _parse_delimited(self, bytes_: bytes, start: int):
        a = bytes_[start:4]
        sizeMessage = int.from_bytes(bytes_[start:4], byteorder='little')
        # message = bytes_[start + 4, sizeMessage]
        return (sizeMessage, start + 4)

    def parse(self, bytes_: bytes) -> list:
        offset: int = 0
        messages_ = list()
        currentMessage: tuple = self._parse_delimited(bytes_, 0)

        while currentMessage is not None:
            messages_.append(currentMessage)
            offset += messages_[-1][0] + 4
            currentMessage = self._parse_delimited(bytes_, offset)

        return messages_

    def _DecodeVarint32(self, bytes: str, start: int):
        pass


# (message_size, pos) = _DecodeVarint32(bytes_, start)
 
# current_message = bytes_[pos:(frame_size + pos)]
 
# bytes_ - входные данные, полученные из сокета(например, прочитанные функцией readAll() или еще какой-то)
 
# start - это указание на начало интересующего нас куска в bytes_(там лежат N сообщений, предваренных размером в Varint32)
 
# для первого сообщения start равен 0
 
# message_size - это размер сообщения
 
# pos - это начало сообщения
 
# current_message - это само сообщение