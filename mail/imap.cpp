#include "imap.h"

#include <QDebug>
#include <QEventLoop>
#include <QSslConfiguration>
#include <QTextCodec>

#include "common/utils.h"

IMap::IMap(QObject *parent) : QObject(parent), m_socket(0), m_timeOut(10000), m_lastSendId(0), m_currentCommand(0)
{

}

QTcpSocket *IMap::socket() const
{
    return m_socket;
}
/*
void IMap::waitForResponse()
{
    m_responseText.clear();

    QEventLoop loop;
    connect(this, SIGNAL(responseRecieved()),&loop, SLOT(quit()));
    loop.exec();
}*/

int IMap::send(IMapCommand* command, bool addCommandId)
{
    if(addCommandId)
    {
        m_lastSendId++;
        socket()->write(  ( QString::number(m_lastSendId) +" " + command->generate()).toUtf8() + "\r\n");
        return m_lastSendId;
    }
    else
    {
        socket()->write(  command->generate().toUtf8() + "\r\n");
        return -1;
    }

}

void IMap::send(QString data, bool addCommandId)
{
    if(addCommandId)
    {
        m_lastSendId++;
        socket()->write(  ( QString::number(m_lastSendId) +" " + data).toUtf8() + "\r\n");
    }
    else
    {
        socket()->write(  data.toUtf8() + "\r\n");
    }
}

void IMap::connectToHost()
{
    if( get_protocol() == IMap::TCP)
    {
        m_socket = new QTcpSocket(this);
        connect( m_socket, &QTcpSocket::stateChanged, this, &IMap::socketStateChanged);
        connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(socketError(QAbstractSocket::SocketError)));
        connect( m_socket, &QTcpSocket::readyRead, this, &IMap::socketReadyRead);

    }
    else
    {
        m_socket = new QSslSocket(this);

        connect( m_socket, &QTcpSocket::stateChanged, this, &IMap::socketStateChanged);
        connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(socketError(QAbstractSocket::SocketError)));
        connect( m_socket, &QTcpSocket::readyRead, this, &IMap::socketReadyRead);
        connect(  ((QSslSocket*) m_socket), SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(socketSslErrors(QList<QSslError>)));

        //on supprime la vérification du serveur
        ((QSslSocket*) m_socket)->setPeerVerifyMode(QSslSocket::VerifyNone);
        QList<QSslError> errors;
        errors << QSslError(QSslError::SelfSignedCertificate);
        errors << QSslError(QSslError::HostNameMismatch);
        ((QSslSocket*)this->m_socket)->ignoreSslErrors(errors);
    }

    if( get_protocol() == IMap::SSL)
        ((QSslSocket*) m_socket)->connectToHostEncrypted( get_host(), get_port());
    else
        m_socket->connectToHost( get_host(), get_port());
    /*
    if(!m_socket->waitForConnected())
    {
        return;
    }
*/


    //  waitForResponse();
}

void IMap::login()
{
    runCommand(new IMapCommand( IMapCommand::Login));
}

void IMap::listFolder(const QString &name)
{
    runCommand(new IMapCommand( IMapCommand::ListFolder, name));
}

void IMap::listMails(const QString flag)
{
    runCommand( new IMapCommand( IMapCommand::ListMails, flag));
    //send("UID SEARCH " +flag);
}

void IMap::fetchMail(QString uid)
{    
     runCommand( new IMapCommand( IMapCommand::FetchMail, uid));
}


void IMap::selectMailBox(const QString &name)
{
    runCommand(new IMapCommand( IMapCommand::SelectFolder, name));
}

void IMap::socketStateChanged(QAbstractSocket::SocketState state)
{
    if( state == QAbstractSocket::UnconnectedState)
    {
        setState( Disconnected);
    }
    else if( state == QAbstractSocket::ConnectingState)
    {
        setState( ConnectingToHost);
    }
    else if( state == QAbstractSocket::ConnectedState)
    {
        setState( ConnectedToHost);
    }
}


void IMap::socketError(QAbstractSocket::SocketError error)
{
    qDebug() << "IMap::socketError" << error << m_socket->errorString();

}

void IMap::socketReadyRead()
{

    if( m_currentCommand == 0)
        return;

    QByteArray response = socket()->readAll();

    if( m_currentCommand->type() == IMapCommand::Login)
    {
        if( response == "+\r\n") //send login data
        {
            send(QByteArray().append((char) 0).append(get_login()).append((char) 0).append(get_password()).toBase64(), false);
        }
        else if(  response.contains("OK AUTHENTICATE completed")) //logged in
        {
            setState( Logged);
            emit commandFinished( m_currentCommand);
            m_currentCommand = 0;
            runCommand();
        }
    }
    else
    {
        m_currentCommand->parseReply( response);
    }


}




void IMap::socketSslErrors(const QList<QSslError> &errors)
{
    ((QSslSocket*) m_socket)->ignoreSslErrors( errors);
}



IMap::State IMap::state() const
{
    return m_state;
}

void IMap::setState(const IMap::State &state)
{
    if( m_state != state)
    {
        m_state = state;
        emit stateChanged( m_state);
    }
}


