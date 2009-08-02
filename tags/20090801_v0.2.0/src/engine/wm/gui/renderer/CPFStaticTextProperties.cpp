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

#include "CPFStaticTextProperties.h"

#include <CEGUI/CEGUIPropertyHelper.h>
#include "CPFStaticText.h"

namespace CEGUI{
	namespace CPFStaticTextProperties{
		String	TextColours::get(const PropertyReceiver* receiver) const
		{
			CPFStaticText* wr = static_cast<CPFStaticText*>(static_cast<const Window*>(receiver)->getWindowRenderer());
			return PropertyHelper::colourRectToString(wr->getTextColours());
		}

		void	TextColours::set(PropertyReceiver* receiver, const String& value)
		{
			CPFStaticText* wr = static_cast<CPFStaticText*>(static_cast<Window*>(receiver)->getWindowRenderer());
			wr->setTextColours(PropertyHelper::stringToColourRect(value));
		}

		String	HorzFormatting::get(const PropertyReceiver* receiver) const
		{
			CPFStaticText* wr = static_cast<CPFStaticText*>(static_cast<const Window*>(receiver)->getWindowRenderer());
			switch(wr->getHorizontalFormatting())
			{
			case CPFStaticText::RightAligned:
				return String("RightAligned");
				break;

			case CPFStaticText::HorzCentred:
				return String("HorzCentred");
				break;

			case CPFStaticText::HorzJustified:
				return String("HorzJustified");
				break;

			case CPFStaticText::WordWrapLeftAligned:
				return String("WordWrapLeftAligned");
				break;

			case CPFStaticText::WordWrapRightAligned:
				return String("WordWrapRightAligned");
				break;

			case CPFStaticText::WordWrapCentred:
				return String("WordWrapCentred");
				break;

			case CPFStaticText::WordWrapJustified:
				return String("WordWrapJustified");
				break;

			default:
				return String("LeftAligned");
				break;
			}
		}

		void	HorzFormatting::set(PropertyReceiver* receiver, const String& value)
		{
			CPFStaticText::HorzFormatting fmt;

			if( value=="RightAligned" ){
				fmt = CPFStaticText::RightAligned;
			}
			else if( value=="HorzCentred" ){
				fmt = CPFStaticText::HorzCentred;
			}
			else if( value=="HorzJustified" ){
				fmt = CPFStaticText::HorzJustified;
			}
			else if( value=="WordWrapLeftAligned" ){
				fmt = CPFStaticText::WordWrapLeftAligned;
			}
			else if( value=="WordWrapRightAligned" ){
				fmt = CPFStaticText::WordWrapRightAligned;
			}
			else if( value=="WordWrapCentred" ){
				fmt = CPFStaticText::WordWrapCentred;
			}
			else if( value=="WordWrapJustified" ){
				fmt = CPFStaticText::WordWrapJustified;
			}
			else{
				fmt = CPFStaticText::LeftAligned;
			}

			CPFStaticText* wr = static_cast<CPFStaticText*>(static_cast<Window*>(receiver)->getWindowRenderer());
			wr->setHorizontalFormatting(fmt);
		}

		String	VertFormatting::get(const PropertyReceiver* receiver) const
		{
			CPFStaticText* wr = static_cast<CPFStaticText*>(static_cast<const Window*>(receiver)->getWindowRenderer());

			switch(wr->getVerticalFormatting())
			{
			case CPFStaticText::BottomAligned:
				return String("BottomAligned");
				break;

			case CPFStaticText::VertCentred:
				return String("VertCentred");
				break;

			default:
				return String("TopAligned");
				break;
			}
		}

		void	VertFormatting::set(PropertyReceiver* receiver, const String& value)
		{
			CPFStaticText::VertFormatting fmt;

			if( value=="BottomAligned" ){
				fmt = CPFStaticText::BottomAligned;
			}
			else if( value=="VertCentred" ){
				fmt = CPFStaticText::VertCentred;
			}
			else{
				fmt = CPFStaticText::TopAligned;
			}

			CPFStaticText* wr = static_cast<CPFStaticText*>(static_cast<Window*>(receiver)->getWindowRenderer());
			wr->setVerticalFormatting(fmt);
		}

		String	VertScrollbar::get(const PropertyReceiver* receiver) const
		{
			CPFStaticText* wr = static_cast<CPFStaticText*>(static_cast<const Window*>(receiver)->getWindowRenderer());
			return PropertyHelper::boolToString(wr->isVerticalScrollbarEnabled());
		}

		void	VertScrollbar::set(PropertyReceiver* receiver, const String& value)
		{
			CPFStaticText* wr = static_cast<CPFStaticText*>(static_cast<Window*>(receiver)->getWindowRenderer());
			wr->setVerticalScrollbarEnabled(PropertyHelper::stringToBool(value));
		}

		String	HorzScrollbar::get(const PropertyReceiver* receiver) const
		{
			CPFStaticText* wr = static_cast<CPFStaticText*>(static_cast<const Window*>(receiver)->getWindowRenderer());
			return PropertyHelper::boolToString(wr->isHorizontalScrollbarEnabled());
		}

		void	HorzScrollbar::set(PropertyReceiver* receiver, const String& value)
		{
			CPFStaticText* wr = static_cast<CPFStaticText*>(static_cast<Window*>(receiver)->getWindowRenderer());
			wr->setHorizontalScrollbarEnabled(PropertyHelper::stringToBool(value));
		}
	}
}
