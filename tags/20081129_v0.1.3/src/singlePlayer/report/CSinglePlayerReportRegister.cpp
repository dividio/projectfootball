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

#include "CSinglePlayerReportRegister.h"

CSinglePlayerReportRegister::CSinglePlayerReportRegister()
{
    m_matchReportList = new std::vector<CMatchReport*>();
}

CSinglePlayerReportRegister::~CSinglePlayerReportRegister()
{
    std::vector<CMatchReport*>::iterator it;
    for( it=m_matchReportList->begin(); it!=m_matchReportList->end(); it++ ){
        delete (*it);
    }
    delete m_matchReportList;
}

void CSinglePlayerReportRegister::generateMatchReport(int xMatch)
{
    CMatchReport *matchReport = new CMatchReport(xMatch);
    m_matchReportList->push_back(matchReport);
}

std::vector<CMatchReport*>* CSinglePlayerReportRegister::getMatchReportList()
{
    return m_matchReportList;
}
