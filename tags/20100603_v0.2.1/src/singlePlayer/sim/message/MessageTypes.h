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


#ifndef MESSAGETYPES_H_
#define MESSAGETYPES_H_

enum MessageType
{
    Msg_StartMatch,     // Sim to R
    Msg_BeforeStart,    // R to T
    Msg_HalfTime,       // R to T
    Msg_EndMatch,       // R to T, T to P
    Msg_KickOff,        // R to T, T to P
    Msg_TouchBall,      // Sim to R
    Msg_ReceiveBall,
    Msg_PassToMe,
    Msg_SupportAttacker,
    Msg_GoHome,         // T to P
    Msg_KickIn,         // T to P
    Msg_Interrupt,      // T to P
    Msg_PlayOn,         // R to T, T to P
    Msg_Wait
};

#endif // MESSAGETYPES_H_
