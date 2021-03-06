/******************************************************************************
* Copyright (C) 2010 - Ikaro Games   www.ikarogames.com                       *
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

#ifndef CPFSTRATEGICPOSITIONS_H_
#define CPFSTRATEGICPOSITIONS_H_

#include <string>

class CPfStrategicPositions
{
public:
    CPfStrategicPositions();
    CPfStrategicPositions(const CPfStrategicPositions &obj);
    virtual ~CPfStrategicPositions();

    double getNAttractionX() const;
    const std::string& getNAttractionX_str() const;
    int getNLineupOrder() const;
    const std::string& getNLineupOrder_str() const;
    int getNBottomRightAreaX() const;
    const std::string& getNBottomRightAreaX_str() const;
    int getXFkFormation() const;
    const std::string& getXFkFormation_str() const;
    int getNTopLeftAreaZ() const;
    const std::string& getNTopLeftAreaZ_str() const;
    int getXFkRole() const;
    const std::string& getXFkRole_str() const;
    int getNTopLeftAreaX() const;
    const std::string& getNTopLeftAreaX_str() const;
    int getNOffensivePosX() const;
    const std::string& getNOffensivePosX_str() const;
    int getNOffensivePosZ() const;
    const std::string& getNOffensivePosZ_str() const;
    double getNAttractionZ() const;
    const std::string& getNAttractionZ_str() const;
    int getXStrategicPosition() const;
    const std::string& getXStrategicPosition_str() const;
    int getNDefensivePosZ() const;
    const std::string& getNDefensivePosZ_str() const;
    int getNDefensivePosX() const;
    const std::string& getNDefensivePosX_str() const;
    int getNInitialPosZ() const;
    const std::string& getNInitialPosZ_str() const;
    int getNInitialPosX() const;
    const std::string& getNInitialPosX_str() const;
    int getNBottomRightAreaZ() const;
    const std::string& getNBottomRightAreaZ_str() const;

    void setNAttractionX(double NAttractionX);
    void setNAttractionX_str(const std::string &NAttractionX);
    void setNLineupOrder(int NLineupOrder);
    void setNLineupOrder_str(const std::string &NLineupOrder);
    void setNBottomRightAreaX(int NBottomRightAreaX);
    void setNBottomRightAreaX_str(const std::string &NBottomRightAreaX);
    void setXFkFormation(int XFkFormation);
    void setXFkFormation_str(const std::string &XFkFormation);
    void setNTopLeftAreaZ(int NTopLeftAreaZ);
    void setNTopLeftAreaZ_str(const std::string &NTopLeftAreaZ);
    void setXFkRole(int XFkRole);
    void setXFkRole_str(const std::string &XFkRole);
    void setNTopLeftAreaX(int NTopLeftAreaX);
    void setNTopLeftAreaX_str(const std::string &NTopLeftAreaX);
    void setNOffensivePosX(int NOffensivePosX);
    void setNOffensivePosX_str(const std::string &NOffensivePosX);
    void setNOffensivePosZ(int NOffensivePosZ);
    void setNOffensivePosZ_str(const std::string &NOffensivePosZ);
    void setNAttractionZ(double NAttractionZ);
    void setNAttractionZ_str(const std::string &NAttractionZ);
    void setXStrategicPosition(int XStrategicPosition);
    void setXStrategicPosition_str(const std::string &XStrategicPosition);
    void setNDefensivePosZ(int NDefensivePosZ);
    void setNDefensivePosZ_str(const std::string &NDefensivePosZ);
    void setNDefensivePosX(int NDefensivePosX);
    void setNDefensivePosX_str(const std::string &NDefensivePosX);
    void setNInitialPosZ(int NInitialPosZ);
    void setNInitialPosZ_str(const std::string &NInitialPosZ);
    void setNInitialPosX(int NInitialPosX);
    void setNInitialPosX_str(const std::string &NInitialPosX);
    void setNBottomRightAreaZ(int NBottomRightAreaZ);
    void setNBottomRightAreaZ_str(const std::string &NBottomRightAreaZ);

private:
    std::string m_NAttractionX;
    std::string m_NLineupOrder;
    std::string m_NBottomRightAreaX;
    std::string m_XFkFormation;
    std::string m_NTopLeftAreaZ;
    std::string m_XFkRole;
    std::string m_NTopLeftAreaX;
    std::string m_NOffensivePosX;
    std::string m_NOffensivePosZ;
    std::string m_NAttractionZ;
    std::string m_XStrategicPosition;
    std::string m_NDefensivePosZ;
    std::string m_NDefensivePosX;
    std::string m_NInitialPosZ;
    std::string m_NInitialPosX;
    std::string m_NBottomRightAreaZ;

};
#endif /*CPFSTRATEGICPOSITIONS_H_*/
