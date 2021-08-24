/*****************************************************************************/
/*                                                                           */
/* ideco : test task                                                         */
/*                                                                           */
/*  Copyright (C) 2021 Kuzmin Yaroslav <kuzmin.yaroslav@gmail.com>           */
/*                                                                           */
/* ideco is free software: you can redistribute it and/or modify it          */
/* under the terms of the GNU General Public License as published by the     */
/* Free Software Foundation, either version 3 of the License, or             */
/* (at your option) any later version.                                       */
/*                                                                           */
/* ideco is distributed in the hope that it will be useful, but              */
/* WITHOUT ANY WARRANTY; without even the implied warranty of                */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                      */
/* See the GNU General Public License for more details.                      */
/*                                                                           */
/* You should have received a copy of the GNU General Public License along   */
/* with this program.  If not, see <http://www.gnu.org/licenses/>.           */
/*                                                                           */
/*****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include "netrequest.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QString>

class Window : public QWidget
{
Q_OBJECT

public:
	Window(QWidget *parent = nullptr);
	~Window();

private slots:
	void enableButton(const QString & text);
	void loadGetRequest(bool checked);
	void readData(QString & str);
	void finishRequest(QString & str);
	void stopWait();

private:
	QLineEdit * lineEditUrl;
	QPushButton * pushButtonLoad;
	QPlainTextEdit * plainTextEdit;
	NetRequest * netRequest;
	bool timeoutRequest;
	bool firstData;
};

#endif
