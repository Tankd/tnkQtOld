#ifndef IMAPSERVER_H
#define IMAPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QSslSocket>
#include "common/easyproperty.h"

#include "imapcommand.h"



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




    State state() const;
    void setState(const State &state);

    void send(QString data, bool addCommandId);
signals:
    void commandFinished(IMapCommand* command);
    void stateChanged( State state);

public slots:

    int send(IMapCommand *command, bool addCommandId = true);
    void connectToHost();
    void login();

    void listFolder(const QString& name);
    void selectMailBox( const QString& name);
    void listMails(const QString flag);
    void fetchMail(QString uid);


protected slots:
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketError(QAbstractSocket::SocketError error);
    void socketReadyRead();

    void socketSslErrors(const QList<QSslError> &errors);


public slots:
    void runCommand(IMapCommand* command = 0)
    {

        if( command)
        {
            connect(command, &IMapCommand::finished, this, &IMap::on_imapcommandFinished);
            m_nextCommands << command;
        }

        if( m_currentCommand != 0)
            return;

        if( m_nextCommands.size() == 0)
            return;


        if(  command && m_currentCommand && m_currentCommand != command)
            qDebug() << "PUTAIN CA MERDE GRAVE";

        m_currentCommand = m_nextCommands.at(0);
        m_nextCommands.removeFirst();

        send(m_currentCommand);

        if( m_currentCommand->type() == IMapCommand::Login)
            setState( Loggin);
    }


private slots:
    void on_imapcommandFinished(IMapCommand* command)
    {

        if( m_currentCommand == command)
            m_currentCommand = 0;

        runCommand( );
        emit commandFinished(command);
    }


protected:
    QTcpSocket *m_socket;
    State m_state;

    int m_lastSendId;


    IMapCommand* m_currentCommand;
    QList<IMapCommand*> m_nextCommands;


};

#endif // IMAPSERVER_H
