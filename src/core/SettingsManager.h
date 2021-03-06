/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2014 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
* Copyright (C) 2014 Piotr Wójcik <chocimier@tlen.pl>
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

#ifndef OTTER_SETTINGSMANAGER_H
#define OTTER_SETTINGSMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVariant>

namespace Otter
{

class SettingsManager : public QObject
{
	Q_OBJECT

public:
	static void createInstance(const QString &path, QObject *parent = NULL);
	static void registerOption(const QString &key);
	static void removeOverride(const QUrl &url, const QString &key = QString());
	static void setDefaultValue(const QString &key, const QVariant &value);
	static void setValue(const QString &key, const QVariant &value, const QUrl &url = QUrl());
	static SettingsManager* getInstance();
	static QVariant getDefaultValue(const QString &key);
	static QVariant getValue(const QString &key, const QUrl &url = QUrl());
	static bool hasOverride(const QUrl &url, const QString &key = QString());

protected:
	explicit SettingsManager(QObject *parent = NULL);

private:
	static SettingsManager *m_instance;
	static QString m_globalPath;
	static QString m_overridePath;
	static QHash<QString, QVariant> m_defaults;

signals:
	void valueChanged(QString key, QVariant value);
};

}

#endif
