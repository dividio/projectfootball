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

#ifndef CPFROTATINGTEXT_H_
#define CPFROTATINGTEXT_H_

#include <boost/thread.hpp>
#include "CPFStaticText.h"
#include "CPFRotatingTextProperties.h"


namespace CEGUI{
	class CPFRotatingText : public CPFStaticText{
	public:
		static const utf8	TypeName[];	//!< type name for this widget.

	public:
		CPFRotatingText(const String &type);
		virtual ~CPFRotatingText();

		virtual void render();

		void	setTextSpeed( float setting );
		float	getTextSpeed() const { return d_textSpeed; }

	protected:
		void renderRotatingText();

	protected:
		// properties
		static CPFRotatingTextProperties::TextSpeed	d_textSpeedProperty;

		float			d_textSpeed;

	private:
		void runThread();

	private:
		boost::thread	m_thread;
		bool			m_stopThread;
	};
	CEGUI_DEFINE_WR_FACTORY(CPFRotatingText)
}

#endif /* CPFROTATINGTEXT_H_ */
