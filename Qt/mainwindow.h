#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// local
#include "api_handler.h"

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
    Ui::MainWindow *ui;
    std::unique_ptr<APIHandler> m_apiHandler;
    std::vector<std::string> m_summaries;
};
#endif // MAINWINDOW_H
