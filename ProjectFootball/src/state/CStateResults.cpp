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

#include "CStateResults.h"
#include "../utils/CLog.h"
#include "../engine/CGameEngine.h"

CStateResults::CStateResults()
    :CState()
{
    CLog::getInstance()->debug("CStateResults()");

    CEGUI::WindowManager *ceguiWM = &(CEGUI::WindowManager::getSingleton());
    m_sheet = ceguiWM->loadWindowLayout((CEGUI::utf8*)"results.layout");

    m_competitionsCombo         = static_cast<CEGUI::Combobox*>(ceguiWM->getWindow((CEGUI::utf8*)"Results/CompetitionCombo"));
    m_competitionPhasesCombo    = static_cast<CEGUI::Combobox*>(ceguiWM->getWindow((CEGUI::utf8*)"Results/CompetitionPhaseCombo"));
    m_resultsList               = static_cast<CEGUI::MultiColumnList*>(ceguiWM->getWindow((CEGUI::utf8*)"Results/ResultsList"));

    m_competitionsCombo->getEditbox()->setEnabled(false);
    m_competitionsCombo->subscribeEvent(CEGUI::Combobox::EventListSelectionChanged, CEGUI::Event::Subscriber(&CStateResults::handleCompetitionChange, this));

    m_competitionPhasesCombo->getEditbox()->setEnabled(false);
    m_competitionPhasesCombo->subscribeEvent(CEGUI::Combobox::EventListSelectionChanged, CEGUI::Event::Subscriber(&CStateResults::handleCompetitionPhaseChange, this));

    m_resultsList->setUserColumnDraggingEnabled(false);
    m_resultsList->setUserColumnSizingEnabled(false);
    m_resultsList->setUserSortControlEnabled(false);
    m_resultsList->setWantsMultiClickEvents(true);

    // i18n support
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Results/ResultsLabel"))->setText((CEGUI::utf8*)gettext("Results:"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Results/BackButton"))->setText((CEGUI::utf8*)gettext("Back"));

    m_resultsList->addColumn((CEGUI::utf8*)gettext("Home Team"),   0, CEGUI::UDim(0.4,0));
    m_resultsList->addColumn((CEGUI::utf8*)gettext("Goals"),       1, CEGUI::UDim(0.1,0));
    m_resultsList->addColumn((CEGUI::utf8*)gettext("Away Team"),   2, CEGUI::UDim(0.4,0));
    m_resultsList->addColumn((CEGUI::utf8*)gettext("Goals"),       3, CEGUI::UDim(0.1,0));
}

CStateResults::~CStateResults()
{
    CLog::getInstance()->debug("~CStateResults()");
}

CStateResults* CStateResults::getInstance()
{
    static CStateResults instance;
    return &instance;
}

void CStateResults::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

    loadCompetitions();
    loadCompetitionPhases();
    loadResultsList();
}

void CStateResults::forcedLeave()
{

}

bool CStateResults::leave()
{
    return true;
}

void CStateResults::update()
{
}

void CStateResults::loadCompetitions()
{
    m_competitionsCombo->clearAllSelections();
    m_competitionsCombo->resetList();
    m_competitionsCombo->getEditbox()->setText("");

    IPfCompetitionsDAO                      *competitionsDAO    = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfCompetitionsDAO();
    std::vector<CPfCompetitions*>           *competitionsList   = competitionsDAO->findCompetitions();
    std::vector<CPfCompetitions*>::iterator it;

    for( it=competitionsList->begin(); it!=competitionsList->end(); it++ ){
        CPfCompetitions *competition = (*it);
        m_competitionsCombo->addItem(new CEGUI::ListboxTextItem(competition->getSCompetition(), competition->getXCompetition()));
    }

    competitionsDAO->freeVector(competitionsList);
}

void CStateResults::loadCompetitionPhases()
{
    m_competitionPhasesCombo->clearAllSelections();
    m_competitionPhasesCombo->resetList();
    m_competitionPhasesCombo->getEditbox()->setText("");

    CEGUI::ListboxItem *item = m_competitionsCombo->getSelectedItem();
    if( item!=NULL ){
        IPfCompetitionPhasesDAO                         *competitionPhasesDAO   = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfCompetitionPhasesDAO();
        std::vector<CPfCompetitionPhases*>              *competitionPhasesList  = competitionPhasesDAO->findByXFkCompetition(item->getID());
        std::vector<CPfCompetitionPhases*>::iterator    it;

        for( it=competitionPhasesList->begin(); it!=competitionPhasesList->end(); it++ ){
            CPfCompetitionPhases *competitionPhase = (*it);
            m_competitionPhasesCombo->addItem(new CEGUI::ListboxTextItem(competitionPhase->getSCompetitionPhase(), competitionPhase->getXCompetitionPhase()));
        }

        competitionPhasesDAO->freeVector(competitionPhasesList);
    }
}

void CStateResults::loadResultsList()
{
    m_resultsList->resetList();

    CEGUI::ListboxItem *item = m_competitionPhasesCombo->getSelectedItem();
    if( item!=NULL ){
        IPfMatchesDAO                       *matchesDAO     = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfMatchesDAO();
        IPfTeamsDAO                         *teamsDAO       = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO();
        IPfGoalsDAO                         *goalsDAO       = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfGoalsDAO();
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

bool CStateResults::handleCompetitionChange(const CEGUI::EventArgs& e)
{
    loadCompetitionPhases();
    loadResultsList();
    return true;
}

bool CStateResults::handleCompetitionPhaseChange(const CEGUI::EventArgs& e)
{
    loadResultsList();
    return true;
}
