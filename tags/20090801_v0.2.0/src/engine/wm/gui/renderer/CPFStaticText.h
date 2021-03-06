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

#ifndef CPFSTATICTEXT_H_
#define CPFSTATICTEXT_H_

#include "CPFStatic.h"
#include "CPFStaticTextProperties.h"

namespace CEGUI{
	/*!
	 * \brief
	 * 		Based in FalagardStaticText class.
	 * 		This class requires LookNFeel to be assigned.  The LookNFeel should provide the following:
	 *
	 * 		States:
	 * 			- Enabled                     - basic rendering for enabled state.
	 * 			- Disabled                    - basic rendering for disabled state.
	 * 			- EnabledFrame                - frame rendering for enabled state
	 * 			- DisabledFrame               - frame rendering for disabled state.
	 * 			- WithFrameEnabledBackground  - backdrop rendering for enabled state with frame enabled.
	 * 			- WithFrameDisabledBackground - backdrop rendering for disabled state with frame enabled.
	 * 			- NoFrameEnabledBackground    - backdrop rendering for enabled state with frame disabled.
	 * 			- NoFrameDisabledBackground   - backdrop rendering for disabled state with frame disabled.
	 *
	 * 		Named Areas (missing areas will default to 'WithFrameTextRenderArea'):
	 * 			WithFrameTextRenderArea
	 * 			WithFrameTextRenderAreaHScroll
	 * 			WithFrameTextRenderAreaVScroll
	 * 			WithFrameTextRenderAreaHVScroll
	 * 			NoFrameTextRenderArea
	 * 			NoFrameTextRenderAreaHScroll
	 * 			NoFrameTextRenderAreaVScroll
	 * 			NoFrameTextRenderAreaHVScroll
	 */
	class CPFStaticText : public CPFStatic{
	public:
		static const utf8	TypeName[];	//!< type name for this widget.

		/*************************************************************************
		 * Formatting Enumerations
		 *************************************************************************/
		/*!
		 * \brief
		 * 		Enumeration of horizontal formatting options for falagard static text widgets
		 */
		enum HorzFormatting{
			LeftAligned,            //!< Text is output as a single line of text with the first character aligned with the left edge of the widget.
			RightAligned,           //!< Text is output as a single line of text with the last character aligned with the right edge of the widget.
			HorzCentred,            //!< Text is output as a single line of text horizontally centred within the widget.
			HorzJustified,          //!< Text is output as a single line of text with the first and last characters aligned with the edges of the widget.
			WordWrapLeftAligned,    //!< Text is output as multiple word-wrapped lines of text with the first character of each line aligned with the left edge of the widget.
			WordWrapRightAligned,   //!< Text is output as multiple word-wrapped lines of text with the last character of each line aligned with the right edge of the widget.
			WordWrapCentred,        //!< Text is output as multiple word-wrapped lines of text with each line horizontally centered within the widget.
			WordWrapJustified       //!< Text is output as multiple word-wrapped lines of text with the first and last characters of each line aligned with the edges of the widget.
		};

		/*!
		 * \brief
		 * 		Enumeration of vertical formatting options for a falagard static text widgets
		 */
		enum VertFormatting{
			TopAligned,     //!< Text is output with the top of first line of text aligned with the top edge of the widget.
			BottomAligned,  //!< Text is output with the bottom of last line of text aligned with the bottom edge of the widget.
			VertCentred     //!< Text is output vertically centred within the widget.
		};

		/*************************************************************************
		 * Child Widget name suffix constants
		 *************************************************************************/
		static const String VertScrollbarNameSuffix;   //!< Widget name suffix for the vertical scrollbar component.
		static const String HorzScrollbarNameSuffix;   //!< Widget name suffix for the horizontal scrollbar component.

	public:
		CPFStaticText(const String &type);
		virtual ~CPFStaticText();

		/*************************************************************************
		 * Scrolled text implementation
		 *************************************************************************/
		/*!
		 * \brief
		 * 		Return a ColourRect object containing the colours used when rendering this widget.
		 */
		ColourRect    getTextColours(void) const                {return d_textCols;}

		/*!
		 * \brief
		 * 		Return the current horizontal formatting option set for this widget.
		 */
		HorzFormatting    getHorizontalFormatting(void) const   {return    d_horzFormatting;}

		/*!
		 * \brief
		 * 		Return the current vertical formatting option set for this widget.
		 */
		VertFormatting    getVerticalFormatting(void) const     {return d_vertFormatting;}

		/*!
		 * \brief
		 * 		Sets the colours to be applied when rendering the text.
		 */
		void    setTextColours(const ColourRect& colours);

		/*!
		 * \brief
		 * 		Set the vertical formatting required for the text.
		 */
		void    setVerticalFormatting(VertFormatting v_fmt);

		/*!
		 * \brief
		 * 		Set the horizontal formatting required for the text.
		 */
		void    setHorizontalFormatting(HorzFormatting h_fmt);

		/*!
		 * \brief
		 * 		Return whether the vertical scroll bar is set to be shown if needed.
		 */
		bool    isVerticalScrollbarEnabled(void) const  {return d_enableVertScrollbar;}

		/*!
		 * \brief
		 * 		Return whether the horizontal scroll bar is set to be shown if needed.
		 */
		bool    isHorizontalScrollbarEnabled(void) const    {return d_enableHorzScrollbar;}

		/*!
		 * \brief
		 * 		Set whether the vertical scroll bar will be shown if needed.
		 */
		void    setVerticalScrollbarEnabled(bool setting);

		/*!
		 * \brief
		 * 		Set whether the horizontal scroll bar will be shown if needed.
		 */
		void    setHorizontalScrollbarEnabled(bool setting);

		void render(void);

	protected:
		// overridden from FalagardStatic base class
		void onLookNFeelAssigned();
		void onLookNFeelUnassigned();

		// text field with scrollbars methods
		void renderScrolledText(void);
		void configureScrollbars(void);
		Scrollbar* getVertScrollbar(void) const;
		Scrollbar* getHorzScrollbar(void) const;
		Rect getTextRenderArea(void) const;
		Size getDocumentSize(const Rect& renderArea) const;

		// overridden event handlers
		bool onTextChanged(const EventArgs& e);
		bool onSized(const EventArgs& e);
		bool onFontChanged(const EventArgs& e);
		bool onMouseWheel(const EventArgs& e);

		// event subscribers
		bool handleScrollbarChange(const EventArgs& e);

		// properties
		static CPFStaticTextProperties::TextColours    d_textColoursProperty;
		static CPFStaticTextProperties::VertFormatting d_vertFormattingProperty;
		static CPFStaticTextProperties::HorzFormatting d_horzFormattingProperty;
		static CPFStaticTextProperties::VertScrollbar  d_vertScrollbarProperty;
		static CPFStaticTextProperties::HorzScrollbar  d_horzScrollbarProperty;

		// implementation data
		HorzFormatting  d_horzFormatting;       //!< Horizontal formatting to be applied to the text.
		VertFormatting  d_vertFormatting;       //!< Vertical formatting to be applied to the text.
		ColourRect      d_textCols;             //!< Colours used when rendering the text.
		bool            d_enableVertScrollbar;  //!< true if vertical scroll bar is enabled.
		bool            d_enableHorzScrollbar;  //!< true if horizontal scroll bar is enabled.

		typedef std::vector<Event::Connection> ConnectionList;
		ConnectionList  d_connections;
	};
	CEGUI_DEFINE_WR_FACTORY(CPFStaticText)
}


#endif /* CPFSTATICTEXT_H_ */
