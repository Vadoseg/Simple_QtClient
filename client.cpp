
#include "client.h"
#include <unistd.h>

Client::Client(std::string ip, int port_num) : socket(new QTcpSocket(this)) {

  socket->connectToHost(ip.c_str(), port_num);

  connect(socket, &QTcpSocket::readyRead, this, &Client::socketRead);

  checkConnect();
}

Client::~Client(){}

int Client::checkConnect(){

  if (!socket->waitForConnected()) {
    std::cerr << "Connection failed!" << std::endl;
    return -1;
  }

  connectionStatus = 1;

  return 0;
}

bool Client::isConnected(){
  return connectionStatus;
}

void Client::socketRead(){

  QDataStream client_datastream(socket);

  int block_size = 0;

  while(socket->bytesAvailable() > 0){
    if (block_size == 0){
      if (socket->bytesAvailable() < sizeof(int)) return;

      client_datastream >> block_size;
    }

    if (socket->bytesAvailable() < block_size)
      return;

    QByteArray message;
    message.resize(block_size);
    client_datastream.readRawData(message.data(), block_size);

    qDebug() << "Recieved message from athena_server: " << Qt::hex << message.data();

    block_size = 0;
  }
}

void Client::socketWrite(const QByteArray &data){

  QByteArray block;

  QDataStream outBlock(&block, QIODevice::WriteOnly);

  outBlock << data.size();

  block.append(data);

  socket->write(block);
}
