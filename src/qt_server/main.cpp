#include <QCoreApplication>
#include "tcp_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tcp_server server;

    return a.exec();
}
