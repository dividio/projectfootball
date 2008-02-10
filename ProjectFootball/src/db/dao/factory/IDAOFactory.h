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
*       generated by dia/DAOcodegen.py                                        *
*       Version: 1.11                                                          *
******************************************************************************/

#ifndef IDAOFACTORY_H_
#define IDAOFACTORY_H_

#include "../IPfGoalsDAO.h"
#include "../IPfGameStatesDAO.h"
#include "../IPfTeamsDAO.h"
#include "../IPfMatchesDAO.h"
#include "../IPfGameOptionsDAO.h"

class IDAOFactory
{
public:
    IDAOFactory(){}
    virtual ~IDAOFactory(){}

    virtual bool createSchema() =0;

    virtual bool beginTransaction() =0;
    virtual bool commit() =0;
    virtual bool rollback() =0;

    virtual IPfGoalsDAO* getIPfGoalsDAO() =0;
    virtual IPfGameStatesDAO* getIPfGameStatesDAO() =0;
    virtual IPfTeamsDAO* getIPfTeamsDAO() =0;
    virtual IPfMatchesDAO* getIPfMatchesDAO() =0;
    virtual IPfGameOptionsDAO* getIPfGameOptionsDAO() =0;

};
#endif /*IDAOFACTORY_H_*/
