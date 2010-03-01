/******************************************************************************
* Copyright (C) 2010 - Ikaro Games   www.ikarogames.com                       *
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
*       Version: 1.23                                                         *
******************************************************************************/

#ifndef IDAOFACTORY_H_
#define IDAOFACTORY_H_

#include "../IPfCompetitionPhasesDAO.h"
#include "../IPfRankingDAO.h"
#include "../IPfTeamAveragesDAO.h"
#include "../IPfFormationsDAO.h"
#include "../IPfTeamsByCompetitionsDAO.h"
#include "../IPfConfederationsDAO.h"
#include "../IPfTeamPlayersDAO.h"
#include "../IPfStadiumsDAO.h"
#include "../IPfTeamsDAO.h"
#include "../IPfTeamPlayerAveragesDAO.h"
#include "../IPfCompetitionsBySeasonDAO.h"
#include "../IPfSeasonsDAO.h"
#include "../IPfDemarcationsDAO.h"
#include "../IPfTeamPlayerContractsDAO.h"
#include "../IPfStrategicPositionsDAO.h"
#include "../IPfCoachesDAO.h"
#include "../IPfMatchesDAO.h"
#include "../IPfGameOptionsDAO.h"
#include "../IPfGoalsDAO.h"
#include "../IPfRolesDAO.h"
#include "../IPfCountriesDAO.h"
#include "../IPfCoachContractsDAO.h"
#include "../IPfRolesByTeamPlayersDAO.h"
#include "../IPfFormationsByCoachesDAO.h"
#include "../IPfScorersDAO.h"
#include "../IPfCompetitionsDAO.h"

class IDAOFactory
{
public:
    IDAOFactory(){}
    virtual ~IDAOFactory(){}

    virtual bool executeScript(const std::string &script) =0;
    virtual bool executeScriptFile(const char *scriptFile) =0;

    virtual bool beginTransaction() =0;
    virtual bool commit() =0;
    virtual bool rollback() =0;

    virtual void save() =0;

    virtual IPfCompetitionPhasesDAO* getIPfCompetitionPhasesDAO() =0;
    virtual IPfRankingDAO* getIPfRankingDAO() =0;
    virtual IPfTeamAveragesDAO* getIPfTeamAveragesDAO() =0;
    virtual IPfFormationsDAO* getIPfFormationsDAO() =0;
    virtual IPfTeamsByCompetitionsDAO* getIPfTeamsByCompetitionsDAO() =0;
    virtual IPfConfederationsDAO* getIPfConfederationsDAO() =0;
    virtual IPfTeamPlayersDAO* getIPfTeamPlayersDAO() =0;
    virtual IPfStadiumsDAO* getIPfStadiumsDAO() =0;
    virtual IPfTeamsDAO* getIPfTeamsDAO() =0;
    virtual IPfTeamPlayerAveragesDAO* getIPfTeamPlayerAveragesDAO() =0;
    virtual IPfCompetitionsBySeasonDAO* getIPfCompetitionsBySeasonDAO() =0;
    virtual IPfSeasonsDAO* getIPfSeasonsDAO() =0;
    virtual IPfDemarcationsDAO* getIPfDemarcationsDAO() =0;
    virtual IPfTeamPlayerContractsDAO* getIPfTeamPlayerContractsDAO() =0;
    virtual IPfStrategicPositionsDAO* getIPfStrategicPositionsDAO() =0;
    virtual IPfCoachesDAO* getIPfCoachesDAO() =0;
    virtual IPfMatchesDAO* getIPfMatchesDAO() =0;
    virtual IPfGameOptionsDAO* getIPfGameOptionsDAO() =0;
    virtual IPfGoalsDAO* getIPfGoalsDAO() =0;
    virtual IPfRolesDAO* getIPfRolesDAO() =0;
    virtual IPfCountriesDAO* getIPfCountriesDAO() =0;
    virtual IPfCoachContractsDAO* getIPfCoachContractsDAO() =0;
    virtual IPfRolesByTeamPlayersDAO* getIPfRolesByTeamPlayersDAO() =0;
    virtual IPfFormationsByCoachesDAO* getIPfFormationsByCoachesDAO() =0;
    virtual IPfScorersDAO* getIPfScorersDAO() =0;
    virtual IPfCompetitionsDAO* getIPfCompetitionsDAO() =0;

};
#endif /*IDAOFACTORY_H_*/
