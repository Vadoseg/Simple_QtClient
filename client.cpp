
#include "client.h"

Client::Client(std::string ip, int port_num) {

  socket = new QTcpSocket(this);

         // connect(socket, &QTcpSocket::readyRead, this, [socket]() {
         //   QByteArray data = socket->readAll();    // Lambda
         //   qDebug() << "Received from server:" << data;
         // });

  connect(socket, &QTcpSocket::connected, this, [this]() {
    socket->write("Hello from client!");    // Lambda
    socket->flush();
  });

  socket->connectToHost(ip.c_str(), port_num);

  Connect(socket);
}

int Client::Connect(QTcpSocket *socket){

  if (!socket->waitForConnected()) {
    std::cerr << "Connection failed!" << std::endl;
    return 1;
  }

  connection = 1;

  return 0;
}

bool Client::isConnected(){
  return connection;
}
