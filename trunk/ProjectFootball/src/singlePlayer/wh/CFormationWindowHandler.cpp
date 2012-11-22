/******************************************************************************
* Copyright (C) 2012 - Ikaro Games   www.ikarogames.com                       *
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

#include "CFormationWindowHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeamPlayers.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"

#include <boost/lexical_cast.hpp>

#define VERT_PITCH_CENTER 0.469
#define VERT_PITCH_MAX 0.46
#define VERT_PITCH_POS_MAX 35
#define HORZ_PITCH_CENTER 0.485
#define HORZ_PITCH_MAX 0.45
#define HORZ_PITCH_POS_MAX 55

#define GET_OFFENSIVE_GUI m_lineUpGui[11]
#define GET_DEFENSIVE_GUI m_lineUpGui[12]

CFormationWindowHandler::CFormationWindowHandler(CSinglePlayerGame &game) :
	CWindowHandler("formation.layout"),
	m_game(game),
	m_initiated(false)
{
    LOG_DEBUG("CFormationWindowHandler()");
}

CFormationWindowHandler::~CFormationWindowHandler()
{
    LOG_DEBUG("~CFormationWindowHandler()");

    if( m_initiated ){
		m_lineUpTeamPlayersList->removeColumnWithID(0);
		m_lineUpTeamPlayersList->removeColumnWithID(1);
		m_lineUpTeamPlayersList->removeColumnWithID(2);
		m_lineUpTeamPlayersList->removeColumnWithID(3);
		m_lineUpTeamPlayersList->removeColumnWithID(4);
		m_lineUpTeamPlayersList->removeColumnWithID(5);
    }
}

void CFormationWindowHandler::enter()
{
    loadTeamPlayersList();
    m_selectedPlayer = NULL;
}

void CFormationWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();
	std::string image_pos, label_pos;

    m_lineUpTeamPlayersList = static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"Formation/LineUpTeamPlayersList"));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Role"),           0, CEGUI::UDim(0.10,0));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Sqd #"), 			1, CEGUI::UDim(0.10,0));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Name"), 			2, CEGUI::UDim(0.30,0));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Pos"),           	3, CEGUI::UDim(0.10,0));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Spd"),			4, CEGUI::UDim(0.10,0));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("ShP"),    		5, CEGUI::UDim(0.10,0));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Moral"),          6, CEGUI::UDim(0.10,0));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Avg"),        	7, CEGUI::UDim(0.10,0));
    m_lineUpTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_lineUpTeamPlayersList->setUserColumnSizingEnabled(false);
    m_lineUpTeamPlayersList->setUserSortControlEnabled(false);
    m_lineUpTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);

    m_teamFormationImg		= static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"Formation/FormationLayout"));
    m_teamFormationName = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"Formation/FormationName"));

    // i18n support
    windowMngr.getWindow((CEGUI::utf8*)"Formation/TeamStartLineUpLabel")->setText((CEGUI::utf8*)gettext("Starting Line Up:"));
    windowMngr.getWindow((CEGUI::utf8*)"Formation/FormationLabel")->setText((CEGUI::utf8*)gettext("Formation:"));

    // events
    registerEventConnection(m_lineUpTeamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CFormationWindowHandler::lineUpTeamPlayersListboxSelectionChanged, this)));

	for (int i = 0; i < 11; i++) {
		image_pos = "Formation/Player_img_" + boost::lexical_cast< std::string >(i + 1);
		label_pos = "Formation/Player_txt_" + boost::lexical_cast< std::string >(i + 1);
		m_lineUpGui[i] = std::make_pair(static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)image_pos.c_str())),
										static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)label_pos.c_str())));
		m_lineUpGui[i].first->setProperty("Image", "set:Tactics image:Inactive_Position");
		m_lineUpGui[i].second->setText("[colour=&apos;FF00FF00&apos;]0");
	}

	/* update offensive gui */
	GET_OFFENSIVE_GUI = std::make_pair(static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"Formation/Player_off_img")),
									   static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Formation/Player_off_txt")));
	/* update defensive gui */
	GET_DEFENSIVE_GUI = std::make_pair(static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"Formation/Player_def_img")),
									   static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Formation/Player_def_txt")));
	m_selectedPlayer = NULL;
	setOffDefPosVisability();
    m_initiated = true;
}

void CFormationWindowHandler::leave()
{
    if (m_selectedPlayer != NULL) {
        delete m_selectedPlayer;
    }
}

void CFormationWindowHandler::changePlayers(CEGUI::MultiColumnList *list1, int row1, CEGUI::MultiColumnList *list2, int row2)
{
    changeRows(list1, row1, list2, row2);

    list1->getHorzScrollbar()->setVisible(false);
    list2->getHorzScrollbar()->setVisible(false);
    delete m_selectedPlayer;
    m_selectedPlayer = NULL;
    list1->clearAllSelections();
    list2->clearAllSelections();

	saveTeamPlayersList();
}

void CFormationWindowHandler::loadTeamPlayersList()
{
    m_lineUpTeamPlayersList   ->resetList();

    std::string                  currentTimestamp          = m_game.getCurrentTime().getTimestamp();
    CPfTeams                     *team                     = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game.getOptionManager()->getGamePlayerTeam());
    IPfTeamPlayersDAO            *teamPlayersDAO           = m_game.getIDAOFactory()->getIPfTeamPlayersDAO();
    IPfTeamAveragesDAO           *teamAveragesDAO          = m_game.getIDAOFactory()->getIPfTeamAveragesDAO();
    IPfFormationsDAO             *formationsDAO            = m_game.getIDAOFactory()->getIPfFormationsDAO();
    CPfFormations                *formation                = formationsDAO->findActiveByXTeam(team->getXTeam(), currentTimestamp);
    std::vector<CPfTeamPlayers*> *lineUpTeamPlayersList    = teamPlayersDAO->findLineUpByXFkTeam(team->getXTeam(), currentTimestamp);
    std::vector<CPfTeamPlayers*> *alternateTeamPlayersList = teamPlayersDAO->findAlternateByXFkTeam(team->getXTeam(), currentTimestamp);
    std::vector<CPfTeamPlayers*> *notLineUpTeamPlayersList = teamPlayersDAO->findNotLineUpByXFkTeam(team->getXTeam(), currentTimestamp);


    std::vector<CPfTeamPlayers*>::iterator it;
    for( it=lineUpTeamPlayersList->begin(); it!=lineUpTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);
        addPlayerToLineUpList(teamPlayer, m_lineUpTeamPlayersList, formation->getXFormation());
    }

	m_teamFormationImg->setProperty("Image", "set:Tactics image:Pitch");

    teamPlayersDAO->freeVector(lineUpTeamPlayersList);
    teamPlayersDAO->freeVector(alternateTeamPlayersList);
    teamPlayersDAO->freeVector(notLineUpTeamPlayersList);
    delete team;

    m_lineUpTeamPlayersList   ->getHorzScrollbar()->setVisible(false);
    m_lineUpTeamPlayersList   ->getVertScrollbar()->setVisible(false);
	m_teamFormationName->setText((CEGUI::String)formation->getSName_str());
}

void CFormationWindowHandler::addPlayerToLineUpList(CPfTeamPlayers *player, CEGUI::MultiColumnList *list, int xFormation)
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().get("WidgetsImageset").getImage("MultiListSelectionBrush");
    IPfRolesDAO *rolesDAO =  m_game.getIDAOFactory()->getIPfRolesDAO();
	int index = player->getNLineupOrder() - 1;

    int row_idx = list->addRow();
    int XTeamPlayer = player->getXTeamPlayer();
	CPfStrategicPositions *position = m_game.getIDAOFactory()->getIPfStrategicPositionsDAO()->findByXFkFormation(xFormation)->at(index);
    CPfRoles *role = rolesDAO->findInStrategicPositionByXFormationAndLineUpOrder(xFormation, player->getNLineupOrder());
	std::pair< CEGUI::Window *, CEGUI::Window * >* gui_pos = &m_lineUpGui[index];
    CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)role->getSShortName_str().c_str(), XTeamPlayer);
	item->setSelectionBrushImage(sel_img);
	list->setItem(item, 0, row_idx);
	delete role;

	item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getNSquadNumber_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 1, row_idx);

	item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getSShortName().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 2, row_idx);
	
	item = new CEGUI::ListboxTextItem((CEGUI::utf8*)"N/A", XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 3, row_idx);
	
    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getNSpeed_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 4, row_idx);

    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getNKickPower_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 5, row_idx);

    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getNMoral_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 6, row_idx);

    CPfTeamPlayerAverages *playerAverage = m_game.getIDAOFactory()->getIPfTeamPlayerAveragesDAO()->findByXTeamPlayer(player->getXTeamPlayer_str());
    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)playerAverage->getNTotal_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 7, row_idx);
    delete playerAverage;

	CEGUI::UVector2 pos(CEGUI::UDim((float)(HORZ_PITCH_CENTER + (HORZ_PITCH_MAX * position->getNInitialPosX() / HORZ_PITCH_POS_MAX)), 0),
						CEGUI::UDim((float)(VERT_PITCH_CENTER + (VERT_PITCH_MAX * position->getNInitialPosZ() / VERT_PITCH_POS_MAX)), 0));
	gui_pos->first->setPosition(pos);
	gui_pos->second->setPosition(pos);

	const std::string text = "[colour=&apos;FF00FF00&apos;]" + player->getNSquadNumber_str();
	gui_pos->second->setText((CEGUI::utf8*)text.c_str());
}

void CFormationWindowHandler::saveTeamPlayersList()
{
    m_game.getIDAOFactory()->beginTransaction();
    CPfTeams                    *team                   = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game.getOptionManager()->getGamePlayerTeam());
    IPfTeamPlayersDAO           *teamPlayersDAO         = m_game.getIDAOFactory()->getIPfTeamPlayersDAO();

    unsigned int i;
    int lineUpOrder = 1;
    std::string currentTimestamp = m_game.getCurrentTime().getTimestamp();

    for( i=0; i<m_lineUpTeamPlayersList->getRowCount(); i++ ){

        CEGUI::ListboxItem  *item           = m_lineUpTeamPlayersList->getItemAtGridReference(CEGUI::MCLGridRef(i, 1));
        int                 xTeamPlayer   = item->getID();

        CPfTeamPlayers *teamPlayer = teamPlayersDAO->findByXTeamPlayer(xTeamPlayer);
        teamPlayer->setNLineupOrder(lineUpOrder);
		teamPlayersDAO->updateReg(teamPlayer);
		delete teamPlayer;

        lineUpOrder++;
    }

    delete team;
    m_game.getIDAOFactory()->commit();
}

void CFormationWindowHandler::selectChanged(CEGUI::MultiColumnList *list)
{
    CEGUI::ListboxItem *currentItem = list->getFirstSelectedItem();

    if( currentItem != NULL ) {
        int currentRow  = list->getItemRowIndex(currentItem);
        list->clearAllSelections();
        IPfTeamPlayersDAO *teamPlayersDAO = m_game.getIDAOFactory()->getIPfTeamPlayersDAO();
        int xTeamPlayer = currentItem->getID();
        if(m_selectedPlayer == NULL) {
            m_selectedPlayer = teamPlayersDAO->findByXTeamPlayer(xTeamPlayer);
            m_selectedPlayerRow = currentRow;
            m_selectedPlayerList = list;
			if (m_lineUpTeamPlayersList == list) {
				m_lineUpGui[m_selectedPlayerRow].first->setProperty("Image", "set:Tactics image:Initial_Position");
				m_lineUpGui[m_selectedPlayerRow].second->setText("[colour=&apos;FF00FF00&apos;]I");
				m_highlight_player = true;
				setOffDefPosVisability();
			}
            changeRowSelection(m_selectedPlayerList, m_selectedPlayerRow, true);
        } else {
			std::string orig_shirt_num = m_selectedPlayer->getNSquadNumber_str();
            if ((xTeamPlayer == m_selectedPlayer->getXTeamPlayer())) {
                delete m_selectedPlayer;
                m_selectedPlayer = NULL;
            } else {
                changePlayers(m_selectedPlayerList, m_selectedPlayerRow, list, currentRow);
            }
            if (m_highlight_player) {
				m_lineUpGui[m_selectedPlayerRow].first->setProperty("Image", "set:Tactics image:Inactive_Position");
				const std::string text = "[colour=&apos;FF00FF00&apos;]" + orig_shirt_num;
				m_lineUpGui[m_selectedPlayerRow].second->setText((CEGUI::utf8*)text.c_str());
				m_highlight_player = false;
				setOffDefPosVisability();
			}
        }
    }
}

bool CFormationWindowHandler::lineUpTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e)
{
    selectChanged(m_lineUpTeamPlayersList);
    return true;
}

void CFormationWindowHandler::changeRows(CEGUI::MultiColumnList *list1, int row1, CEGUI::MultiColumnList *list2, int row2)
{
    CEGUI::ListboxItem *item1 = NULL;
    CEGUI::ListboxItem *item2 = NULL;
	std::string text = "[colour=&apos;FF00FF00&apos;]";
    int columns = list1->getColumnCount();
	int i = 0, j = 0;

	if (list1 == m_lineUpTeamPlayersList) {
		i++;
	}
	if (list2 == m_lineUpTeamPlayersList) {
		j++;
	}

    for(; i < columns; i++, j++) {
        CEGUI::ListboxItem *itemAux;
        CEGUI::MCLGridRef reference1 = CEGUI::MCLGridRef(row1, i);
        CEGUI::MCLGridRef reference2 = CEGUI::MCLGridRef(row2, j);
        item1 = list1->getItemAtGridReference(reference1);
        item2 = list2->getItemAtGridReference(reference2);
		if ((i == 0) and (j == 1)) {
			text.append(item1->getText().c_str());
			m_lineUpGui[row2].second->setText((CEGUI::utf8*)text.c_str());
		} else if ((i == 1) and (j == 0)) {
			text.append(item2->getText().c_str());
			m_lineUpGui[row1].second->setText((CEGUI::utf8*)text.c_str());
		} else if ((i == 1) and (j == 1)) {
			std::string temp_text = text;
			text.append(item2->getText().c_str());
			temp_text.append(item1->getText().c_str());
			m_lineUpGui[row1].second->setText((CEGUI::utf8*)text.c_str());
			m_lineUpGui[row2].second->setText((CEGUI::utf8*)temp_text.c_str());
		}
        item1->setAutoDeleted(false);
        item2->setAutoDeleted(false);
        list1->setItem(item2, reference1);
        list2->setItem(item1, reference2);
        itemAux = item1;
        item1 = item2;
        item2 = itemAux;
        item1->setAutoDeleted(true);
        item2->setAutoDeleted(true);
    }
}

void CFormationWindowHandler::changeRowSelection(CEGUI::MultiColumnList *list, int row, bool newSelectionState)
{

    int columns = list->getColumnCount();
    for( int i = 0; i < columns; i++) {
        CEGUI::ListboxItem *item = list->getItemAtGridReference(CEGUI::MCLGridRef(row, i));
        item->setSelected(newSelectionState);
    }
}

void CFormationWindowHandler::setOffDefPosVisability()
{
	if (m_selectedPlayer) {
		std::string currentTimestamp = m_game.getCurrentTime().getTimestamp();
		CPfTeams *team = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game.getOptionManager()->getGamePlayerTeam());
		IPfFormationsDAO *formationsDAO = m_game.getIDAOFactory()->getIPfFormationsDAO();
		CPfFormations *formation = formationsDAO->findActiveByXTeam(team->getXTeam(), currentTimestamp);
		CPfStrategicPositions *position = m_game.getIDAOFactory()->getIPfStrategicPositionsDAO()->findByXFkFormation(formation->getXFormation())->at(m_selectedPlayer->getNLineupOrder() - 1);
		if ((position->getNOffensivePosX() != position->getNInitialPosX()) or
			(position->getNOffensivePosZ() != position->getNInitialPosZ())) {
			CEGUI::UVector2 offPos(CEGUI::UDim((float)(HORZ_PITCH_CENTER + (HORZ_PITCH_MAX * position->getNOffensivePosX() / HORZ_PITCH_POS_MAX)), 0),
								   CEGUI::UDim((float)(VERT_PITCH_CENTER + (VERT_PITCH_MAX * position->getNOffensivePosZ() / VERT_PITCH_POS_MAX)), 0));
			GET_OFFENSIVE_GUI.first->setPosition(offPos);
			GET_OFFENSIVE_GUI.second->setPosition(offPos);
			GET_OFFENSIVE_GUI.first->setProperty("Image", "set:Tactics image:Offensive_Position");
			GET_OFFENSIVE_GUI.second->setText("[colour=&apos;FF00FF00&apos;]O");
		}
		if ((position->getNDefensivePosX() != position->getNInitialPosX()) or
			(position->getNDefensivePosZ() != position->getNInitialPosZ())) {
			CEGUI::UVector2 defPos(CEGUI::UDim((float)(HORZ_PITCH_CENTER + (HORZ_PITCH_MAX * position->getNDefensivePosX() / HORZ_PITCH_POS_MAX)), 0),
								   CEGUI::UDim((float)(VERT_PITCH_CENTER + (VERT_PITCH_MAX * position->getNDefensivePosZ() / VERT_PITCH_POS_MAX)), 0));
			GET_DEFENSIVE_GUI.first->setPosition(defPos);
			GET_DEFENSIVE_GUI.second->setPosition(defPos);
			GET_DEFENSIVE_GUI.first->setProperty("Image", "set:Tactics image:Defensive_Position");
			GET_DEFENSIVE_GUI.second->setText("[colour=&apos;FF00FF00&apos;]D");
		}
	} else {
		GET_OFFENSIVE_GUI.first->setProperty("Image", "");
		GET_OFFENSIVE_GUI.second->setText("");
		GET_DEFENSIVE_GUI.first->setProperty("Image", "");
		GET_DEFENSIVE_GUI.second->setText("");
	}
}
