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

#include "CPFStatic.h"



namespace CEGUI{
	const utf8 CPFStatic::TypeName[] = "PF/Static";

	CPFStaticProperties::FrameEnabled		CPFStatic::d_frameEnabledProperty;
	CPFStaticProperties::BackgroundEnabled	CPFStatic::d_backgroundEnabledProperty;

	CPFStatic::CPFStatic(const String &type) :
		WindowRenderer(type),
		d_frameEnabled(false),
		d_backgroundEnabled(false)
	{
		registerProperty(&d_frameEnabledProperty);
		registerProperty(&d_backgroundEnabledProperty);
	}

	CPFStatic::~CPFStatic()
	{}

	void CPFStatic::setFrameEnabled(bool setting)
	{
		if( d_frameEnabled!=setting ){
			d_frameEnabled = setting;
			d_window->invalidate();
		}
	}

	void CPFStatic::setBackgroundEnabled(bool setting)
	{
		if( d_backgroundEnabled!=setting ){
			d_backgroundEnabled = setting;
			d_window->invalidate();
		}
	}

	void CPFStatic::render()
	{
		// get WidgetLookNFeel for the assigned look
		const WidgetLookFeel &wlf = getLookNFeel();
		bool is_enabled = !d_window->isDisabled();

		// render frame section
		if( d_frameEnabled ){
			wlf.getStateImagery(is_enabled?"EnabledFrame":"DisabledFrame").render(*d_window);
		}

		// render background section
		if( d_backgroundEnabled ){
			if( d_frameEnabled ){
				wlf.getStateImagery(is_enabled?"WithFrameEnabledBackground":"WithFrameDisabledBackground").render(*d_window);
			}
			else{
				wlf.getStateImagery(is_enabled?"NoFrameEnabledBackground":"NoFrameDisabledBackground").render(*d_window);
			}
		}

		// render basic imagery
		wlf.getStateImagery(is_enabled?"Enabled":"Disabled").render(*d_window);
	}
}
