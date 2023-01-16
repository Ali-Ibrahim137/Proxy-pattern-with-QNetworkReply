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
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

// stdlib
#include <memory>

class APIHandler: public QObject
{
    Q_OBJECT

public:
    APIHandler(const QString &hostUrl);
    ~APIHandler() = default;
    void GetFilesList();
    void DownloadFile(const QString &fileName);

Q_SIGNALS:
    void FilesListObtained(const QByteArray &data);
    void FileObtained(const QByteArray &data, const QString &fileName);
    void Error(const QString &message);

private:
    QString m_hostUrl;
    std::unique_ptr<QNetworkAccessManager> m_networkManager;
};

#endif // API_HANDLER_H
