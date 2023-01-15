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

QNetworkReply *APIHandler::GetFilesList()
{
    const QString url = m_hostUrl + constants::FILES_ENDPOINT;
    return m_networkManager->get(QNetworkRequest(url));
}

QNetworkReply *APIHandler::DownloadFile(const QString &fileName)
{
    const QString url = m_hostUrl + constants::DOWNLOAD_FILE_ENDPOINT + fileName;
    return m_networkManager->get(QNetworkRequest(url));
}
