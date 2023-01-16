// local
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "api_reply.h"

// qt
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace constants
{
    const QString BASE_URL = "http://127.0.0.1:3000";
    int STATUS_BAR_TIMEOUT = 5000;
    int MAX_CONTENT_LENGTH = 1000;
    namespace json_keys
    {
        const QString SUMMARY_KEY = "summary";
    }   // json_keys namespace
} // constants namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_apiProxy(std::make_unique<APIProxy>(constants::BASE_URL))
{
    ui->setupUi(this);
    // Get Files
    auto reply = m_apiProxy->GetFilesList();
    connect(reply, &APIReply::finished, this, [reply, this]
    {
        if(reply->error() == QNetworkReply::NoError)
        {
            auto data = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            QJsonObject obj = doc.object();
            for(auto &&key: obj.keys()) {
                auto summary = obj.value(key).toObject()[constants::json_keys::SUMMARY_KEY].toString().toStdString();
                ui->filesComboBox->addItem(key);
                m_summaries.push_back(summary);
            }
            connect(ui->filesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index)
            {
                ui->fileSummaryLabel->setText(QString::fromStdString(m_summaries[index]));
            });
        }
        else
        {
            ui->statusbar->showMessage(reply->errorString(), constants::STATUS_BAR_TIMEOUT);
        }
        if(!m_summaries.empty())
        {
            ui->fileSummaryLabel->setText(QString::fromStdString(m_summaries[0]));
        }
        reply->deleteLater();
    });
    connect(ui->downloadButton, &QPushButton::clicked, this, [this]()
    {
        auto fileName = ui->filesComboBox->currentText();
        auto reply = m_apiProxy->DownloadFile(fileName);
        connect(reply, &APIReply::finished, this, [this, reply]()
        {
            if(reply->error() == QNetworkReply::NoError)
            {
                auto data = reply->readAll();
                // Do What ever you want with data now.
                auto dataToDisplay = QString(data).left(std::min(constants::MAX_CONTENT_LENGTH, data.length()));
                if(data.length() > constants::MAX_CONTENT_LENGTH)
                {
                    dataToDisplay += "...";
                }
                ui->fileContent->setText(dataToDisplay);
            }
            else
            {
                ui->statusbar->showMessage(reply->errorString(), constants::STATUS_BAR_TIMEOUT);
            }
            reply->deleteLater();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
