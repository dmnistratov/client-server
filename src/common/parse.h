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
    std::cout << size << std::endl;
    const char* message = static_cast<const char*>(data);
    int a = (int)(message[0] << 24 | message[1] << 16 | message[2] << 8 | message[3]);
    int b;
    std::memcpy(&b, message, sizeof(int));
    std::cout << b << std::endl;
    return nullptr;
 };

 template<typename MessageType>
 class DelimitedMessagesStreamParser
 {
 public:
 typedef std::shared_ptr<const MessageType> PointerToConstValue;
 std::list<PointerToConstValue> parse(const std::string& data){
 };

 private:
 std::vector<char> m_buffer;
 };