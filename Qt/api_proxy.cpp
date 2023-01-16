// local
#include "api_proxy.h"

APIProxy::APIProxy(const QString &hostUrl)
{
    m_apiHandler = std::make_unique<APIHandler>(hostUrl);
    InitializeConnections();
}

void APIProxy::GetFilesList()
{
    if(m_filesList.size() != 0)
    {
        // Value is stored before, emit it as a signal.
        emit FilesListObtained(m_filesList);
    }
    else
    {
        // Call the endpoint.
        m_apiHandler->GetFilesList();
    }
}

void APIProxy::DownloadFile(const QString &fileName)
{
    if(auto iter = m_filesMap.find(fileName.toStdString()); iter != m_filesMap.end())
    {
        emit FileObtained(iter->second);
    }
    else
    {
        m_apiHandler->DownloadFile(fileName);
    }
}

void APIProxy::InitializeConnections()
{
    connect(m_apiHandler.get(), &APIHandler::FilesListObtained, this, [this](const QByteArray &data)
    {
        m_filesList = data;             // Store the value.
        emit FilesListObtained(data);   // Emit Signal.
    });
    connect(m_apiHandler.get(), &APIHandler::FileObtained, this, [this](const QByteArray &data, const QString &fileName)
    {
        m_filesMap[fileName.toStdString()] = data;
        emit FileObtained(data);
    });
    connect(m_apiHandler.get(), &APIHandler::Error, this, [this](const QString &message)
    {
        emit Error(message);
    });
}
