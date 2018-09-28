#include "restws.h"

#include <QAuthenticator>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonArray>

#include <QEventLoop>



namespace tnk {
namespace ws{

RestWs::RestWs(QObject *parent) : QNetworkAccessManager(parent)
{
    connect( this, &QNetworkAccessManager::authenticationRequired, this, &RestWs::on_authenticationRequired);
}

QNetworkReply *RestWs::syncRequest(REQUESTTYPE type, const QString &path, QJsonObject data)
{
    QNetworkReply *reply = 0;
    int count = 5;
    do
    {
        qDebug() << "start" << count;
        switch( type)
        {
        case RestWs::GET:
            reply = this->get( path, data);
            break;

        case RestWs::POST:
            reply = this->post( path, data);
            break;

        case RestWs::PUT:
            reply = this->put( path, data);
            break;

        case RestWs::DEL:
            reply = this->del(path);
            break;

        default:
            break;
        }

        qDebug() << "wait";
        waitForFinished( reply);



        if(reply->isFinished())
        {
            qDebug() << "finished";
            return reply;
        }
        else
        {
            qDebug() << "restart";
            delete reply;
            reply = 0;
            count--;
        }
    }while(count > 0);


    return reply;
}

QNetworkReply *RestWs::get(const QString &path, QJsonObject filter)
{
    QUrl url(m_host+path);
    if( filter.isEmpty() == false)
    {
        QUrlQuery query;
        query.addQueryItem("filter", QJsonDocument( filter).toJson());
        url.setQuery( query);
    }



    return QNetworkAccessManager::get( QNetworkRequest(url));

}

QNetworkReply *RestWs::post(const QString &path, const QJsonObject &object)
{
    QByteArray ba = QJsonDocument( object).toJson();
    QUrl url(m_host+path);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, ba.size());
    request.setRawHeader("Accept", "application/json");

    return QNetworkAccessManager::post( request, ba);
}

QNetworkReply *RestWs::put(const QString &path, const QJsonObject &object)
{
    QByteArray ba = QJsonDocument( object).toJson();
    QUrl url(m_host+path);
    QNetworkRequest request(url);
    if(ba.isEmpty() == false)
    {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::ContentLengthHeader, ba.size());
    }
    request.setRawHeader("Accept", "application/json");

    return QNetworkAccessManager::put( request, ba);
}

QNetworkReply *RestWs::del(const QString &path)
{
    QUrl url(m_host+path);
    return QNetworkAccessManager::deleteResource( QNetworkRequest(url));
}

void RestWs::waitForFinished(QNetworkReply *reply)
{
    QEventLoop loop;
    connect( reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
}

QJsonValue RestWs::waitJson(QNetworkReply *reply)
{
    waitForFinished(reply);
    return toJson( reply);
}

QJsonValue RestWs::getJson(const QString &path, QJsonObject filter)
{
    auto reply = this->get(path, filter);

    waitForFinished( reply);
    return this->toJson(reply);
}

QJsonValue RestWs::toJson(QNetworkReply *reply)
{

    if( reply->error() == QNetworkReply::NoError)
    {
        return toJson(reply->readAll());
    }
    else
    {
        return QJsonValue();
    }

}

QJsonValue RestWs::toJson(QByteArray data)
{
    QJsonDocument doc = QJsonDocument::fromJson( data);
    if( doc.isArray())
        return doc.array();
    else
        return doc.object();
}

void RestWs::on_authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    authenticator->setUser( m_user);
    authenticator->setPassword( m_password);
}

}
}
