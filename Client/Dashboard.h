#pragma once

#include <QApplication>
#include <iostream>
#include "Client.h"
#include "ui_Dashboard.h"

class Dashboard : public QWidget, public Ui::Dashboard
{
	Q_OBJECT

public:
	Dashboard(QWidget *parent = Q_NULLPTR);
	~Dashboard();
};
