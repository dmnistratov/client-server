/*!
 * \brief Расшифровывает сообщение, предваренное длиной из массива байтов.
 *
 * \tparam Message Тип сообщения, для работы с которым предназначена данная функция.
 *
 * \param data Указатель на буфер данных.
 * \param size Размер буфера данных.
 * \param bytesConsumed Количество байт, которое потребовалось для расшифровки сообщения в случае успеха.
 *
 * \return Умный указатель на сообщение. Если удалось расшифровать сообщение, то он не пустой.
 */

 #include <list>
 #include <memory>
 #include <vector>
 
 template<typename Message>
 std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0){
    if (size < 4)
        return nullptr;

    std::string buffer(static_cast<const char*>(data), size);
    size_t length = static_cast<size_t>(buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3]);

    if (length > size - 4)
        return nullptr;

    auto message = std::make_shared<Message>();
    message->ParseFromString(buffer.substr(4, 4 + length));
    *bytesConsumed = 4 + length;
    return message;
 };

 template<typename MessageType>
 class DelimitedMessagesStreamParser
 {
    public:
    typedef std::shared_ptr<const MessageType> PointerToConstValue;
    std::list<PointerToConstValue> parse(const std::string& data){
        for (auto byte : data)
            m_buffer.push_back(byte);

        size_t bytesConsumed = 0;
        std::list<PointerToConstValue> messages;
        for (auto message = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size(), &bytesConsumed); message != nullptr; message = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size(), &bytesConsumed)){
            messages.push_back(message);
            m_buffer.erase(m_buffer.begin(), m_buffer.begin() + bytesConsumed);
            bytesConsumed = 0;
        }

        return messages;
    };

    private:
    std::vector<char> m_buffer;
};