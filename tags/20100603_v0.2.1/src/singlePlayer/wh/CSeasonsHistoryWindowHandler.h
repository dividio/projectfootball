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

#ifndef CSEASONSHISTORYWINDOWHANDLER_H_
#define CSEASONSHISTORYWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>
#include "../../engine/wm/CWindowHandler.h"

//Forward declarations
class CSinglePlayerGame;


class CSeasonsHistoryWindowHandler : public CWindowHandler
{
public:
    CSeasonsHistoryWindowHandler(CSinglePlayerGame &game);
    virtual ~CSeasonsHistoryWindowHandler();

    virtual void enter();
    virtual void init();
    virtual void leave();

private:
    bool seasonsListboxSelectionChanged(const CEGUI::EventArgs& e);

    void loadSeasonsHistory();

    CEGUI::MultiColumnList  *m_seasonsList;

    CSinglePlayerGame       &m_game;
    bool                    m_initiated;
};

#endif /*CSEASONSHISTORYWINDOWHANDLER_H_*/
