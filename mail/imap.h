#ifndef IMAPSERVER_H
#define IMAPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QSslSocket>
#include "common/easyproperty.h"

class IMap : public QObject
{
    Q_OBJECT

    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)

public:
    enum Protocol{
        TCP,
        SSL,
        TLS
    };

    enum AuthMethod{
        AUTHPLAIN,
        AUTHLOGIN
    };


    enum State {
        Disconnected,
        ConnectingToHost,
        ConnectedToHost,
        Loggin,
        Logged,
    };


    PROPERTY( QString, host)
    PROPERTY( uint, port)
    PROPERTY( QString, login)
    PROPERTY( QString, password)
    PROPERTY( Protocol, protocol)
    PROPERTY( AuthMethod, authMethod)

    PROPERTY( int, timeOut)

    public:
        explicit IMap(QObject *parent = nullptr);


    QTcpSocket *socket() const;


  //  void waitForResponse();

    QByteArray responseText() const;


    QStringList listMailBox();
    State state() const;
    void setState(const State &state);

signals:
    void responseRecieved();
    void stateChanged( State state);

public slots:

    int send( const QString& data, bool addCommandId = true);
    void connectToHost();
    void login();

    bool selectMailBox( const QString& name);
    QList<uint> listMails(const QString flag);
    QByteArray fetchMail(uint uid);


protected slots:
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketError(QAbstractSocket::SocketError error);
    void socketReadyRead();

    void socketSslErrors(const QList<QSslError> &errors);




protected:
    QTcpSocket *m_socket;

    State m_state;

    QByteArray m_responseText;

    int m_lastSendId;


    QHash<uint, QByteArray> m_mailDatas;

};

#endif // IMAPSERVER_H
