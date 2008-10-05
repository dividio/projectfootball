/******************************************************************************
* Copyright (C) 2008 - Ikaro Games   www.ikarogames.com                       *
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

#include <cmath>

#include "CMessage.h"


std::string CMessage::m_pCtorName = "CMessage_p_ctor";

CMessage::CMessage()
{
    Sender = -1;
    Receiver = -1;
    Msg = -1;
    DispatchTime = -1;
    ExtraInfo = 0;
}


CMessage::CMessage(double time, int sender, int receiver, int msg, void *info)
{
    Sender = sender;
    Receiver = receiver;
    Msg = msg;
    DispatchTime = time;
    ExtraInfo = info;
}


CMessage::~CMessage()
{
}

bool CMessage::operator()(const CMessage& message) const
{
    return this->operator==(message);
}


bool CMessage::operator==(const CMessage& message) const
{
  return (fabs(DispatchTime-message.DispatchTime) < SMALLEST_DELAY) &&
          (Sender == message.Sender)        &&
          (Receiver == message.Receiver)    &&
          (Msg == message.Msg);
}


bool CMessage::operator<(const CMessage& message) const
{
  if (this->operator==(message)) {
    return false;
  } else {
    return  (DispatchTime < message.DispatchTime);
  }
}
