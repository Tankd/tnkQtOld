#include "imapcommand.h"
#include <QDebug>
#include <QTextCodec>

IMapCommand::IMapCommand(IMapCommand::Type type, QString param)
    :m_type( type),
      m_param(param)
{

}

QString IMapCommand::generate() const
{


    if( type() == Login)
    {
        // if( get_authMethod() == IMap::AUTHPLAIN)
        return ("authenticate plain");
    }
    else if( type() == ListFolder)
    {
        return QString("LIST \"\" %1").arg( param());
    }
    else if( type() == SelectFolder)
    {
        return QString("SELECT %1").arg( param());
    }
    else if( type() == ListMails)
    {
        return QString("UID SEARCH %1" ).arg( param());
    }
    else if( type() == FetchMail)
    {
        return QString("UID FETCH %1 body[]" ).arg( param());
    }
}

void IMapCommand::parseReply(QByteArray data)
{

    m_response.append( data);

    auto datalines = QString(data).split("\r\n");
    datalines.removeLast();

    if( this->type() == ListFolder && datalines.last().contains("LIST completed"))
    {
        auto lines = QString(m_response).split("\r\n");
        foreach( QString line, lines)
        {
            line.remove(0, line.indexOf("/")+2);
            line.remove("\"");
            m_result << line;
        }

        setFinished();
    }
    else if( this->type() == SelectFolder && datalines.last().contains("SELECT completed"))
    {
        auto lines = QString(m_response).split("\r\n");
        QString s =lines.at(0);
        s.remove("* ");
        s.remove("EXISTS");
        m_result << s.trimmed();


        s = lines.at(1);
        s.remove("* ");
        s.remove("RECENT");
        m_result << s.trimmed();

        setFinished();
    }
    else if( this->type() == ListMails && datalines.last().contains( "SEARCH completed"))
    {
        auto lines = QString(m_response).split("\r\n");
        auto line = lines.at(0);
        line.remove("* SEARCH");
        line = line.trimmed();
        m_result = line.split(  " ");
        m_result.removeAll("");
        setFinished();
    }
    else if( this->type() == FetchMail && datalines.last().contains( "FETCH completed"))
    {
        QStringList lines = QString(m_response).split("\r\n");
        lines.removeFirst();
        lines.removeFirst();
        lines.removeFirst();

        lines.removeLast();
        lines.removeLast();

        //qDebug() << m_response;
        m_result << lines.join("\r\n");
        setFinished();
    }


    return;
}

IMapCommand::Type IMapCommand::type() const
{
    return m_type;
}

QString IMapCommand::param() const
{
    return m_param;
}

QStringList IMapCommand::result() const
{
    return m_result;
}

bool IMapCommand::isFinished() const
{
    return m_isFinished;
}

void IMapCommand::setFinished()
{
    m_isFinished = true;
    emit finished(this);
}
