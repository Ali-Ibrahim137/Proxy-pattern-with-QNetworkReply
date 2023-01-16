//---------------------------------------------------------------------------------------------------------------------
/// @file
///
/// @brief      API Proxy Class
///
/// @author     Ali Ibrahim (ali103575@gmail.com)
///
/// @version    1.0
/// @date       01-16-2023
//---------------------------------------------------------------------------------------------------------------------

#ifndef API_PROXY_H
#define API_PROXY_H

// local
#include "api_handler.h"

// qt

// stdlib
#include <memory>
#include <map>

class APIProxy: public QObject
{
    Q_OBJECT
public:
    APIProxy(const QString &hostUrl);
    ~APIProxy() = default;
    APIReply *GetFilesList();
    APIReply *DownloadFile(const QString &fileName);

private:
    std::unique_ptr<APIHandler> m_apiHandler;
    std::map<std::string, QByteArray> m_filesMap;
    QByteArray m_filesList;
};

#endif // API_PROXY_H
