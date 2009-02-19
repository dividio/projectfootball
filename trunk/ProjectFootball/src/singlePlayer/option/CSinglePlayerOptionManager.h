/******************************************************************************
* Copyright (C) 2008 - Ikaro Games   www.ikarogames.com                       *
*                                                                             *
* This program is free software; you can redistribute it and/or               *
* modify it under the terms of the GNU General Public License                 *
* as published by the Free Software Foundation; either version 2              *
* of the License, or (at your option) any later version.                      *
*                                                                             *
* This program is distributed in the hope that it will be useful,             *
* but WITHOUT ANY WARRANTY; without even the implied warranty of              *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
* GNU General Public License for more details.                                *
*                                                                             *
* You should have received a copy of the GNU General Public License           *
* along with this program; if not, write to the Free Software                 *
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. *
*                                                                             *
*                                                                             *
******************************************************************************/

#ifndef CSINGLEPLAYEROPTIONMANAGER_H_
#define CSINGLEPLAYEROPTIONMANAGER_H_

#include "../../utils/COptionManager.h"
#include "../db/dao/IPfGameOptionsDAO.h"

class CSinglePlayerOptionManager : public COptionManager
{
public:
	/**
	 * Constructor/Destructor
	 */
	CSinglePlayerOptionManager(IPfGameOptionsDAO *gameOptionsDAO);
	virtual ~CSinglePlayerOptionManager();


    /**
     * Load the options from the config file
     */
    virtual void loadOptions();


    /**
     * Save the options in the config file
     */
    virtual void saveOptions();


    /**
     * Set the default values of options
     */
    virtual void setDefaultValues();


    /**
     * Get/Set the value of the option
     */
    // Game options
    int			getGamePlayerTeam();
    void		setGamePlayerTeam(int xPlayerTeam);
    bool		getGameNew();
    void		setGameNew(bool newGame);

    // Match options
    bool		getMatchResultMode();
    void		setMatchResultMode(bool mode);


private:
    IPfGameOptionsDAO	*m_gameOptionsDAO;
};

#endif /*CSINGLEPLAYEROPTIONMANAGER_H_*/
