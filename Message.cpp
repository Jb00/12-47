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

   QFile file("/home/4user4/jbaubin/05/port");
   int port;
       if ( file.open(QIODevice::ReadOnly) ) {
     // file opened successfully
     QTextStream t( &file );        // use a text stream
     // until end of file...
     while ( !t.atEnd() ) {
       // read and parse the command line
       port = t.readLine().toInt();         // line of text excluding '\n'
       qDebug() << "Read port " << port;
     }
     // Close the file
     file.close();
   }

       udpReceive ->bind(port,QUdpSocket::ShareAddress); //Bind on correct port and share the address,


    QFile fileip("/home/4user4/jbaubin/05/testFile");
    QString ip;
        if ( fileip.open(QIODevice::ReadOnly) ) {
      // file opened successfully
      QTextStream t( &fileip );        // use a text stream
      // until end of file...
      while ( !t.atEnd() ) {
        // read and parse the command line
        ip = t.readLine();         // line of text excluding '\n'
        qDebug() << "Read liine " << ip;
        udpSocket->writeDatagram(datagram.data(), datagram.size(),QHostAddress(ip),port);
        sleep(2);
      }
      // Close the file
      file.close();
    }



  //  QByteArray datagram = "Message";

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
