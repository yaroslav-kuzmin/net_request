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

#include "netrequest.h"

#include <QUrl>
#include <QStringConverter>

NetRequest::NetRequest()
{
}

NetRequest::~NetRequest()
{
}

int NetRequest::process(QString & answer)
{
	if (!answer.contains("://"))
		answer.prepend("https://");

	QUrl url = QUrl::fromUserInput(answer);
	if (!url.isValid()) {
		answer.clear();
		answer.append(tr("Invalid URL %1").arg(url.errorString()));
		return 1;
	}
	answer.clear();

	if (url.scheme().isEmpty()) {
		answer.append("Invalid scheme");
		return 1;
	}

	if (url.host().isEmpty()) {
		answer.append("Invalid host");
		return 1;
	}

	if (url.port() == -1)
		url.setPort(80);

	QNetworkRequest netRequest(url);
	netReply.reset(netManager.get(netRequest));

	connect(netReply.get(), &QNetworkReply::finished, this, &NetRequest::getFinished);
	connect(netReply.get(), &QIODevice::readyRead, this, &NetRequest::getReadyRead);
	answer.append(url.toString());
	answer.append("\nWait..\n");
	return 0;
}

void NetRequest::getFinished()
{
	QNetworkReply::NetworkError error = netReply->error();
	errorStr.clear();
	if (error != QNetworkReply::NoError) {
		errorStr.append(tr("%1").arg(netReply->errorString()));
	}
	emit finished(errorStr);
	netReply.reset();
}

void NetRequest::getReadyRead()
{
	QByteArray byteArray = netReply->readAll();
	auto strDec = QStringDecoder(QStringDecoder::Utf8, QStringConverter::Flag::ConvertInvalidToNull);
	QString str = strDec(byteArray);
	if (strDec.hasError()) {
		str.clear();
		str.append(byteArray.toHex());
	}
	emit readData(str);
}

bool NetRequest::checkProcess()
{
	if (netReply.isNull())
		return false;
	return netReply->isRunning();
}

void NetRequest::stop()
{
	netReply->close();
	netReply.reset();
}

