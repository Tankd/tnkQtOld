#ifndef RESTWS_H
#define RESTWS_H


#include <QNetworkAccessManager>
#include <QJsonObject>

#include "common/easyproperty.h"


class QNetworkReply;
class QAuthenticator;
namespace tnk {
namespace ws{
class RestWs : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit RestWs(QObject *parent = 0);

    typedef enum  REQUESTTYPE{
        GET,
        POST,
        PUT,
        DEL
    }REQUESTTYPE;

signals:

public slots:
    QNetworkReply *syncRequest(REQUESTTYPE type, const QString& path, QJsonObject data = QJsonObject());

    QNetworkReply *get(const QString& path, QJsonObject filter = QJsonObject());
    QNetworkReply *post(const QString& path, const QJsonObject &object);
    QNetworkReply *put(const QString& path, const QJsonObject &object = QJsonObject());
    QNetworkReply *del(const QString& path);




public:

    QJsonValue getJson(const QString &path, QJsonObject filter = QJsonObject());


    static void waitForFinished( QNetworkReply *reply);
    static QJsonValue waitJson( QNetworkReply *reply);
    static QJsonValue toJson( QNetworkReply* reply);
    static QJsonValue toJson(QByteArray data);

private slots:

    void on_authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);


private:
    PROPERTY(QString, host)
    PROPERTY(QString, user)
    PROPERTY(QString, password)

};
}
}
#endif // RESTWS_H
