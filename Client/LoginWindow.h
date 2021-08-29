#pragma once

#include <QWidget>
//#include <QObject>
#include "MainWindow.h"
#include "ui_LoginWindow.h"

class LoginWindow :
	public QWidget
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = Q_NULLPTR);
	~LoginWindow() {}

private:
	QCheckBox* showpass;
	Ui::LoginWindow ui;
	MainWindow* w;

private slots:
	void showPassword(bool check);
	void on_loginButton_clicked();
	void on_signupButton_clicked();
};
