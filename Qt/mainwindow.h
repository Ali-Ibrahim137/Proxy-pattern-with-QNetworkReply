#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// local
#include "api_proxy.h"

// qt
#include <QMainWindow>

// stdlib
#include <memory>
#include <string>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void InitializeConnections();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<APIProxy> m_apiProxy;
    std::vector<std::string> m_summaries;
};
#endif // MAINWINDOW_H
