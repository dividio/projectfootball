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


#ifndef __CStateMachine_H__
#define __CStateMachine_H__

#include "IState.h"

template <class entity_type>
class CStateMachine
{
public:
    CStateMachine(entity_type *owner) {m_owner = owner;};
    ~CStateMachine(){};

    void setCurrentState(IState<entity_type> *state) {m_currentState = state;};
    void setGlobalState(IState<entity_type> *state) {m_globalState = state;};
    void setPreviousState(IState<entity_type> *state) {m_previousState = state;};

    void update() const {};
    void changeState(IState<entity_type> *newState) {};
    void revertToPreviousState() {};

    IState<entity_type>* currentState() const {return m_currentState;};
    IState<entity_type>* previousState() const {return m_previousState;};
    IState<entity_type>* globalState() const {return m_globalState;};

    bool isInState(const IState<entity_type> &state) const {};

private:

    entity_type *m_owner;

    IState<entity_type> *m_globalState;
    IState<entity_type> *m_currentState;
    IState<entity_type> *m_previousState;
};

#endif // __CStateMachine_H__
