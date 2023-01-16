//---------------------------------------------------------------------------------------------------------------------
/// @file
///
/// @brief      API Reply Class
///
/// @author     Ali Ibrahim (ali103575@gmail.com)
///
/// @version    1.0
/// @date       01-15-2023
//---------------------------------------------------------------------------------------------------------------------

#ifndef API_REPLY_H
#define API_REPLY_H

// qt
#include <QByteArray>
#include <QNetworkReply>
#include <QObject>

class APIReply : public QObject
{
    Q_OBJECT

public:
    APIReply(QNetworkReply *reply);
    APIReply(const QByteArray &array);

    ~APIReply();

    QByteArray readAll();

    QNetworkReply::NetworkError error();

    QString errorString();

Q_SIGNALS:
    void finished();

private:
    QNetworkReply *m_reply;
    QByteArray m_array;
};

#endif // API_REPLY_H
