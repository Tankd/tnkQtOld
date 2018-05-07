#ifndef IMAPCOMMAND_H
#define IMAPCOMMAND_H

#include <QString>
#include <QList>

class IMapCommand : public QObject
{
    Q_OBJECT


signals:
    void finished(IMapCommand* command);
public:

    enum Type {
        Login,
        ListFolder,
        SelectFolder,
        ListMails,
        FetchMail
    };

    IMapCommand(Type type, QString param = QString());



    QString generate() const;

    void parseReply(QByteArray data);


    Type type() const;

    QString param() const;

    QStringList result() const;

    bool isFinished() const;
    void setFinished();

private:
    Type m_type;
    QString m_param;
    QStringList m_result;

    QByteArray m_response;

    bool m_isFinished;
};

#endif // IMAPCOMMAND_H
