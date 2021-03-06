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
*       Version: 1.18                                                         *
******************************************************************************/

#ifndef CDAOFACTORYSQLITE_H_
#define CDAOFACTORYSQLITE_H_

#include <sqlite3.h>
#include <string>

#include "../../../dao/factory/IDAOFactory.h"

#include "../../../dao/IPfCompetitionPhasesDAO.h"
#include "../../../dao/IPfRankingDAO.h"
#include "../../../dao/IPfGameStatesDAO.h"
#include "../../../dao/IPfMatchesDAO.h"
#include "../../../dao/IPfGameOptionsDAO.h"
#include "../../../dao/IPfRegisteredTeamsDAO.h"
#include "../../../dao/IPfConfederationsDAO.h"
#include "../../../dao/IPfTeamPlayerContractsDAO.h"
#include "../../../dao/IPfGoalsDAO.h"
#include "../../../dao/IPfTeamPlayersDAO.h"
#include "../../../dao/IPfCountriesDAO.h"
#include "../../../dao/IPfCompetitionsDAO.h"
#include "../../../dao/IPfTeamsDAO.h"

#include "../CPfCompetitionPhasesDAOSQLite.h"
#include "../CPfRankingDAOSQLite.h"
#include "../CPfGameStatesDAOSQLite.h"
#include "../CPfMatchesDAOSQLite.h"
#include "../CPfGameOptionsDAOSQLite.h"
#include "../CPfRegisteredTeamsDAOSQLite.h"
#include "../CPfConfederationsDAOSQLite.h"
#include "../CPfTeamPlayerContractsDAOSQLite.h"
#include "../CPfGoalsDAOSQLite.h"
#include "../CPfTeamPlayersDAOSQLite.h"
#include "../CPfCountriesDAOSQLite.h"
#include "../CPfCompetitionsDAOSQLite.h"
#include "../CPfTeamsDAOSQLite.h"

class CDAOFactorySQLite : public IDAOFactory
{
public:
    CDAOFactorySQLite(const std::string &filepath);
    virtual ~CDAOFactorySQLite();

    void closeSQLite();
    void openSQLite(const std::string &filepath);

    virtual bool executeScript(const std::string &script);
    virtual bool executeScriptFile(const char *scriptFile);

    virtual bool beginTransaction();
    virtual bool commit();
    virtual bool rollback();

    virtual IPfCompetitionPhasesDAO* getIPfCompetitionPhasesDAO();
    virtual IPfRankingDAO* getIPfRankingDAO();
    virtual IPfGameStatesDAO* getIPfGameStatesDAO();
    virtual IPfMatchesDAO* getIPfMatchesDAO();
    virtual IPfGameOptionsDAO* getIPfGameOptionsDAO();
    virtual IPfRegisteredTeamsDAO* getIPfRegisteredTeamsDAO();
    virtual IPfConfederationsDAO* getIPfConfederationsDAO();
    virtual IPfTeamPlayerContractsDAO* getIPfTeamPlayerContractsDAO();
    virtual IPfGoalsDAO* getIPfGoalsDAO();
    virtual IPfTeamPlayersDAO* getIPfTeamPlayersDAO();
    virtual IPfCountriesDAO* getIPfCountriesDAO();
    virtual IPfCompetitionsDAO* getIPfCompetitionsDAO();
    virtual IPfTeamsDAO* getIPfTeamsDAO();


private:
    sqlite3     *m_database;
    std::string m_filepath;

    CPfCompetitionPhasesDAOSQLite *m_PfCompetitionPhasesDAOSQLite;
    CPfRankingDAOSQLite *m_PfRankingDAOSQLite;
    CPfGameStatesDAOSQLite *m_PfGameStatesDAOSQLite;
    CPfMatchesDAOSQLite *m_PfMatchesDAOSQLite;
    CPfGameOptionsDAOSQLite *m_PfGameOptionsDAOSQLite;
    CPfRegisteredTeamsDAOSQLite *m_PfRegisteredTeamsDAOSQLite;
    CPfConfederationsDAOSQLite *m_PfConfederationsDAOSQLite;
    CPfTeamPlayerContractsDAOSQLite *m_PfTeamPlayerContractsDAOSQLite;
    CPfGoalsDAOSQLite *m_PfGoalsDAOSQLite;
    CPfTeamPlayersDAOSQLite *m_PfTeamPlayersDAOSQLite;
    CPfCountriesDAOSQLite *m_PfCountriesDAOSQLite;
    CPfCompetitionsDAOSQLite *m_PfCompetitionsDAOSQLite;
    CPfTeamsDAOSQLite *m_PfTeamsDAOSQLite;

};
#endif /*CDAOFACTORYSQLITE_H_*/
