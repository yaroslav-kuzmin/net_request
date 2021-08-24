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

#include "window.h"

#include <QBoxLayout>
#include <QTimer>

Window::Window(QWidget *parent)
: QWidget(parent)
{
	netRequest = new NetRequest;

	lineEditUrl = new QLineEdit;
	lineEditUrl->setFocus();

	pushButtonLoad = new QPushButton(tr("Load"));
	pushButtonLoad->setEnabled(false);

	plainTextEdit = new QPlainTextEdit;
	plainTextEdit->setReadOnly(true);

	connect(lineEditUrl, &QLineEdit::textChanged, this, &Window::enableButton);
	connect(pushButtonLoad, &QPushButton::clicked, this, &Window::loadGetRequest);
	connect(netRequest, &NetRequest::readData, this, &Window::readData);
	connect(netRequest, &NetRequest::finished, this, &Window::finishRequest);

	QHBoxLayout * vlayout = new QHBoxLayout;
	vlayout->addWidget(lineEditUrl);
	vlayout->addWidget(pushButtonLoad);

	QVBoxLayout * layout = new QVBoxLayout;
	layout->addLayout(vlayout);
	layout->addWidget(plainTextEdit);

	setLayout(layout);

	setWindowTitle(tr("Ideco"));
}

Window::~Window()
{
	delete netRequest;
}

void Window::enableButton(const QString & text)
{
	if (text.length() != 0)
		pushButtonLoad->setEnabled(true);
	else
		pushButtonLoad->setEnabled(false);
}


void Window::loadGetRequest(bool checked)
{
	QString str = lineEditUrl->text();
	QPalette palette = plainTextEdit->palette();

	int rc = netRequest->process(str);
	if (rc == NetRequest::INVALID_URL) {
		str.clear();
		str.append(tr("Invalid URL"));
		palette.setColor(QPalette::Text, Qt::red);
		firstData = false;
	}
	else {
		palette.setColor(QPalette::Text, Qt::black);
		pushButtonLoad->setEnabled(false);
		firstData = true;
		QTimer::singleShot(10000, this, SLOT(stopWait()));
		timeoutRequest = false;
	}

	plainTextEdit->setPalette(palette);
	plainTextEdit->setPlainText(str);
}

void Window::readData(QString & str)
{
	QPalette palette = plainTextEdit->palette();
	palette.setColor(QPalette::Text, Qt::black);
	plainTextEdit->setPalette(palette);

	QString text = plainTextEdit->toPlainText();
	if (firstData) {
		text.clear();
		firstData = false;
	}

	if (text.length() > 512)
		return;
	if ((str.length() + text.length() < 512))
		text.append(str);
	else {
		qsizetype len = 512 - text.length();
		text.append(str.data(), len);
	}
	plainTextEdit->setPlainText(text);
}

void Window::finishRequest(QString & str)
{
	pushButtonLoad->setEnabled(true);
	if (str.isEmpty())
		return;

	QString text = plainTextEdit->toPlainText();
	QPalette palette = plainTextEdit->palette();
	palette.setColor(QPalette::Text, Qt::red);
	plainTextEdit->setPalette(palette);
	if (!timeoutRequest)
		plainTextEdit->setPlainText(str);
	else {
		text.append(str);
		plainTextEdit->setPlainText(text);
	}
}

void Window::stopWait()
{
	if (!netRequest->checkProcess())
		return;
	timeoutRequest = true;
	QString str(tr("timeout ....\n"));
	QPalette palette = plainTextEdit->palette();
	palette.setColor(QPalette::Text, Qt::red);
	plainTextEdit->setPalette(palette);
	plainTextEdit->setPlainText(str);
	netRequest->stop();
	pushButtonLoad->setEnabled(true);
}

