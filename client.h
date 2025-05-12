#ifndef CLIENT_H
#define CLIENT_H

#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>
#include <iostream>

class Client : public QObject {

  public:
    Client(std::string ip, int port_num);
    bool isConnected();
    QTcpSocket *socket;

  private:
    int Connect(QTcpSocket *socket);
    bool connection = 0;

};

#endif // CLIENT_H
