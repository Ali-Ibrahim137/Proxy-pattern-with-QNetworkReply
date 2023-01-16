// local
#include "api_proxy.h"

APIProxy::APIProxy(const QString &hostUrl)
{
    m_apiHandler = std::make_unique<APIHandler>(hostUrl);
}

APIReply *APIProxy::GetFilesList()
{
    if(m_filesList.size() != 0)
    {
        // Value is stored before, create APIReply with it.
        return new APIReply(m_filesList);
    }
    else
    {
        // Call the endpoint.
        auto reply = m_apiHandler->GetFilesList();
        connect(reply, &APIReply::finished, this, [this, reply]
        {
            m_filesList = reply->readAll();
        });
        return reply;
    }
}

APIReply *APIProxy::DownloadFile(const QString &fileName)
{
    if(auto iter = m_filesMap.find(fileName.toStdString()); iter != m_filesMap.end())
    {
        return new APIReply(iter->second);
    }
    else
    {
        auto reply = m_apiHandler->DownloadFile(fileName);
        connect(reply, &APIReply::finished, this, [this, reply, fileName]
        {
            m_filesMap[fileName.toStdString()] = reply->readAll();
        });
        return reply;
    }
}
