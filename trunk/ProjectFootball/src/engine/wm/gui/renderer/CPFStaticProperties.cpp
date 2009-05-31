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

#include "CPFStaticProperties.h"

#include <CEGUI/CEGUIPropertyHelper.h>
#include "CPFStatic.h"

namespace CEGUI{
	namespace CPFStaticProperties{

		String FrameEnabled::get(const PropertyReceiver *receiver) const
		{
			CPFStatic *wr = static_cast<CPFStatic*>(static_cast<const Window*>(receiver)->getWindowRenderer());
			return PropertyHelper::boolToString(wr->isFrameEnabled());
		}

		void FrameEnabled::set(PropertyReceiver *receiver, const String &value)
		{
			CPFStatic *wr = static_cast<CPFStatic*>(static_cast<const Window*>(receiver)->getWindowRenderer());
			wr->setFrameEnabled(PropertyHelper::stringToBool(value));
		}

		String BackgroundEnabled::get(const PropertyReceiver *receiver) const
		{
			CPFStatic *wr = static_cast<CPFStatic*>(static_cast<const Window*>(receiver)->getWindowRenderer());
			return PropertyHelper::boolToString(wr->isBackgroundEnabled());
		}

		void BackgroundEnabled::set(PropertyReceiver *receiver, const String &value)
		{
			CPFStatic *wr = static_cast<CPFStatic*>(static_cast<const Window*>(receiver)->getWindowRenderer());
			wr->setBackgroundEnabled(PropertyHelper::stringToBool(value));
		}
	}
}
