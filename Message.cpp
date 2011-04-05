#include "Message.h"
#include "MessageController.h"

Message::Message()
{
    tmp =0;
    udpSocket = new QUdpSocket(); //Socket To send the udp message
    udpReceive = new QUdpSocket(); //Socket to receive it
    udpReceive ->bind(77878,QUdpSocket::ShareAddress); //Bind on correct port and share the address,
    //based on the docs it means more than one can connect on it
}


void Message::tsend(QString aMessage)
{
    qDebug() << "==================================================";
    qDebug() << "WE have just sent something";
        qDebug() << "==================================================";
    qDebug() <<aMessage;
   QByteArray datagram(aMessage.toAscii());

  //  QByteArray datagram = "Message";
    udpSocket->writeDatagram(datagram.data(), datagram.size(),QHostAddress("134.117.27.188"),77878);
 //  udpSocket->writeDatagram(datagram.data(), datagram.size(),QHostAddress::Broadcast,77878);
    sleep(2);
}

void Message::treceive()
{

        while(udpReceive->hasPendingDatagrams())
        {

            qDebug() << "==================================================";
            qDebug() << "WE have just RECEIVED something";
            qDebug() << "==================================================";

            qDebug() <<tmp;
            tmp++;
            QByteArray datagram;
            datagram.resize(udpReceive->pendingDatagramSize());
            udpReceive->readDatagram(datagram.data(), datagram.size());
      //      ui->label->setText(tr("Received datagram: \"%1\"").arg(datagram.data()));

            qDebug() << datagram.data();
            MessageController::getInstance()->received(datagram.data());

        }
}
