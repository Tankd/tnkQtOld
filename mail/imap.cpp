#include "imap.h"

#include <QDebug>
#include <QEventLoop>
#include <QSslConfiguration>

#include "common/utils.h"

IMap::IMap(QObject *parent) : QObject(parent), m_socket(0), m_timeOut(10000), m_lastSendId(0)
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

int IMap::send(const QString &data, bool addCommandId)
{
    if(addCommandId)
    {
        m_lastSendId++;
        socket()->write(  ( QString::number(m_lastSendId) +" " + data).toUtf8() + "\r\n");
        return m_lastSendId;
    }
    else
    {
        socket()->write(  data.toUtf8() + "\r\n");
        return -1;
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
    setState( Loggin);
    if( get_authMethod() == IMap::AUTHPLAIN)
    {
        send("authenticate plain");
    }
}

QList<uint> IMap::listMails(const QString flag)
{
    QList<uint> result;
    /*send("UID SEARCH " +flag);
    waitForResponse();


    QList<QByteArray> list = m_responseText.split('\r\n');

    QList<uint> result;
    QString str = list.at(0);
    str.remove(0, str.indexOf("SEARCH")+7);

    if(str.size())
        foreach( QString s, str.split(" "))
            result << s.toUInt();
*/
    return result;

}

QByteArray IMap::fetchMail(uint uid)
{
    /* int id = send( QString("FETCH %1 body[]").arg( uid));
    waitForResponse();

    if( m_responseText.contains("FETCH") == false)
        return QByteArray();

    QString head = m_responseText;
    head.remove(0, head.indexOf("{")+1);
    head.remove( head.indexOf("}"), head.size());
    uint size = head.toUInt();
    waitForResponse();

    QByteArray data;
    while( data.size()<=size)
    {
        waitForResponse();
        data = m_responseText;
        //str.remove(0, str.indexOf('\r\n')+1);
        //str.remove( str.lastIndexOf('\r\n'), str.size());
    }

    return data;*/
    return "";
}

QStringList IMap::listMailBox()
{
    /*send( QString("LIST \"\" \"*\""));
    waitForResponse();

    auto result = QString(m_responseText).split("\r\n");

    return result;*/
    return QStringList();
}

bool IMap::selectMailBox(const QString &name)
{
    /*send( QString("SELECT %1").arg(name));
    waitForResponse();

    if( m_responseText.contains("NO Mailbox") || m_responseText.contains("BAD Command"))
    {
        qDebug() << "IMap::selectMailBox" << name << "error";
        return false;
    }*/

    return true;

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
    m_responseText = socket()->readAll();
    if( m_responseText == "+\r\n") //send login data
    {
        send(QByteArray().append((char) 0).append(get_login()).append((char) 0).append(get_password()).toBase64(), false);
    }
    else if( m_responseText.contains("OK AUTHENTICATE completed")) //logged in
    {
        setState( Logged);
    }

    emit responseRecieved();
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

QByteArray IMap::responseText() const
{
    return m_responseText;
}

