#pragma once

#include <QDialog>
#include "ui_changePasswordDialog.h"

class Client;

class changePasswordDialog : public QDialog
{
	Q_OBJECT

public:
	changePasswordDialog(QWidget *parent = Q_NULLPTR);
	~changePasswordDialog();

private:
	Client* c;
	Ui::changePasswordDialog ui;

private slots:
	void on_doneButton_clicked();
	void on_cancelButton_clicked();
};
