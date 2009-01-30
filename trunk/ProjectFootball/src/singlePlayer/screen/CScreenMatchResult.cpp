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

#include "CScreenMatchResult.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../utils/CLog.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../db/bean/CPfMatches.h"
#include "../event/match/CEndMatchEvent.h"
#include "../event/match/CGoalMatchEvent.h"
#include "../event/match/CStartMatchEvent.h"
#include "../event/strategy/CSinglePlayerEventStrategy.h"


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
    if(m_match != NULL) {
        delete m_match;
    }
}

void CScreenMatchResult::enter()
{
    CScreen::enter();

    simulateMatches();

    IPfMatchesDAO *matchesDAO = m_game->getIDAOFactory()->getIPfMatchesDAO();
    if(m_match != NULL) {
        delete m_match;
    }
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
    m_competitionName     ->setProperty("Text", (CEGUI::utf8*)competition->getSCompetition().c_str());
    m_competitionPhaseName->setProperty("Text", (CEGUI::utf8*)competitionPhase->getSCompetitionPhase().c_str());
    m_homeName            ->setProperty("Text", (CEGUI::utf8*)homeName.c_str());
    m_awayName            ->setProperty("Text", (CEGUI::utf8*)awayName.c_str());
    m_homeScore           ->setProperty("Text", (CEGUI::utf8*)nHomeGoals.str().c_str());
    m_awayScore           ->setProperty("Text", (CEGUI::utf8*)nAwayGoals.str().c_str());

    //Loading Home Shield
    m_homeLogo->setProperty("Image", "set:"+ homeTeam->getSLogo() +" image:"+homeTeam->getSLogo()+"_b");

    //Loading Away Shield
    m_awayLogo->setProperty("Image", "set:"+ awayTeam->getSLogo() +" image:"+awayTeam->getSLogo()+"_b");

    std::vector<CPfGoals*>::iterator it;
    CEGUI::ListboxTextItem *item;
    CPfTeamPlayers *player;
    std::ostringstream event;

    for( it=homeGoalsList->begin(); it!=homeGoalsList->end(); it++ ){
        CPfGoals *goal = (*it);

        int row_idx = m_homeEventsList->addRow();

        item = new CEGUI::ListboxTextItem(goal->getNMinute_str());
        m_homeEventsList->setItem(item, 0, row_idx);

        player = playersDAO->findByXTeamPlayer(goal->getXFkTeamPlayerScorer());
        event << gettext("Goal by ") << player->getSName().c_str();
        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)event.str().c_str());
        m_homeEventsList->setItem(item, 1, row_idx);
        delete player;
        event.str("");
    }
    goalsDAO->freeVector(homeGoalsList);

    for( it=awayGoalsList->begin(); it!=awayGoalsList->end(); it++ ){
        CPfGoals *goal = (*it);

        int row_idx = m_awayEventsList->addRow();

        item = new CEGUI::ListboxTextItem(goal->getNMinute_str());
        m_awayEventsList->setItem(item, 0, row_idx);

        player = playersDAO->findByXTeamPlayer(goal->getXFkTeamPlayerScorer());
        event << gettext("Goal by ") << player->getSName().c_str();
        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)event.str().c_str());
        m_awayEventsList->setItem(item, 1, row_idx);
        delete player;
        event.str("");
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

    delete competition;
    delete competitionPhase;
    delete awayTeam;
    delete homeTeam;

}

void CScreenMatchResult::simulateMatches()
{
    IDAOFactory         *daoFactory = m_game->getIDAOFactory();
    IPfGameOptionsDAO   *optionsDAO = daoFactory->getIPfGameOptionsDAO();
    IPfMatchesDAO       *matchesDAO = daoFactory->getIPfMatchesDAO();
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
        simulateMatch(match);
    }
    matchesDAO->freeVector(matchesList);

    daoFactory->commit();

    delete userMatch;
}

void CScreenMatchResult::simulateMatch(CPfMatches *match)
{
    if( !match->getLPlayed() ){
        IDAOFactory        *daoFactory     = m_game->getIDAOFactory();
        IPfTeamPlayersDAO  *teamPlayersDAO = daoFactory->getIPfTeamPlayersDAO();
        IPfTeamAveragesDAO *teamsAvgDAO    = daoFactory->getIPfTeamAveragesDAO();

        CStartMatchEvent    startMatchEvent(match->getXMatch());
        m_game->getEventStrategy()->process(startMatchEvent);

        int xHomeTeam  = match->getXFkTeamHome();
        int xAwayTeam  = match->getXFkTeamAway();
        CPfTeamAverages *homeTeamAvg = teamsAvgDAO->findByXTeam(xHomeTeam);
        CPfTeamAverages *awayTeamAvg = teamsAvgDAO->findByXTeam(xAwayTeam);
        int nHomeGoals = getRandomNGoals(homeTeamAvg, awayTeamAvg);
        int nAwayGoals = getRandomNGoals(awayTeamAvg, homeTeamAvg);

        delete homeTeamAvg;
        delete awayTeamAvg;

        if( nHomeGoals>0 ){
            std::vector<CPfTeamPlayers*>* teamPlayesList = teamPlayersDAO->findLineUpByXFkTeam(xHomeTeam);
            while( nHomeGoals>0 ){
                int numPlayer = rand()%teamPlayesList->size();
                if(numPlayer == 0) { //Goalie don't score
                    numPlayer = 10;
                }
                CPfTeamPlayers *teamPlayer = teamPlayesList->operator[](numPlayer);
                CGoalMatchEvent goalMatchEvent(match->getXMatch(), xHomeTeam, teamPlayer->getXTeamPlayer(), rand()%90, false);
                m_game->getEventStrategy()->process(goalMatchEvent);
                nHomeGoals--;
            }
            teamPlayersDAO->freeVector(teamPlayesList);
        }
        if( nAwayGoals>0 ){
            std::vector<CPfTeamPlayers*>* teamPlayesList = teamPlayersDAO->findLineUpByXFkTeam(xAwayTeam);
            while( nAwayGoals>0 ){
                int numPlayer = rand()%teamPlayesList->size();
                if(numPlayer == 0) { //Goalie don't score
                    numPlayer = 10;
                }
                CPfTeamPlayers *teamPlayer = teamPlayesList->operator[](numPlayer);
                CGoalMatchEvent goalMatchEvent(match->getXMatch(), xAwayTeam, teamPlayer->getXTeamPlayer(), rand()%90, false);
                m_game->getEventStrategy()->process(goalMatchEvent);
                nAwayGoals--;
            }
            teamPlayersDAO->freeVector(teamPlayesList);
        }

        CEndMatchEvent endMatchEvent(match->getXMatch());
        m_game->getEventStrategy()->process(endMatchEvent);
    }
}


int CScreenMatchResult::getRandomNGoals(CPfTeamAverages *attackTeam, CPfTeamAverages *defenseTeam)
{
    int goals = 0;
    int teamFactor = attackTeam->getNTotal() - defenseTeam->getNTotal();

    int n = rand()%100 + teamFactor;

         if( n<25  )         { goals = 0; }
    else if( n>=25 && n<55  ){ goals = 1; }
    else if( n>=55 && n<80  ){ goals = 2; }
    else if( n>=80 && n<96  ){ goals = 3; }
    else if( n>=96 && n<100 ){ goals = 4; }
    else if( n>=100 )        { goals = 5; }
    return goals;
}


bool CScreenMatchResult::continueButtonClicked(const CEGUI::EventArgs& e)
{
    m_game->nextScreen(m_game->getGameScreen());
    return true;
}
