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
*       generated by dia/DAOcodegen.py                                        *
*       Version: 1.4                                                          *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfEquipos.h"

CPfEquipos::CPfEquipos()
{
    m_XFkPais = "0";
    m_XEquipo = "0";
    m_SEquipo = "";
    m_SRutaEscudo = "";
}

CPfEquipos::~CPfEquipos()
{
}

int CPfEquipos::getXFkPais_int()
{
    return atoi(m_XFkPais.c_str());
}

const std::string* CPfEquipos::getXFkPais()
{
    return &m_XFkPais;
}

int CPfEquipos::getXEquipo_int()
{
    return atoi(m_XEquipo.c_str());
}

const std::string* CPfEquipos::getXEquipo()
{
    return &m_XEquipo;
}

const std::string* CPfEquipos::getSEquipo()
{
    return &m_SEquipo;
}

const std::string* CPfEquipos::getSRutaEscudo()
{
    return &m_SRutaEscudo;
}

void CPfEquipos::setXFkPais(int XFkPais)
{
    std::ostringstream stream;
    stream << XFkPais;
    m_XFkPais = stream.str();
}

void CPfEquipos::setXFkPais(const std::string XFkPais)
{
    m_XFkPais = XFkPais;
}

void CPfEquipos::setXEquipo(int XEquipo)
{
    std::ostringstream stream;
    stream << XEquipo;
    m_XEquipo = stream.str();
}

void CPfEquipos::setXEquipo(const std::string XEquipo)
{
    m_XEquipo = XEquipo;
}

void CPfEquipos::setSEquipo(const std::string SEquipo)
{
    m_SEquipo = SEquipo;
}

void CPfEquipos::setSRutaEscudo(const std::string SRutaEscudo)
{
    m_SRutaEscudo = SRutaEscudo;
}

