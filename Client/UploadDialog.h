#pragma once

#include <QDialog>
#include "ui_UploadDialog.h"
#include "Client.h"
class LoginWindow;
class MainWindow;
class UploadDialog : public QDialog
{
	Q_OBJECT

public:
	UploadDialog(QWidget* parent = Q_NULLPTR);
	~UploadDialog();

	std::string open(std::string usernames);
private:
	Client* c;
	std::string usernames;
	Ui::UploadDialog ui;

	//MainWindow* mainWindow;
private slots:
	void on_addButton_clicked();
	void on_doneButton_clicked();
};
