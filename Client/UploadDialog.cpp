#include "UploadDialog.h"
#include"AllUsers.h"
#include"MainWindow.h"
UploadDialog::UploadDialog(QWidget* parent)
	: QDialog(parent)
{
	Client* c = c->getInstance();

	ui.setupUi(this);
	this->setFixedSize(400, 300);
}

UploadDialog::~UploadDialog()
{
	for (int i = 0; i < ui.usernameBox->count(); i++)
	{
		ui.usernameBox->removeItem(i);
	}
}

std::string UploadDialog::open(std::string usernames)
{
	QString individualUser = "";

	for (int i = 0; i < usernames.size(); i++)
	{
		if (usernames[i] == ',' || usernames[i] == '\0')
		{
			ui.usernameBox->addItem(individualUser);
			individualUser = "";
		}
		else
		{
			individualUser += usernames[i];
		}
	}

	this->exec();


	return this->usernames;
}

void UploadDialog::on_doneButton_clicked()
{
	this->usernames += "done";
	this->close();
}

void UploadDialog::on_addButton_clicked()
{
	//all clients usernames
	//de rezolvat bug daca nu acordam drept cuiva de acces
	QString username = ui.usernameBox->currentText();
	this->usernames += username.toUtf8().constData();
	this->usernames += ",";
	ui.usernameBox->removeItem(ui.usernameBox->findText(username));//atentie la remove ca nu mai apare la urmatorul upload
}

