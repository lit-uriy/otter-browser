/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2014 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#ifndef OTTER_QTWEBKITWEBBACKEND_H
#define OTTER_QTWEBKITWEBBACKEND_H

#include "../../../../core/WebBackend.h"

namespace Otter
{

class QtWebKitPage;

class QtWebKitWebBackend : public WebBackend
{
	Q_OBJECT

public:
	explicit QtWebKitWebBackend(QObject *parent = NULL);

	WebWidget* createWidget(bool isPrivate = false, ContentsWidget *parent = NULL);
	QString getTitle() const;
	QString getDescription() const;
	QString getVersion() const;
	QString getEngineVersion() const;
	QString getUserAgent(const QString &pattern = QString()) const;
	QUrl getHomePage() const;
	QIcon getIcon() const;
	bool requestThumbnail(const QUrl &url, const QSize &size);

protected slots:
	void optionChanged(const QString &option);
	void pageLoaded(bool success);

private:
	QHash<QtWebKitPage*, QPair<QUrl, QSize> > m_thumbnailRequests;
	bool m_isInitialized;

	static QMap<QString, QString> m_userAgentComponents;
	static QMap<QString, QString> m_userAgents;
};

}

#endif
