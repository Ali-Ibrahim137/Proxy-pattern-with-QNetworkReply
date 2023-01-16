// local
#include "api_reply.h"

// qt
#include <QTimer>

APIReply::APIReply(QNetworkReply *reply)
    : m_reply(reply)
    , m_array()
{
    // Call the endpoint
    connect(m_reply, &QNetworkReply::finished, this, [this]
    {
        if (m_reply->error() == QNetworkReply::NoError)
        {
            // Store the value
            m_array = m_reply->readAll();
        }
        // emit APIReply finished signal
        emit finished();
    });
}

APIReply::APIReply(const QByteArray &array)
    : m_reply(nullptr)
    , m_array(array)
{
    // Value is stored before, emit APIReply finished signal
    QTimer::singleShot(0, this, SIGNAL(finished()));
}

APIReply::~APIReply()
{
    if (m_reply)
    {
        // delete reply
        m_reply->deleteLater();
    }
}

QByteArray APIReply::readAll()
{
    return m_array;
}

QNetworkReply::NetworkError APIReply::error()
{
    if (m_reply)
    {
        return m_reply->error();
    }
    return QNetworkReply::NetworkError::NoError;
}

QString APIReply::errorString()
{
    if (m_reply)
    {
        return m_reply->errorString();
    }
    return QString();
}
