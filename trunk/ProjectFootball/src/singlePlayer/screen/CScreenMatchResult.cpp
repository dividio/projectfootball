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

#include "CScreenMatchResult.h"
#include "../utils/CLog.h"

CScreenMatchResult::CScreenMatchResult(CSinglePlayerGame *game)
 :CScreen("matchResult.layout")
{
    CLog::getInstance()->debug("CScreenMatchResult()");

    m_game = game;
    m_match = NULL;

    m_competitionName		= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/Competition"));
    m_competitionPhaseName	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/CompetitionPhase"));
    m_homeName				= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/HomeName"));
    m_awayName				= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/AwayName"));
    m_homeScore            	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/HomeScore"));
    m_awayScore            	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/AwayScore"));
    m_homeEventsList       	= static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/HomeTeamEventsList"));
    m_awayEventsList       	= static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/AwayTeamEventsList"));
    m_homeLogo             	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/HomeTeamLogo"));
    m_awayLogo             	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/AwayTeamLogo"));
    m_continueButton		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/ContinueButton"));

    // Event handle
    m_continueButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMatchResult::continueButtonClicked, this));

    // i18n support
    m_continueButton->setText((CEGUI::utf8*)gettext("Continue"));

    m_homeEventsList->addColumn((CEGUI::utf8*)gettext("min"), 0, CEGUI::UDim(0.2,0));
    m_homeEventsList->addColumn((CEGUI::utf8*)gettext("Event"), 1, CEGUI::UDim(0.8,0));
    m_awayEventsList->addColumn((CEGUI::utf8*)gettext("min"), 0, CEGUI::UDim(0.2,0));
    m_awayEventsList->addColumn((CEGUI::utf8*)gettext("Event"), 1, CEGUI::UDim(0.8,0));

    m_homeEventsList->setUserColumnDraggingEnabled(false);
    m_homeEventsList->setUserColumnSizingEnabled(false);
    m_homeEventsList->setUserSortControlEnabled(true);
    m_awayEventsList->setUserColumnDraggingEnabled(false);
    m_awayEventsList->setUserColumnSizingEnabled(false);
    m_awayEventsList->setUserSortControlEnabled(true);
    m_homeEventsList->getHorzScrollbar()->setVisible(false);
    m_awayEventsList->getHorzScrollbar()->setVisible(false);
}

CScreenMatchResult::~CScreenMatchResult()
{
    CLog::getInstance()->debug("~CScreenMatchResult()");
    delete m_match;
}

void CScreenMatchResult::enter()
{
    CScreen::enter();

    simulateMatches();

    IPfMatchesDAO *matchesDAO = m_game->getIDAOFactory()->getIPfMatchesDAO();
    m_match = matchesDAO->findLastPlayerTeamMatch();
    loadMatchInfo(m_match);
}

void CScreenMatchResult::leave()
{
    m_homeEventsList->resetList();
    m_awayEventsList->resetList();
}

void CScreenMatchResult::loadMatchInfo(CPfMatches *match)
{
    IDAOFactory             *daoFactory           = m_game->getIDAOFactory();
    IPfMatchesDAO           *matchesDAO           = daoFactory->getIPfMatchesDAO();
    IPfGoalsDAO             *goalsDAO             = daoFactory->getIPfGoalsDAO();
    IPfTeamPlayersDAO       *playersDAO           = daoFactory->getIPfTeamPlayersDAO();
    IPfCompetitionsDAO      *competitionsDAO      = daoFactory->getIPfCompetitionsDAO();
    IPfCompetitionPhasesDAO *competitionPhasesDAO = daoFactory->getIPfCompetitionPhasesDAO();
    IPfTeamsDAO             *teamsDAO             = daoFactory->getIPfTeamsDAO();

    CPfTeams                *homeTeam         = teamsDAO->findByXTeam(match->getXFkTeamHome());
    CPfTeams                *awayTeam         = teamsDAO->findByXTeam(match->getXFkTeamAway());
    CPfCompetitionPhases    *competitionPhase = competitionPhasesDAO->findByXCompetitionPhase(match->getXFkCompetitionPhase());
    CPfCompetitions         *competition      = competitionsDAO->findByXCompetition(competitionPhase->getXFkCompetition());
    std::vector<CPfGoals*>  *homeGoalsList    = goalsDAO->findByXFkMatchAndXFkTeamScorer(match->getXMatch(), homeTeam->getXTeam());
    std::vector<CPfGoals*>  *awayGoalsList    = goalsDAO->findByXFkMatchAndXFkTeamScorer(match->getXMatch(), awayTeam->getXTeam());

    std::ostringstream nHomeGoals;
    nHomeGoals << homeGoalsList->size();
    std::ostringstream nAwayGoals;
    nAwayGoals << awayGoalsList->size();

    std::string homeName = homeTeam->getSTeam();
    std::string awayName = awayTeam->getSTeam();
    m_competitionName->setProperty("Text", competition->getSCompetition().c_str());
    m_competitionPhaseName->setProperty("Text", competitionPhase->getSCompetitionPhase().c_str());
    m_homeName->setProperty("Text", homeName.c_str());
    m_awayName->setProperty("Text", awayName.c_str());
    m_homeScore->setProperty("Text", nHomeGoals.str());
    m_awayScore->setProperty("Text", nAwayGoals.str());
    //Loading Home logo
    CEGUI::String imagesetHomeName = "TeamLogo" + homeTeam->getXTeam_str();
    if(!CEGUI::ImagesetManager::getSingleton().isImagesetPresent(imagesetHomeName)) {
        CEGUI::ImagesetManager::getSingleton().createImagesetFromImageFile(imagesetHomeName, homeTeam->getSLogo());
    }
    m_homeLogo->setProperty("Image", "set:"+ imagesetHomeName +" image:full_image");

    //Loading Away logo
    CEGUI::String imagesetAwayName = "TeamLogo" + awayTeam->getXTeam_str();
    if(!CEGUI::ImagesetManager::getSingleton().isImagesetPresent(imagesetAwayName)) {
        CEGUI::ImagesetManager::getSingleton().createImagesetFromImageFile(imagesetAwayName, awayTeam->getSLogo());
    }
    m_awayLogo->setProperty("Image", "set:"+ imagesetAwayName +" image:full_image");

    std::vector<CPfGoals*>::iterator it;
    CEGUI::ListboxTextItem *item;
    CPfTeamPlayers *player;
    char event[40];

    for( it=homeGoalsList->begin(); it!=homeGoalsList->end(); it++ ){
        CPfGoals *goal = (*it);

        int row_idx = m_homeEventsList->addRow();

        item = new CEGUI::ListboxTextItem(goal->getNMinute_str());
        m_homeEventsList->setItem(item, 0, row_idx);

        player = playersDAO->findByXTeamPlayer(goal->getXFkTeamPlayerScorer());
        sprintf(event, gettext("Goal by %s"), player->getSName().c_str());
        item = new CEGUI::ListboxTextItem(event);
        m_homeEventsList->setItem(item, 1, row_idx);
    }
    goalsDAO->freeVector(homeGoalsList);

    for( it=awayGoalsList->begin(); it!=awayGoalsList->end(); it++ ){
        CPfGoals *goal = (*it);

        int row_idx = m_awayEventsList->addRow();

        item = new CEGUI::ListboxTextItem(goal->getNMinute_str());
        m_awayEventsList->setItem(item, 0, row_idx);

        player = playersDAO->findByXTeamPlayer(goal->getXFkTeamPlayerScorer());
        sprintf(event, gettext("Goal by %s"), player->getSName().c_str());
        item = new CEGUI::ListboxTextItem(event);
        m_awayEventsList->setItem(item, 1, row_idx);
    }
    goalsDAO->freeVector(awayGoalsList);

    m_homeEventsList->setSortColumn(0);
    m_awayEventsList->setSortColumn(0);
    m_homeEventsList->setSortDirection(CEGUI::ListHeaderSegment::Descending);
    m_awayEventsList->setSortDirection(CEGUI::ListHeaderSegment::Descending);
    m_homeEventsList->handleUpdatedItemData();
    m_awayEventsList->handleUpdatedItemData();
    m_homeEventsList->getHorzScrollbar()->setVisible(false);
    m_awayEventsList->getHorzScrollbar()->setVisible(false);

}

void CScreenMatchResult::simulateMatches()
{
    IDAOFactory         *daoFactory = m_game->getIDAOFactory();
    IPfGameOptionsDAO   *optionsDAO = daoFactory->getIPfGameOptionsDAO();
    IPfMatchesDAO       *matchesDAO = daoFactory->getIPfMatchesDAO();
    IPfTeamPlayersDAO   *teamPlayersDAO = daoFactory->getIPfTeamPlayersDAO();
    CPfMatches          *userMatch;

    CPfGameOptions *resultMode = optionsDAO->findBySCategoryAndSAttribute("Match", "ResultMode");
    if(resultMode->getSValue() == "true") { //result mode
        userMatch = matchesDAO->findNextPlayerTeamMatch();
    } else {
        userMatch = matchesDAO->findLastPlayerTeamMatch();
    }
    delete resultMode;

    srand(time(NULL));
    daoFactory->beginTransaction();

    std::vector<CPfMatches*>*           matchesList = matchesDAO->findByXFkCompetitionPhase(userMatch->getXFkCompetitionPhase());
    std::vector<CPfMatches*>::iterator  it;

    for( it=matchesList->begin(); it!=matchesList->end(); it++ ){
        CPfMatches *match = (*it);
        if( !match->getLPlayed() ){
            CStartMatchEvent    startMatchEvent(match->getXMatch());
            m_game->getEventStrategy()->process(startMatchEvent);

            int nHomeGoals = getRandomNGoals();
            int nAwayGoals = getRandomNGoals();

            if( nHomeGoals>0 ){
                std::vector<CPfTeamPlayers*>* teamPlayesList = teamPlayersDAO->findActiveByXFkTeam(match->getXFkTeamHome());
                while( nHomeGoals>0 ){
                    CPfTeamPlayers *teamPlayer = teamPlayesList->operator[](rand()%teamPlayesList->size());
                    CGoalMatchEvent goalMatchEvent(match->getXMatch(), match->getXFkTeamHome(), teamPlayer->getXTeamPlayer(), rand()%90, false);
                    m_game->getEventStrategy()->process(goalMatchEvent);
                    nHomeGoals--;
                }
                teamPlayersDAO->freeVector(teamPlayesList);
            }
            if( nAwayGoals>0 ){
                std::vector<CPfTeamPlayers*>* teamPlayesList = teamPlayersDAO->findActiveByXFkTeam(match->getXFkTeamAway());
                while( nAwayGoals>0 ){
                    CPfTeamPlayers *teamPlayer = teamPlayesList->operator[](rand()%teamPlayesList->size());
                    CGoalMatchEvent goalMatchEvent(match->getXMatch(), match->getXFkTeamAway(), teamPlayer->getXTeamPlayer(), rand()%90, false);
                    m_game->getEventStrategy()->process(goalMatchEvent);
                    nAwayGoals--;
                }
                teamPlayersDAO->freeVector(teamPlayesList);
            }

            CEndMatchEvent endMatchEvent(match->getXMatch());
            m_game->getEventStrategy()->process(endMatchEvent);
        }
    }
    matchesDAO->freeVector(matchesList);

    daoFactory->commit();

    delete userMatch;
}

int CScreenMatchResult::getRandomNGoals()
{
    int n = rand()%100;

    if( n>=0  && n<15  ){ return 0; }
    if( n>=15 && n<50  ){ return 1; }
    if( n>=50 && n<90  ){ return 2; }
    if( n>=90 && n<100 ){ return 3; }
}

bool CScreenMatchResult::continueButtonClicked(const CEGUI::EventArgs& e)
{
    m_game->nextScreen(m_game->getGameScreen());
    return true;
}
