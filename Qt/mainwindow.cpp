// local
#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    InitializeConnections();
    m_apiProxy->GetFilesList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitializeConnections()
{
    // APIProxy connections
    connect(m_apiProxy.get(), &APIProxy::FilesListObtained, this, [this](const QByteArray &data)
    {
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();
        for(auto &&key: obj.keys()) {
            auto summary = obj.value(key).toObject()[constants::json_keys::SUMMARY_KEY].toString().toStdString();
            ui->filesComboBox->addItem(key);
            m_summaries.push_back(summary);
        }
        if(!m_summaries.empty())
        {
            ui->fileSummaryLabel->setText(QString::fromStdString(m_summaries[0]));
        }
    });
    connect(m_apiProxy.get(), &APIProxy::FileObtained, this, [this](const QByteArray &data)
    {
        // Do What ever you want with data now.
        auto dataToDisplay = QString(data).left(std::min(constants::MAX_CONTENT_LENGTH, data.length()));
        if(data.length() > constants::MAX_CONTENT_LENGTH)
        {
            dataToDisplay += "...";
        }
        ui->fileContent->setText(dataToDisplay);
    });
    connect(m_apiProxy.get(), &APIProxy::Error, this, [this](const QString &message)
    {
        ui->statusbar->showMessage(message, constants::STATUS_BAR_TIMEOUT);
    });

    // UI connections
    connect(ui->filesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index)
    {
        if(index < static_cast<int>(m_summaries.size()))
        {
            ui->fileSummaryLabel->setText(QString::fromStdString(m_summaries[index]));
        }
    });
    connect(ui->downloadButton, &QPushButton::clicked, this, [this]()
    {
        auto fileName = ui->filesComboBox->currentText();
        m_apiProxy->DownloadFile(fileName);
    });
}
