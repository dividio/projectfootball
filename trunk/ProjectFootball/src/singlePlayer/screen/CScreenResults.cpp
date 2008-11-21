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

#include <libintl.h>

#include "CScreenResults.h"
#include "../utils/CLog.h"

CScreenResults::CScreenResults(CSinglePlayerGame *game)
    :CScreen("results.layout")
{
    CLog::getInstance()->debug("CScreenResults()");

    m_game = game;

    m_competitionsCombobox      = static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/CompetitionCombo"));
    m_competitionPhasesCombobox = static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/CompetitionPhaseCombo"));
    m_resultsList               = static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/ResultsList"));
    m_backButton				= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/BackButton"));

    m_competitionsCombobox->getEditbox()->setEnabled(false);
    m_competitionPhasesCombobox->getEditbox()->setEnabled(false);

    m_resultsList->setUserColumnDraggingEnabled(false);
    m_resultsList->setUserColumnSizingEnabled(false);
    m_resultsList->setUserSortControlEnabled(false);
    m_resultsList->setWantsMultiClickEvents(true);

    // i18n support
    m_backButton->setText((CEGUI::utf8*)gettext("Back"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/ResultsLabel"))->setText((CEGUI::utf8*)gettext("Results:"));

    // Event handle
    m_competitionsCombobox->subscribeEvent(CEGUI::Combobox::EventListSelectionChanged, CEGUI::Event::Subscriber(&CScreenResults::competitionsComboboxListSelectionChanged, this));
    m_competitionPhasesCombobox->subscribeEvent(CEGUI::Combobox::EventListSelectionChanged, CEGUI::Event::Subscriber(&CScreenResults::competitionPhasesComboboxListSelectionChanged, this));
    m_backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenResults::backButtonClicked, this));

    m_resultsList->addColumn((CEGUI::utf8*)gettext("Home Team"),   0, CEGUI::UDim(0.4,0));
    m_resultsList->addColumn((CEGUI::utf8*)gettext("Goals"),       1, CEGUI::UDim(0.1,0));
    m_resultsList->addColumn((CEGUI::utf8*)gettext("Away Team"),   2, CEGUI::UDim(0.4,0));
    m_resultsList->addColumn((CEGUI::utf8*)gettext("Goals"),       3, CEGUI::UDim(0.1,0));
}

CScreenResults::~CScreenResults()
{
    CLog::getInstance()->debug("~CScreenResults()");
}

void CScreenResults::enter()
{
	CScreen::enter();

    loadCompetitions();
    loadCompetitionPhases();
    loadResultsList();
}

void CScreenResults::loadCompetitions()
{
    m_competitionsCombobox->clearAllSelections();
    m_competitionsCombobox->resetList();
    m_competitionsCombobox->getEditbox()->setText("");

    IPfCompetitionsDAO                      *competitionsDAO    = m_game->getIDAOFactory()->getIPfCompetitionsDAO();
    std::vector<CPfCompetitions*>           *competitionsList   = competitionsDAO->findCompetitions();
    std::vector<CPfCompetitions*>::iterator it;

    for( it=competitionsList->begin(); it!=competitionsList->end(); it++ ){
        CPfCompetitions *competition = (*it);
        m_competitionsCombobox->addItem(new CEGUI::ListboxTextItem(competition->getSCompetition(), competition->getXCompetition()));
    }

    competitionsDAO->freeVector(competitionsList);
}

void CScreenResults::loadCompetitionPhases()
{
    m_competitionPhasesCombobox->clearAllSelections();
    m_competitionPhasesCombobox->resetList();
    m_competitionPhasesCombobox->getEditbox()->setText("");

    CEGUI::ListboxItem *item = m_competitionsCombobox->getSelectedItem();
    if( item!=NULL ){
        IPfCompetitionPhasesDAO                         *competitionPhasesDAO   = m_game->getIDAOFactory()->getIPfCompetitionPhasesDAO();
        std::vector<CPfCompetitionPhases*>              *competitionPhasesList  = competitionPhasesDAO->findByXFkCompetition(item->getID());
        std::vector<CPfCompetitionPhases*>::iterator    it;

        for( it=competitionPhasesList->begin(); it!=competitionPhasesList->end(); it++ ){
            CPfCompetitionPhases *competitionPhase = (*it);
            m_competitionPhasesCombobox->addItem(new CEGUI::ListboxTextItem(competitionPhase->getSCompetitionPhase(), competitionPhase->getXCompetitionPhase()));
        }

        competitionPhasesDAO->freeVector(competitionPhasesList);
    }
}

void CScreenResults::loadResultsList()
{
    m_resultsList->resetList();

    CEGUI::ListboxItem *item = m_competitionPhasesCombobox->getSelectedItem();
    if( item!=NULL ){
        IPfMatchesDAO                       *matchesDAO     = m_game->getIDAOFactory()->getIPfMatchesDAO();
        IPfTeamsDAO                         *teamsDAO       = m_game->getIDAOFactory()->getIPfTeamsDAO();
        IPfGoalsDAO                         *goalsDAO       = m_game->getIDAOFactory()->getIPfGoalsDAO();
        std::vector<CPfMatches*>            *matchesList    = matchesDAO->findByXFkCompetitionPhase(item->getID());
        std::vector<CPfMatches*>::iterator  it;

        for( it=matchesList->begin(); it!=matchesList->end(); it++ ){
            CPfMatches  *match      = (*it);
            CPfTeams    *teamHome   = teamsDAO->findByXTeam(match->getXFkTeamHome());
            CPfTeams    *teamAway   = teamsDAO->findByXTeam(match->getXFkTeamAway());

            int row_idx = m_resultsList->addRow();
            if( match->getLPlayed() ){
                std::vector<CPfGoals*>  *homeGoalsList  = goalsDAO->findByXFkMatchAndXFkTeamScorer(match->getXMatch(), match->getXFkTeamHome());
                std::vector<CPfGoals*>  *awayGoalsList  = goalsDAO->findByXFkMatchAndXFkTeamScorer(match->getXMatch(), match->getXFkTeamAway());

                std::ostringstream nHomeGoals;
                nHomeGoals << homeGoalsList->size();

                std::ostringstream nAwayGoals;
                nAwayGoals << awayGoalsList->size();

                m_resultsList->setItem(new CEGUI::ListboxTextItem(teamHome->getSTeam()),    0, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem(nHomeGoals.str()),        1, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem(teamAway->getSTeam()),    2, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem(nAwayGoals.str()),        3, row_idx);

                goalsDAO->freeVector(homeGoalsList);
                goalsDAO->freeVector(awayGoalsList);
            }else{
                m_resultsList->setItem(new CEGUI::ListboxTextItem(teamHome->getSTeam()),    0, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem("-"),                     1, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem(teamAway->getSTeam()),    2, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem("-"),                     3, row_idx);
            }

            delete teamHome;
            delete teamAway;
        }

        matchesDAO->freeVector(matchesList);
    }
    m_resultsList->getHorzScrollbar()->setVisible(false);
}

bool CScreenResults::competitionsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    loadCompetitionPhases();
    loadResultsList();
    return true;
}

bool CScreenResults::competitionPhasesComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    loadResultsList();
    return true;
}

bool CScreenResults::backButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->previousScreen();
	return true;
}
