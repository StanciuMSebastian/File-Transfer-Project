#include "LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent)
{
	w = new MainWindow();
	ui.setupUi(this);
	this->setFixedSize(600, 400);
}

void LoginWindow::on_signupButton_clicked()
{
	std::string username = ui.usernameEdit->text().toUtf8().constData();
	std::string password = ui.passwordEdit->text().toUtf8().constData();
	
	if (!ui.usernameEdit->text().isEmpty() && !ui.passwordEdit->text().isEmpty())
	{
		Client* c = c->getInstance();
			
		if (c->signup(username, password))
		{
			w->setClient();
			w->setWindowTitle(ui.usernameEdit->text());
			w->show();
			this->close();
		}
		else
		{
			ui.errorLabel->setText("Username sau paroala sub forma incorecta");
			delete c;
		}
	}
}

void LoginWindow::showPassword(bool check)
{
	if (check)
	{
	
	}
}


void LoginWindow::on_loginButton_clicked()
{
	std::string username = ui.usernameEdit->text().toUtf8().constData();
	std::string password = ui.passwordEdit->text().toUtf8().constData();

	if (!ui.usernameEdit->text().isEmpty() && !ui.passwordEdit->text().isEmpty())
	{
		Client* c = c->getInstance();
		if (c->login(username, password))
		{
			w->setClient();
			w->setWindowTitle(ui.usernameEdit->text());
			w->show();
			this->close();
		}
		else
		{
			ui.errorLabel->setText("Username sau paroala incorecta");
			delete c;
		}
	}
}
