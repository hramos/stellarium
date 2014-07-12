/*
 * Stellarium
 * Copyright (C) 2014 Marcos Cardinot
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#include "AOLandscape.hpp"
#include "LandscapeMgr.hpp"

AOLandscape::AOLandscape(StelAddOnDAO* pStelAddOnDAO)
	: m_pStelAddOnDAO(pStelAddOnDAO)
{
}

AOLandscape::~AOLandscape()
{
}

void AOLandscape::checkInstalledAddOns() const
{
	QDir landscapeDestination = GETSTELMODULE(LandscapeMgr)->getLandscapeDir();
	QStringList landscapes = GETSTELMODULE(LandscapeMgr)->getUserLandscapeIDs();
	foreach (QString landscape, landscapes) {
		if (landscapeDestination.cd(landscape))
		{
			m_pStelAddOnDAO->updateInstalledAddon(landscape % ".zip", "1.0", landscapeDestination.absolutePath());
			landscapeDestination.cdUp();
		}
	}
}

void AOLandscape::installFromFile(const QString& filePath) const
{
	QString ref = GETSTELMODULE(LandscapeMgr)->installLandscapeFromArchive(filePath);
	if(!ref.isEmpty())
	{
		qWarning() << "FAILED to install " << filePath;
	}
	// update database
	QDir landscapeDestination = GETSTELMODULE(LandscapeMgr)->getLandscapeDir();
	if (landscapeDestination.cd(ref))
	{
		m_pStelAddOnDAO->updateInstalledAddon(ref % ".zip", "1.0",
				     landscapeDestination.absolutePath());
	}
}
