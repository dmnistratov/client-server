#include "pch.h"
#include "../../DelimitedMessagesStreamParser.h"
#include "../../../../proto/messages.pb.h"
#include <boost/make_shared.hpp>
#include <vector>

#if GOOGLE_PROTOBUF_VERSION >= 3012004
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSizeLong())
#else
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSize())
#endif
typedef std::vector<char> Data;
typedef std::shared_ptr<const Data> PointerToConstData;
template <typename Message> PointerToConstData serializeDelimited(const Message& msg)
{
    const size_t messageSize = PROTOBUF_MESSAGE_BYTE_SIZE(msg);
    const size_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);
    
    const std::shared_ptr<Data>& result = std::make_shared<Data>(headerSize + messageSize);
    google::protobuf::uint8* buffer = reinterpret_cast<google::protobuf::uint8*>(&*result->begin());

    google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(messageSize, buffer);
    msg.SerializeWithCachedSizesToArray(buffer + headerSize);

    return result;
}


TEST(TestParseDelimited, RequestForSlowResponse)
{
    TestTask::Messages::RequestForSlowResponse msg = TestTask::Messages::RequestForSlowResponse();
    msg.set_time_in_seconds_to_sleep(2);
    auto data = serializeDelimited(&msg);

    ASSERT_EQ(
        parseDelimited<TestTask::Messages::RequestForSlowResponse>(reinterpret_cast<const void*>(data.get()->data()), data.get()->size()),
        std::make_shared<TestTask::Messages::RequestForSlowResponse>(msg)
    );
}

TEST(TestParseDelimited, RequestForFastResponse)
{
    TestTask::Messages::RequestForFastResponse msg = TestTask::Messages::RequestForFastResponse();
    auto data = serializeDelimited(&msg);

    ASSERT_EQ(
        parseDelimited<TestTask::Messages::RequestForFastResponse>(reinterpret_cast<const void*>(data.get()->data()), data.get()->size()),
        std::make_shared<TestTask::Messages::RequestForFastResponse>(msg)
    );
}

TEST(TestParseDelimited, LessData)
{
    TestTask::Messages::RequestForSlowResponse msg = TestTask::Messages::RequestForSlowResponse();
    msg.set_time_in_seconds_to_sleep(2);
    PointerToConstData ptr = serializeDelimited(&msg);
    char* data = new char[ptr.get()->size() - 1];
    strcpy_s(data, ptr.get()->size(), ptr.get()->data());

    ASSERT_EQ(
        parseDelimited<TestTask::Messages::RequestForSlowResponse>(reinterpret_cast<const void*>(data), ptr.get()->size()),
        nullptr
    );
}

TEST(TestParseDelimited, MoreData)
{
    TestTask::Messages::RequestForSlowResponse msg = TestTask::Messages::RequestForSlowResponse();
    msg.set_time_in_seconds_to_sleep(2);
    PointerToConstData ptr = serializeDelimited(&msg);
    char* data = new char[ptr.get()->size() + 1];
    strcpy_s(data, ptr.get()->size(), ptr.get()->data());
    data[ptr.get()->size()] = '\x44';

    ASSERT_EQ(
        parseDelimited<TestTask::Messages::RequestForSlowResponse>(reinterpret_cast<const void*>(data), ptr.get()->size()),
        std::make_shared<TestTask::Messages::RequestForSlowResponse>(msg)
    );
}

TEST(TestDelimitedMessagesStreamParser, Main)
{
    TestTask::Messages::WrapperMessage* slowMsgBase = new TestTask::Messages::WrapperMessage();
    TestTask::Messages::RequestForSlowResponse* slowRequest = new TestTask::Messages::RequestForSlowResponse();
    slowRequest->set_time_in_seconds_to_sleep(2);
    slowMsgBase->set_allocated_request_for_slow_response(slowRequest);
    auto slowPtr = serializeDelimited(&slowMsgBase);

    TestTask::Messages::WrapperMessage* fastMsgBase = new TestTask::Messages::WrapperMessage();
    TestTask::Messages::RequestForFastResponse* fastRequest = new TestTask::Messages::RequestForFastResponse();
    fastMsgBase->set_allocated_request_for_fast_response(fastRequest);
    auto fastPtr = serializeDelimited(&fastMsgBase);
    
    char* data = new char[slowPtr.get()->size() + fastPtr.get()->size()];
    strcpy(data, slowPtr.get()->data());
    strcat(data, fastPtr.get()->data());

    DelimitedMessagesStreamParser<TestTask::Messages::WrapperMessage> parser;
    auto messages = std::vector<DelimitedMessagesStreamParser<TestTask::Messages::WrapperMessage>::PointerToConstValue>();
    messages.push_back(std::make_shared<const TestTask::Messages::WrapperMessage>(slowMsgBase));
    messages.push_back(std::make_shared<const TestTask::Messages::WrapperMessage>(fastMsgBase));

    ASSERT_EQ(
        parser.parse(data),
        messages
    );
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}