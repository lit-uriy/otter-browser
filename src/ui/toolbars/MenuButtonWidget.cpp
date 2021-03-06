/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2015 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
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

#include "MenuButtonWidget.h"
#include "../Menu.h"
#include "../ToolBarWidget.h"
#include "../../core/SessionsManager.h"
#include "../../core/Utils.h"

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>

namespace Otter
{

MenuButtonWidget::MenuButtonWidget(QWidget *parent) : ToolButtonWidget(parent),
	m_menu(new Menu(Menu::NoMenuRole, this))
{
	setIcon(Utils::getIcon(QLatin1String("otter-browser"), false));
	setText(tr("Menu"));
	setMenu(m_menu);
	setPopupMode(QToolButton::InstantPopup);
	setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	toolBarModified(ToolBarsManager::MenuBar);

	ToolBarWidget *toolBar = qobject_cast<ToolBarWidget*>(parent);

	if (toolBar)
	{
		disconnect(toolBar, SIGNAL(toolButtonStyleChanged(Qt::ToolButtonStyle)), this, SLOT(setToolButtonStyle(Qt::ToolButtonStyle)));
	}

	connect(ToolBarsManager::getInstance(), SIGNAL(toolBarModified(int)), this, SLOT(toolBarModified(int)));
	connect(m_menu, SIGNAL(aboutToShow()), this, SLOT(updateMenu()));
}

void MenuButtonWidget::toolBarModified(int identifier)
{
	if (identifier == ToolBarsManager::MenuBar)
	{
		if (ToolBarsManager::getToolBarDefinition(ToolBarsManager::MenuBar).visibility == AlwaysVisibleToolBar)
		{
			QToolButton::setMaximumSize(0, 0);
		}
		else
		{
			ToolBarWidget *toolBar = qobject_cast<ToolBarWidget*>(parentWidget());

			if (toolBar)
			{
				setMaximumButtonSize(toolBar->getMaximumButtonSize());
			}
			else
			{
				setMaximumButtonSize(QWIDGETSIZE_MAX);
			}
		}
	}
}

void MenuButtonWidget::updateMenu()
{
	disconnect(m_menu, SIGNAL(aboutToShow()), this, SLOT(updateMenu()));

	QFile file(SessionsManager::getReadableDataPath(QLatin1String("menuButton.json")));
	file.open(QFile::ReadOnly);

	m_menu->load(QJsonDocument::fromJson(file.readAll()).object());
}

}
