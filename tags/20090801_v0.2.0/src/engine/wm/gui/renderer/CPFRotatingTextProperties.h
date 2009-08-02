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

#ifndef CPFROTATINGTEXTPROPERTIES_H_
#define CPFROTATINGTEXTPROPERTIES_H_

#include <CEGUI/CEGUIProperty.h>

namespace CEGUI{
	namespace CPFRotatingTextProperties{
		/*!
		 * \brief
		 * 		Property to access the state of the text spedd setting for the PFRotatingText widget.
		 *
		 * 		\par Usage:
		 * 			- Name: TextSpeed
		 * 			- Format: "[float]".
		 *
		 * 		\par Where [float] must be a number in the range (0,1].
		 */
		class TextSpeed : public Property{
		public:
			TextSpeed() : Property(
					"TextSpeed",
					"Property to get/set the state of the text speed setting for the PFRotatingText widget. Value must be in the range (0,1]",
					"0.1")
			{}

			String	get(const PropertyReceiver *receiver) const;
			void	set(PropertyReceiver *receiver, const String &value);
		};
	}
}

#endif /* CPFROTATINGTEXTPROPERTIES_H_ */
