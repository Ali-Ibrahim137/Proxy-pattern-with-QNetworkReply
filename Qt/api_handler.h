//---------------------------------------------------------------------------------------------------------------------
/// @file
///
/// @brief      API Handler Class
///
/// @author     Ali Ibrahim (ali103575@gmail.com)
///
/// @version    1.0
/// @date       01-15-2023
//---------------------------------------------------------------------------------------------------------------------

#ifndef API_HANDLER_H
#define API_HANDLER_H

// local

// qt
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

// stdlib
#include <memory>

class APIHandler
{
public:
    APIHandler(const QString &hostUrl);
    virtual ~APIHandler() = default;
    QNetworkReply *GetFilesList();
    QNetworkReply *DownloadFile(const QString &fileName);

private:
    QString m_hostUrl;
    std::unique_ptr<QNetworkAccessManager> m_networkManager;
};

#endif // API_HANDLER_H
