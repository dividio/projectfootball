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

#include "CPFRotatingText.h"

#include "../../../../utils/CLog.h"

namespace CEGUI{
	const utf8	CPFRotatingText::TypeName[]	= "PF/RotatingText";

	CPFRotatingTextProperties::TextSpeed	CPFRotatingText::d_textSpeedProperty;

	CPFRotatingText::CPFRotatingText(const String &type) :
		CPFStaticText(type),
		d_textSpeed(0.1f),
		m_thread(boost::bind(&CPFRotatingText::runThread, this)),
		m_stopThread(false)
	{
		registerProperty(&d_textSpeedProperty);
	}

	CPFRotatingText::~CPFRotatingText()
	{
		m_stopThread = true;

		m_thread.join(); // wait for the thread finish
	}

	void CPFRotatingText::render()
	{
		// base class rendering
		CPFStatic::render();

		// text rendering
		renderRotatingText();
	}

	void CPFRotatingText::setTextSpeed(float setting)
	{
		d_textSpeed = setting;
	}

	void CPFRotatingText::renderRotatingText()
	{
		Font* font = d_window->getFont();
		// can't render text without a font :)
		if( font==NULL){
			return;
		}

		// get destination area for the text.
		Rect absarea(getTextRenderArea());
		Rect clipper(absarea);

        if (!d_formatValid) {
            updateFormatting(clipper.getSize());
        }

        float textHeight = d_formattedRenderedString->getHorizontalExtent();

		Scrollbar* vertScrollbar = getVertScrollbar();
		Scrollbar* horzScrollbar = getHorzScrollbar();

		// calculate X offset
		static float xOffset = horzScrollbar->getPageSize();
		if( xOffset<-(horzScrollbar->getDocumentSize()+horzScrollbar->getPageSize()) ){
			xOffset = horzScrollbar->getPageSize();
		}
		static boost::system_time previous_time = boost::get_system_time();
		boost::system_time time = boost::get_system_time();
		boost::system_time::time_duration_type time_step = (time-previous_time);
		xOffset -= (static_cast<float>(time_step.total_milliseconds())*d_textSpeed);
		previous_time = time;
		absarea.offset(Point(xOffset, 0));

		// see if we may need to adjust horizontal position
		if( horzScrollbar->isVisible() ){
			switch(d_horzFormatting)
			{
			case LeftAligned:
			case WordWrapLeftAligned:
			case HorzJustified:
			case WordWrapJustified:
				absarea.offset(Point(-horzScrollbar->getScrollPosition(), 0));
				break;

			case HorzCentred:
			case WordWrapCentred:
				absarea.setWidth(horzScrollbar->getDocumentSize());
				absarea.offset(Point(-horzScrollbar->getScrollPosition(), 0));
				break;

			case RightAligned:
			case WordWrapRightAligned:
				absarea.offset(Point(horzScrollbar->getScrollPosition(), 0));
				break;
			}
		}

		// adjust y positioning according to formatting option
		switch(d_vertFormatting)
		{
		case TopAligned:
			absarea.d_top -= vertScrollbar->getScrollPosition();
			break;

		case VertCentred:
			// if scroll bar is in use, act like TopAligned
			if( vertScrollbar->isVisible() ){
				absarea.d_top -= vertScrollbar->getScrollPosition();
			}
			// no scroll bar, so centre text instead.
			else{
				absarea.d_top += PixelAligned((absarea.getHeight() - textHeight) * 0.5f);
			}
			break;

		case BottomAligned:
			absarea.d_top = absarea.d_bottom - textHeight;
			absarea.d_top += vertScrollbar->getScrollPosition();
			break;
		}

		// offset the font little down so that it's centered within its own spacing
		absarea.d_top += (font->getLineSpacing() - font->getFontHeight()) * 0.5f;
		// calculate final colours
		ColourRect final_cols(d_textCols);
		final_cols.modulateAlpha(d_window->getEffectiveAlpha());
		// cache the text for rendering.

		// cache the text for rendering.
		d_formattedRenderedString->draw(d_window->getGeometryBuffer(),absarea.getPosition(),&final_cols, &clipper);

	}


	void CPFRotatingText::runThread()
	{
		LOG_DEBUG("A thread has started!");
		m_stopThread = false;
		for(;;){
			if( m_stopThread ){
				break;
			}

			if( d_window ){
				d_window->invalidate();
			}
			boost::system_time time = boost::get_system_time();
			time += boost::posix_time::milliseconds(10);
			m_thread.sleep(time);
		}
		LOG_DEBUG("A thread has finished!");
	}
}
