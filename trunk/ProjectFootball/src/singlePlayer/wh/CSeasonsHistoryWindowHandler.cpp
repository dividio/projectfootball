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

#include "CSeasonsHistoryWindowHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"


CSeasonsHistoryWindowHandler::CSeasonsHistoryWindowHandler(CSinglePlayerGame &game) :
	CWindowHandler("seasonsHistory.layout"),
	m_game(game),
	m_initiated(false)
{
    LOG_DEBUG("CSeasonsHistoryWindowHandler()");
}

CSeasonsHistoryWindowHandler::~CSeasonsHistoryWindowHandler()
{
    LOG_DEBUG("~CSeasonsHistoryWindowHandler()");

    if( m_initiated ){
        m_seasonsList->removeColumnWithID(0);
        m_seasonsList->removeColumnWithID(1);
        m_seasonsList->removeColumnWithID(2);
    }
}

void CSeasonsHistoryWindowHandler::enter()
{
    loadSeasonsHistory();
}

void CSeasonsHistoryWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();

	m_seasonsList = static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"SeasonsHistory/SeasonsList"));
	m_seasonsList->addColumn((CEGUI::utf8*)gettext("Team"), 0, CEGUI::UDim(0.40,0));
	m_seasonsList->addColumn((CEGUI::utf8*)gettext("Competition"), 1, CEGUI::UDim(0.30,0));
	m_seasonsList->addColumn((CEGUI::utf8*)gettext("Season"), 2, CEGUI::UDim(0.30,0));
	m_seasonsList->setUserColumnDraggingEnabled(false);
	m_seasonsList->setUserColumnSizingEnabled(false);
	m_seasonsList->setUserSortControlEnabled(false);

    // i18n support
	windowMngr.getWindow((CEGUI::utf8*)"SeasonsHistory/SeasonsLabel")->setText((CEGUI::utf8*)gettext("Seasons:"));

	// events
	registerEventConnection(m_seasonsList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CSeasonsHistoryWindowHandler::seasonsListboxSelectionChanged, this)));
}

void CSeasonsHistoryWindowHandler::leave()
{

}

void CSeasonsHistoryWindowHandler::loadSeasonsHistory()
{
    m_seasonsList->resetList();
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("MultiListSelectionBrush");

    IDAOFactory                		*daoFactory              	  = m_game.getIDAOFactory();
    IPfSeasonsDAO              		*seasonsDAO              	  = daoFactory->getIPfSeasonsDAO();
    IPfTeamsDAO                		*teamsDAO                	  = daoFactory->getIPfTeamsDAO();
    IPfCoachesDAO              		*coachesDAO              	  = daoFactory->getIPfCoachesDAO();
    IPfCoachContractsDAO       		*coachContractsDAO       	  = daoFactory->getIPfCoachContractsDAO();
    IPfCompetitionPhasesBySeasonDAO *competitionPhasesBySeasonDAO = daoFactory->getIPfCompetitionPhasesBySeasonDAO();
    IPfCompetitionPhasesDAO    		*competitionPhasesDAO      	  = daoFactory->getIPfCompetitionPhasesDAO();
    IPfCompetitionsDAO         		*competitionsDAO         	  = daoFactory->getIPfCompetitionsDAO();

    int XCoach = m_game.getOptionManager()->getGamePlayerCoach();
    CPfCoaches *coach = coachesDAO->findByXCoach(XCoach);
    CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"SeasonsHistory/CoachNameLabel")->setText((CEGUI::utf8*)coach->getSName_str().c_str());
    delete coach;

    std::vector<CPfSeasons*> *seasons = seasonsDAO->findAll();
    std::vector<CPfSeasons*>::iterator itSeason;
    for( itSeason=seasons->begin(); itSeason!=seasons->end(); itSeason++ ){
        CPfSeasons *season = (*itSeason);
        int XSeason = season->getXSeason();
        std::vector<CPfCoachContracts*> *contracts = coachContractsDAO->findByXFkCoachAndXSeason(XCoach, XSeason);
        std::vector<CPfCoachContracts*>::iterator itContract;
        for( itContract=contracts->begin(); itContract!=contracts->end(); itContract++ ){
            CPfCoachContracts *contract = (*itContract);
            int row_idx = m_seasonsList->addRow();

            CPfTeams *team = teamsDAO->findByXTeam(contract->getXFkTeam_str());
            CPfCompetitionPhasesBySeason *competitionPhaseBySeason = competitionPhasesBySeasonDAO->findByXFkSeasonAndXTeam(XSeason, team->getXTeam());
            CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)team->getSTeam_str().c_str(), competitionPhaseBySeason->getXCompetitionPhaseBySeason());
            item->setSelectionBrushImage(sel_img);
            m_seasonsList->setItem(item, 0, row_idx);
            delete team;

            CPfCompetitionPhases *competitionPhase = competitionPhasesDAO->findByXCompetitionPhase(competitionPhaseBySeason->getXFkCompetitionPhase());
            CPfCompetitions *competition = competitionsDAO->findByXCompetition(competitionPhase->getXFkCompetition());
            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)competition->getSCompetition_str().c_str(), competitionPhaseBySeason->getXCompetitionPhaseBySeason());
            item->setSelectionBrushImage(sel_img);
            m_seasonsList->setItem(item, 1, row_idx);
            delete competition;
            delete competitionPhase;

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)season->getSSeason_str().c_str(), competitionPhaseBySeason->getXCompetitionPhaseBySeason());
            item->setSelectionBrushImage(sel_img);
            m_seasonsList->setItem(item, 2, row_idx);
            delete competitionPhaseBySeason;
        }
        if(contracts->empty()) {
            int row_idx = m_seasonsList->addRow();

            CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)gettext("Unemployed"), -1);
            item->setSelectionBrushImage(sel_img);
            m_seasonsList->setItem(item, 0, row_idx);

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)"", -1);
            item->setSelectionBrushImage(sel_img);
            m_seasonsList->setItem(item, 1, row_idx);

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)season->getSSeason_str().c_str(), -1);
            item->setSelectionBrushImage(sel_img);
            m_seasonsList->setItem(item, 2, row_idx);
        }
        coachContractsDAO->freeVector(contracts);
    }
    seasonsDAO->freeVector(seasons);

    m_seasonsList->getHorzScrollbar()->setVisible(false);
    m_seasonsList->getVertScrollbar()->setVisible(true);
}

bool CSeasonsHistoryWindowHandler::seasonsListboxSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *currentItem = m_seasonsList->getFirstSelectedItem();

    if( currentItem != NULL ) {
        int currentRow  = m_seasonsList->getItemRowIndex(currentItem);
        int XCompetitionPhaseBySeason = currentItem->getID();
        if(XCompetitionPhaseBySeason != -1) {
            IPfCompetitionPhasesBySeasonDAO *competitionPhasesBySeasonDAO = m_game.getIDAOFactory()->getIPfCompetitionPhasesBySeasonDAO();
            CPfCompetitionPhasesBySeason *selectedCompetitionPhaseBySeason = competitionPhasesBySeasonDAO->findByXCompetitionPhaseBySeason(XCompetitionPhaseBySeason);
            m_game.setSelectedCompetitionPhaseBySeason(selectedCompetitionPhaseBySeason);
            CGameEngine::getInstance()->getWindowManager()->nextScreen("SeasonSummary");
            delete selectedCompetitionPhaseBySeason;
        }
    }
    return true;
}
