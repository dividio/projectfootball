/******************************************************************************
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
*       generated by dia/DAOcodegen.py                                        *
*       Version: 1.23                                                         *
******************************************************************************/

#ifndef CPFTEAMPLAYERS_H_
#define CPFTEAMPLAYERS_H_

#include <string>

#include "../../../utils/CDate.h"

class CPfTeamPlayers
{
public:
    CPfTeamPlayers();
    CPfTeamPlayers(const CPfTeamPlayers &obj);
    virtual ~CPfTeamPlayers();

    int getXFkRoleSelected() const;
    const std::string& getXFkRoleSelected_str() const;
    int getNLineupOrder() const;
    const std::string& getNLineupOrder_str() const;
    int getNWeight() const;
    const std::string& getNWeight_str() const;
    int getNSquadNumber() const;
    const std::string& getNSquadNumber_str() const;
    int getNHeight() const;
    const std::string& getNHeight_str() const;
    int getNSpeed() const;
    const std::string& getNSpeed_str() const;
    int getNKickPower() const;
    const std::string& getNKickPower_str() const;
    int getXTeamPlayer() const;
    const std::string& getXTeamPlayer_str() const;
    const std::string& getSShortName() const;
    const std::string& getSShortName_str() const;
    int getNFortitude() const;
    const std::string& getNFortitude_str() const;
    const std::string& getSName() const;
    const std::string& getSName_str() const;
    const std::string& getSPhoto() const;
    const std::string& getSPhoto_str() const;
    CDate getDBirthday() const;
    const std::string& getDBirthday_str() const;
    int getXFkCountry() const;
    const std::string& getXFkCountry_str() const;
    int getNMoral() const;
    const std::string& getNMoral_str() const;

    void setXFkRoleSelected(int XFkRoleSelected);
    void setXFkRoleSelected_str(const std::string &XFkRoleSelected);
    void setNLineupOrder(int NLineupOrder);
    void setNLineupOrder_str(const std::string &NLineupOrder);
    void setNWeight(int NWeight);
    void setNWeight_str(const std::string &NWeight);
    void setNSquadNumber(int NSquadNumber);
    void setNSquadNumber_str(const std::string &NSquadNumber);
    void setNHeight(int NHeight);
    void setNHeight_str(const std::string &NHeight);
    void setNSpeed(int NSpeed);
    void setNSpeed_str(const std::string &NSpeed);
    void setNKickPower(int NKickPower);
    void setNKickPower_str(const std::string &NKickPower);
    void setXTeamPlayer(int XTeamPlayer);
    void setXTeamPlayer_str(const std::string &XTeamPlayer);
    void setSShortName(const std::string &SShortName);
    void setSShortName_str(const std::string &SShortName);
    void setNFortitude(int NFortitude);
    void setNFortitude_str(const std::string &NFortitude);
    void setSName(const std::string &SName);
    void setSName_str(const std::string &SName);
    void setSPhoto(const std::string &SPhoto);
    void setSPhoto_str(const std::string &SPhoto);
    void setDBirthday(const CDate &DBirthday);
    void setDBirthday_str(const std::string &DBirthday);
    void setXFkCountry(int XFkCountry);
    void setXFkCountry_str(const std::string &XFkCountry);
    void setNMoral(int NMoral);
    void setNMoral_str(const std::string &NMoral);

private:
    std::string m_XFkRoleSelected;
    std::string m_NLineupOrder;
    std::string m_NWeight;
    std::string m_NSquadNumber;
    std::string m_NHeight;
    std::string m_NSpeed;
    std::string m_NKickPower;
    std::string m_XTeamPlayer;
    std::string m_SShortName;
    std::string m_NFortitude;
    std::string m_SName;
    std::string m_SPhoto;
    std::string m_DBirthday;
    std::string m_XFkCountry;
    std::string m_NMoral;

};
#endif /*CPFTEAMPLAYERS_H_*/
