/******************************************************************************
* Copyright (C) 2007 - Ikaro Games   www.ikarogames.com                       *
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


#ifndef __IState_H__
#define __IState_H__

#include <Ogre.h>
#include <OIS/OIS.h>

class IState:
    public Ogre::FrameListener, public OIS::MouseListener, public OIS::KeyListener
{

public:
  IState() {

  }

  virtual ~IState() {

  }

    virtual void enter() = 0;
    virtual void forcedLeave() = 0;
    virtual bool leave() = 0;
    virtual void update() = 0;

//    virtual bool frameEnded(const Ogre::FrameEvent& evt) = 0;
//    virtual bool frameStarted(const Ogre::FrameEvent& evt) = 0;

    virtual bool keyPressed(const OIS::KeyEvent& e) = 0;
    virtual bool keyReleased(const OIS::KeyEvent& e) = 0;
    virtual bool mouseMoved(const OIS::MouseEvent& e) = 0;
    virtual bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id) = 0;
    virtual bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id) = 0;

};
#endif // __IState_H__
