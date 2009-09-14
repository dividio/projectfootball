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

#include "CTeamPlayerDetailsWindowHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeamPlayers.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"


CTeamPlayerDetailsWindowHandler::CTeamPlayerDetailsWindowHandler(CSinglePlayerGame &game) :
	CWindowHandler("teamPlayerDetails.layout"),
	m_game(game)
{
    LOG_DEBUG("CTeamPlayerDetailsWindowHandler()");
}

CTeamPlayerDetailsWindowHandler::~CTeamPlayerDetailsWindowHandler()
{
    LOG_DEBUG("~CTeamPlayerDetailsWindowHandler()");
}

void CTeamPlayerDetailsWindowHandler::enter()
{
    IDAOFactory *daoFactory = m_game.getIDAOFactory();
    m_selectedTeamPlayer = m_game.getSelectedTeamPlayer();

    m_photo    ->setProperty("Image", "set:"+ m_selectedTeamPlayer->getSPhoto() +" image:"+m_selectedTeamPlayer->getSPhoto()+"_b");
    m_name     ->setText((CEGUI::utf8*)m_selectedTeamPlayer->getSName().c_str());
    m_shortName->setText((CEGUI::utf8*)m_selectedTeamPlayer->getSShortName().c_str());


    m_weight   ->setText((CEGUI::utf8*)m_selectedTeamPlayer->getNWeight_str().c_str());
    m_height   ->setText((CEGUI::utf8*)m_selectedTeamPlayer->getNHeight_str().c_str());

    CDate birthday = m_selectedTeamPlayer->getDBirthday();
    CDate today = CGameEngine::getInstance()->getTimeManager()->getCurrentTime();
    int years = today.getYear() - birthday.getYear();
    if((today.getMonth() < birthday.getMonth()) ||
       (today.getMonth() == birthday.getMonth() && today.getDay() < birthday.getDay())) {
        years = years - 1;
    }
    std::ostringstream yearsAux;
    yearsAux << years;
    m_birthday ->setText(birthday.format("%d/%m/%Y"));
    m_years    ->setText((CEGUI::utf8*)yearsAux.str().c_str());

    CPfCountries *country = daoFactory->getIPfCountriesDAO()->findByXCountry(m_selectedTeamPlayer->getXFkCountry());
    m_country     ->setText((CEGUI::utf8*)gettext(country->getSShortName().c_str()));
    m_country_flag->setProperty("Image", "set:"+ country->getSFlag() +" image:"+country->getSFlag()+"_flag");
    delete country;

    CPfTeamPlayerContracts *contract = daoFactory->getIPfTeamPlayerContractsDAO()->findActiveByXFkTeamPlayer(m_selectedTeamPlayer->getXTeamPlayer_str());
    CPfTeams               *team     = daoFactory->getIPfTeamsDAO()->findByXTeam(contract->getXFkTeam_str());
    m_teamName     ->setText((CEGUI::utf8*)team->getSTeam().c_str());
    m_dateBegin    ->setText(contract->getDBegin().format("%d/%m/%Y"));
    m_dateEnd      ->setText(contract->getDEnd().format("%d/%m/%Y"));
    m_salary       ->setText((CEGUI::utf8*)contract->getNSalary_str().c_str());
    m_releaseClause->setText((CEGUI::utf8*)contract->getNReleaseClause_str().c_str());
    delete team;
    delete contract;
}

void CTeamPlayerDetailsWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();

	m_photo         = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/Photo"));
	m_country_flag  = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/CountryFlag"));
	m_name          = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/Name"));
	m_shortName     = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/ShortName"));
	m_birthday      = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/Birthday"));
	m_weight        = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/Weight"));
	m_height        = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/Height"));
	m_years         = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/Years"));
	m_country       = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/Country"));
	m_teamName      = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/TeamName"));
	m_dateBegin     = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/DateBegin"));
	m_dateEnd       = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/DateEnd"));
	m_salary        = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/Salary"));
	m_releaseClause = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/ReleaseClause"));

    // i18n support
	windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/PlayerDetailsLabel")->setText((CEGUI::utf8*)gettext("Player Details:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/NameLabel")->setText((CEGUI::utf8*)gettext("Name:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/ShortNameLabel")->setText((CEGUI::utf8*)gettext("Short Name:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/BirthdayLabel")->setText((CEGUI::utf8*)gettext("Birthday:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/YearsLabel")->setText((CEGUI::utf8*)gettext("Years:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/WeightLabel")->setText((CEGUI::utf8*)gettext("Weight:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/HeightLabel")->setText((CEGUI::utf8*)gettext("Height:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/CountryLabel")->setText((CEGUI::utf8*)gettext("Country:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/ContractDetailsLabel")->setText((CEGUI::utf8*)gettext("Contract Details:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/TeamNameLabel")->setText((CEGUI::utf8*)gettext("Team:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/DateBeginLabel")->setText((CEGUI::utf8*)gettext("Begin Date:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/DateEndLabel")->setText((CEGUI::utf8*)gettext("End Date:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/SalaryLabel")->setText((CEGUI::utf8*)gettext("Salary:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/ReleaseClauseLabel")->setText((CEGUI::utf8*)gettext("Release Clause:"));
}

void CTeamPlayerDetailsWindowHandler::leave()
{

}

