/*******************************************************************************
 * Copyright (C) 2009 - Ikaro Games   www.ikarogames.com                       *
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

#include "CEventConsumer.h"

#include "IGameEvent.h"
#include "CEventsQueue.h"
#include "CEventMustStopVisitor.h"
#include "CEventProcessorVisitor.h"

#include "../CSinglePlayerGame.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

CEventConsumer::CEventConsumer(CSinglePlayerGame *game)
{
	m_game			= game;
	m_lastEvent		= NULL;

	m_eventMustStopVisitor	= new CEventMustStopVisitor(m_game);
	m_eventProcessorVisitor	= new CEventProcessorVisitor(m_game);
}

CEventConsumer::~CEventConsumer()
{
	if( m_lastEvent!=NULL ){
		delete m_lastEvent;
	}

	delete m_eventProcessorVisitor;
	delete m_eventMustStopVisitor;
}

void CEventConsumer::consumeEvents()
{
	CEventsQueue 	*queue			= m_game->getEventsQueue();
	CDate 			 currentDate 	= m_game->getOptionManager()->getGameCurrentDate();

	m_game->getIDAOFactory()->beginTransaction();

	consumeLastEvent();

	bool stop = false;
	do{
		delete m_lastEvent; // delete the previous event

		m_lastEvent = queue->pop(&currentDate);
		if( m_lastEvent==NULL ){
			if( queue->empty() ){
				m_game->getOptionManager()->setGameCurrentDate(currentDate);
				stop = true;
			}else{
				currentDate.setDay(currentDate.getDay()+1);
			}
		}else{
			m_lastEvent->visitor(*m_eventMustStopVisitor);
			if( m_eventMustStopVisitor->eventMustStop() ){
				m_game->getOptionManager()->setGameCurrentDate(m_lastEvent->getDate());
				stop = true;
			}else{
				m_lastEvent->visitor(*m_eventProcessorVisitor);
			}
		}
	}while(!stop);

	m_game->getIDAOFactory()->commit();
}

void CEventConsumer::consumeLastEvent()
{
	if( m_lastEvent!=NULL ){
		m_lastEvent->visitor(*m_eventProcessorVisitor);
		delete m_lastEvent;
		m_lastEvent = NULL;
	}
}

void CEventConsumer::consumeCurrentDayEvents()
{
	CEventsQueue 	*queue			= m_game->getEventsQueue();
	CDate 			 currentDate 	= m_game->getOptionManager()->getGameCurrentDate();

	currentDate.setHour(23);
	currentDate.setMin(59);
	currentDate.setSec(59);

	m_game->getIDAOFactory()->beginTransaction();

	consumeLastEvent();

	bool stop = false;
	do{
		delete m_lastEvent;	// delete the previous event

		m_lastEvent = queue->pop(&currentDate);
		if( m_lastEvent==NULL ){
			m_game->getOptionManager()->setGameCurrentDate(currentDate);
			stop = true;
		}else{
			m_lastEvent->visitor(*m_eventMustStopVisitor);
			if( m_eventMustStopVisitor->eventMustStop() ){
				m_game->getOptionManager()->setGameCurrentDate(m_lastEvent->getDate());
				stop = true;
			}else{
				m_lastEvent->visitor(*m_eventProcessorVisitor);
			}
		}
	}while(!stop);

	m_game->getIDAOFactory()->commit();
}

const IGameEvent* CEventConsumer::getLastEvent() const
{
	return m_lastEvent;
}
