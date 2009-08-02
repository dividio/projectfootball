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

#ifndef CPFSTATICPROPERTIES_H_
#define CPFSTATICPROPERTIES_H_

#include <CEGUI/CEGUIProperty.h>

namespace CEGUI{
	/*!
	 * \brief
	 * 		Based in CEGUI::FalagardStaticProperties.
	 */
	namespace CPFStaticProperties{
		/*!
		 * \brief
		 * 		Based in CEGUI::FalagardStaticProperties::FrameEnabled class.
		 * 		Property to access the state of the frame enabled setting for the PFStatic widget.
		 *
		 * 		\par Usage:
		 * 			- Name: FrameEnabled
		 * 			- Format: "[text]".
		 *
		 * 		\par Where [Text] is:
		 * 			- "True" to indicate that the frame is enabled.
		 * 			- "False" to indicate that the frame is disabled.
		 */
		class FrameEnabled : public Property{
		public:
			FrameEnabled() : Property(
					"FrameEnabled",
					"Property to get/set the state of the frame enabled setting for the PFStatic widget. Value is either \"True\" or \"False\".",
					"True")
			{}

			String	get(const PropertyReceiver *receiver) const;
			void	set(PropertyReceiver *receiver, const String &value);
		};

		/*!
		 * \brief
		 * 		Based in CEGUI::FalagardStaticProperties::BackgroundEnabled class.
		 * 		Property to access the state of the background enabled setting for the PFStatic widget.
		 *
		 * 		\par Usage:
		 * 			- Name: BackgroundEnabled
		 * 			- Format: "[text]".
		 *
		 * 		\par Where [Text] is:
		 * 			- "True" to indicate that the background is enabled.
		 * 			- "False" to indicate that the background is disabled.
		 */
		class BackgroundEnabled : public Property{
		public:
			BackgroundEnabled() : Property(
					"BackgroundEnabled",
					"Property to get/set the state of the background enabled setting for the PFStatic widget. Value is either \"True\" or \"False\".",
					"True")
			{}

			String	get(const PropertyReceiver *receiver) const;
			void	set(PropertyReceiver *receiver, const String &value);
		};
	}
}

#endif /* CPFSTATICPROPERTIES_H_ */
