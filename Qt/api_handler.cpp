// local
#include "api_handler.h"

namespace constants
{
    const QString FILES_ENDPOINT = "/api/files";
    const QString DOWNLOAD_FILE_ENDPOINT = "/api/download/file/";
}   // constants namespace

APIHandler::APIHandler(const QString &hostUrl)
    : m_hostUrl(hostUrl)
{
    m_networkManager = std::make_unique<QNetworkAccessManager>();
}


void APIHandler::GetFilesList()
{
    const QString url = m_hostUrl + constants::FILES_ENDPOINT;
    auto reply = m_networkManager->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, [reply, this]
    {
        if(reply->error() == QNetworkReply::NoError)
        {
            emit FilesListObtained(reply->readAll());
        }
        else
        {
            emit Error(reply->errorString());
        }
        reply->deleteLater();
    });
}


void APIHandler::DownloadFile(const QString &fileName)
{
    const QString url = m_hostUrl + constants::DOWNLOAD_FILE_ENDPOINT + fileName;
    auto reply = m_networkManager->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, [reply, fileName, this]
    {
        if(reply->error() == QNetworkReply::NoError)
        {
            emit FileObtained(reply->readAll(), fileName);
        }
        else
        {
            emit Error(reply->errorString());
        }
        reply->deleteLater();
    });
}
