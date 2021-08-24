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

#ifndef NETREQUEST_H
#define NETREQUEST_H

#include <QObject>
#include <QString>
#include <QScopedPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class NetRequest : public QObject
{
Q_OBJECT

public:
	NetRequest();
	~NetRequest();
	int process(QString & str);
	bool checkProcess();
	void stop();
signals:
	void readData(QString & str);
	void finished(QString & str);

private slots:
	void getFinished();
	void getReadyRead();

private:
	QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> netReply;
	QNetworkAccessManager netManager;
	QString errorStr;
};

#endif
