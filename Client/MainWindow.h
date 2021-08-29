#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QAbstractItemView>
#include "ui_MainWindow.h"
#include "UploadDialog.h"
#include "Client.h"

class LoginWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    bool getLoggedOut() { return this->loggedOut; }
    void setClient();
    Ui::MainWindowClass ui;
private:
    QString processFilename(QString filepath);
    bool loggedOut = false;
    Client* c;
   

private slots:    
    void on_actionChange_Password_triggered();
    void on_downloadFromButton_clicked();
    void on_downloadButton_clicked();
    void on_uploadButton_clicked();
    void on_actionLog_out_triggered();
    void on_removeButton_clicked();
};
