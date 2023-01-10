#include "session.h"

Session::Session(QTcpSocket* socket,QObject *parent)
    : QObject{parent}, socket_{socket}
{
    timer_ = new QTimer();
    timer_->setSingleShot(true);
    message_ = new WrapperMessage();
    connections_ = 0;
    qintptr descriptor = socket->socketDescriptor();
    connect(socket_, &QTcpSocket::readyRead, this, &Session::slotServerRead);
    connect(socket_, &QTcpSocket::disconnected, this, [this, descriptor](){ emit sessionClosed(descriptor);});
    connect(this, &Session::slowRespond, this, &Session::slotSlowRespond);
    connect(this, &Session::fastRespond, this, &Session::slotFastRespond);
    connect(timer_, &QTimer::timeout, this, [this](){ emit slowRespond();});
}

Session::~Session()
{
    delete timer_;
    delete message_;
}

void Session::setConnections(int connections)
{
    connections_ = connections;
}

qintptr Session::getSocketDescriptor()
{
    return socket_->socketDescriptor();
}

void Session::slotServerRead()
{
    // Add read size
    std::vector<char> m_buffer;
    for (const char byte : socket_->readAll()){
        m_buffer.push_back(byte);
    }

    parseDelimited<WrapperMessage>(m_buffer.data(), m_buffer.size());
    /*QString data = QString(byte);
    message_->ParseFromString(data.toStdString());
    if (message_->has_request_for_fast_response())
        emit fastRespond();
    if (message_->has_request_for_slow_response())
        timer_->start(message_->request_for_slow_response().time_in_seconds_to_sleep() * 1000);*/
}

void Session::slotServerWrite(WrapperMessage* respond_message)
{
}

void Session::slotFastRespond()
{
    std::string request;
    WrapperMessage * message = new WrapperMessage();
    std::string date = QDateTime::currentDateTime().toString(Qt::ISODate).toStdString();
    message->mutable_fast_response()->set_current_date_time(date.c_str());
    message->SerializeToString(&request);
    socket_->write(request.c_str());
}

void Session::slotSlowRespond()
{
    emit updateConnections(this->getSocketDescriptor());
    std::string request;
    WrapperMessage * new_message = new WrapperMessage();
    new_message->mutable_slow_response()->set_connected_client_count(this->connections_);
    new_message->SerializeToString(&request);
    delete new_message;
    socket_->write(request.c_str());
}
