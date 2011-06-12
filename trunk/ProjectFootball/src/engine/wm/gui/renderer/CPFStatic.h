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

#ifndef CPFSTATIC_H_
#define CPFSTATIC_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/CEGUIWindowRendererModule.h>
#include "CPFStaticProperties.h"

namespace CEGUI{
	/*!
	 * \brief
	 * 		Based in FalagardStatic class.
	 *
	 * 		This class requires LookNFeel to be assigned. The LookNFeel should provide the following:
	 *		States:
	 *			- Enabled                     - basic rendering for enabled state.
	 *			- Disabled                    - basic rendering for disabled state.
	 *			- EnabledFrame                - frame rendering for enabled state
	 *			- DisabledFrame               - frame rendering for disabled state.
	 *			- WithFrameEnabledBackground  - backdrop rendering for enabled state with frame enabled.
	 *			- WithFrameDisabledBackground - backdrop rendering for disabled state with frame enabled.
	 *			- NoFrameEnabledBackground    - backdrop rendering for enabled state with frame disabled.
	 *			- NoFrameDisabledBackground   - backdrop rendering for disabled state with frame disabled.
	 */
	class CPFStatic : public WindowRenderer{
	public:
		static const utf8	TypeName[];

		CPFStatic(const String &type);
		virtual ~CPFStatic();

		bool	isFrameEnabled() const { return d_frameEnabled; }
		bool	isBackgroundEnabled() const { return d_backgroundEnabled; }
		void	setFrameEnabled(bool setting);
		void	setBackgroundEnabled(bool setting);

		virtual void render();

	protected:
		// static properties
		static CPFStaticProperties::FrameEnabled		d_frameEnabledProperty;
		static CPFStaticProperties::BackgroundEnabled	d_backgroundEnabledProperty;

		// implementation data
		bool	d_frameEnabled;
		bool	d_backgroundEnabled;
	};
}

#endif /* CPFSTATIC_H_ */
