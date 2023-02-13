#include <list>
#include <memory>
#include <vector>
#include <string>

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
template<typename Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0)
{
    if (size < 4)
        return nullptr;

    const char* dataChr = reinterpret_cast<const char*>(data);

    size_t msgSize = 0;
    msgSize = (msgSize << 8) + dataChr[3];
    msgSize = (msgSize << 8) + dataChr[2];
    msgSize = (msgSize << 8) + dataChr[1];
    msgSize = (msgSize << 8) + dataChr[0];

    if (msgSize > size - 4)
        return nullptr;

    if (msgSize < 1 || msgSize > 8)
        return nullptr;

    char* dataMsg = new char[msgSize];
    std::copy(dataChr + 4, dataChr + 4 + msgSize, dataMsg);

    auto msgPtr = std::make_shared<Message>();
    msgPtr->ParseFromString(dataMsg);

    *bytesConsumed = 4 + msgSize;

    return msgPtr;
}


template<typename MessageType>
class DelimitedMessagesStreamParser
{
public:
    typedef std::shared_ptr<const MessageType> PointerToConstValue;

    std::list<PointerToConstValue> parse(const std::string& data)
    {
        std::list<PointerToConstValue> result = std::list<PointerToConstValue>();

        for (auto ch : data)
        {
            m_buffer.push_back(ch);
        }

        size_t bytesConsumed = 0;
        std::shared_ptr<MessageType> msgPtr = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size(), &bytesConsumed);
        while (msgPtr != nullptr)
        {
            result.push_back(msgPtr);
            m_buffer.erase(m_buffer.begin(), m_buffer.begin() + bytesConsumed);
            msgPtr = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size(), &bytesConsumed);
        }

        return result;
    }


private:
    std::vector<char> m_buffer; 
};