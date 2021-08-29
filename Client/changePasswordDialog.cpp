#include "changePasswordDialog.h"
#include "Client.h"

changePasswordDialog::changePasswordDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->c = c->getInstance();
}

changePasswordDialog::~changePasswordDialog()
{
}

void changePasswordDialog::on_doneButton_clicked()
{
	QString QnewPass = ui.newPasswordEdit->text();

	c->sendPacketType(P_Chg_password);
	c->sendInt(c->getID());
	c->sendString(QnewPass.toUtf8().constData());

	this->close();
}

void changePasswordDialog::on_cancelButton_clicked()
{
	this->close();
}