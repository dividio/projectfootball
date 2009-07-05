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

#ifndef CMEMBERFUNCTIONSLOT_H_
#define CMEMBERFUNCTIONSLOT_H_

#include "ISlotFunctorBase.h"
#include "../IGameEvent.h"

template<typename T>
class CMemberFunctionSlot: public ISlotFunctorBase {
public:
	typedef void(T::*MemberFunctionType)(const IGameEvent&);

	CMemberFunctionSlot(MemberFunctionType function, T *object) :
		m_function(function),
		m_object(object)
	{}

	virtual ~CMemberFunctionSlot(){}

	virtual void operator()(const IGameEvent &event) const
	{
		(m_object->*m_function)(event);
	}

private:
	MemberFunctionType	m_function;
	T*					m_object;
};

#endif /* CMEMBERFUNCTIONSLOT_H_ */
