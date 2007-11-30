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


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "../DBManager/CDAOAbstractFactory.h"
#include "../DBManager/IDAOFactory.h"
#include "../DBManager/IPfEquiposDAO.h"

//int main(void) {
//	cout << "Aplicación test:" << endl;
//	CPfEquipos *equipo;
//	CPfEquipos *equipo1 = new CPfEquipos("1", "1", "Athletic Bilbao", "ruta/escudo.png");
//	CPfEquipos *equipo2 = new CPfEquipos("2", "2", "Sevilla", "ruta/escudo.png");
//	CPfEquipos *equipo3 = new CPfEquipos("3", "3", "Real Mandril", "ruta/escudo.png");
//
//	vector<CPfEquipos *> *equipos;
//
//	IDAOFactory *factory = CDAOAbstractFactory::getIDAOFactory();
//
//	IPfEquiposDAO *equiposDAO = factory->getIPfEquiposDAO();
//
//	equiposDAO->insert(equipo1);
//	equiposDAO->insert(equipo2);
//	equiposDAO->insert(equipo3);
//
//
//	int cont = 4;
//	char key [33];
//	for (cont = 4; cont <= 4999; cont++) {
//		sprintf(key, "%d", cont);
//		equipo = new CPfEquipos("3", key, "boo", "RUTA/BOO");
//		equiposDAO->insert(equipo);
//		delete equipo;
//	}
//	sprintf(key, "%d", cont);
//	equipo = new CPfEquipos("5", key, "Er gueno", "RUTA/del/gueno.png");
//	equiposDAO->insert(equipo);
//	delete equipo;
//
//
//	for (cont = 5000; cont <= 10000; cont++) {
//		sprintf(key, "%d", cont);
//		equipo = new CPfEquipos("3", key, "boo", "RUTA/BOO");
//		equiposDAO->insert(equipo);
//		delete equipo;
//	}
//
//
//	cout << "Equipos insertados." << endl;
//
//	string val = "1";
//	equipo = equiposDAO->findByXEquipo(val);
//	cout << "Encontrado el equipo: " << equipo->getSEquipo()->c_str() << endl;
//
//
//
//	equipos = equiposDAO->findVectorByXFkPais("5");
//
//	cout << "Busqueda realizada." << endl;
//
//	if(!equipos->empty())
//	        cout << "EL GANADOR ES: " << equipos->front()->getSEquipo()->c_str() <<endl;
//	else
//		cout << "Vector Vacio" << endl;
//
//	equipo3->setSEquipo("Real Madrid");
//
//	equiposDAO->update(equipo3);
//
//	cout << "Registro actualizado" << endl;
//
//	equiposDAO->deleteReg(equipo2);
//
//	cout << "Registro eliminado" << endl;
//
//	delete equipo;
//	delete equipo1;
//	delete equipo2;
//	delete equipo3;
//
//    std::vector<CPfEquipos*>::iterator it;
//    for( it = equipos->begin(); it != equipos->end(); it++ ){
//        delete (*it);
//        (*it) = NULL;
//    }
//
//	return EXIT_SUCCESS;
//}
