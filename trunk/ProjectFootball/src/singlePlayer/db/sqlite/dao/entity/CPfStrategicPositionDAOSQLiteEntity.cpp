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

#include <stdlib.h>
#include <string.h>

#include "CPfStrategicPositionDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfStrategicPositionDAOSQLiteEntity::CPfStrategicPositionDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfStrategicPositionDAOSQLiteEntity::~CPfStrategicPositionDAOSQLiteEntity()
{
}

void CPfStrategicPositionDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfStrategicPositionDAOSQLiteEntity::deleteReg(CPfStrategicPosition *reg)
{
    std::string sql("DELETE FROM PF_STRATEGIC_POSITION WHERE X_STRATEGIC_POSITION=");
    sql += "'"+reg->getXStrategicPosition_str()+"'";
    return exec(sql);
}

bool CPfStrategicPositionDAOSQLiteEntity::insertReg(CPfStrategicPosition *reg)
{
    std::string sql("INSERT INTO PF_STRATEGIC_POSITION (N_LINEUP_ORDER,X_FK_FORMATION,N_TOP_LEFT_AREA,X_FK_ROLE,N_OFFENSIVE_POS_X,N_BOTTOM_RIGHT_AREA,N_OFFENSIVE_POS_Z,N_DEFENSIVE_POS_Z,N_DEFENSIVE_POS_X,N_INITIAL_POS_Z,N_INITIAL_POS_X) VALUES (");
    sql += (reg->getNLineupOrder_str()=="")?"NULL":"'"+reg->getNLineupOrder_str()+"'";
    sql += (reg->getXFkFormation_str()=="")?",NULL":",'"+reg->getXFkFormation_str()+"'";
    sql += (reg->getNTopLeftArea_str()=="")?",NULL":",'"+reg->getNTopLeftArea_str()+"'";
    sql += (reg->getXFkRole_str()=="")?",NULL":",'"+reg->getXFkRole_str()+"'";
    sql += (reg->getNOffensivePosX_str()=="")?",NULL":",'"+reg->getNOffensivePosX_str()+"'";
    sql += (reg->getNBottomRightArea_str()=="")?",NULL":",'"+reg->getNBottomRightArea_str()+"'";
    sql += (reg->getNOffensivePosZ_str()=="")?",NULL":",'"+reg->getNOffensivePosZ_str()+"'";
    sql += (reg->getNDefensivePosZ_str()=="")?",NULL":",'"+reg->getNDefensivePosZ_str()+"'";
    sql += (reg->getNDefensivePosX_str()=="")?",NULL":",'"+reg->getNDefensivePosX_str()+"'";
    sql += (reg->getNInitialPosZ_str()=="")?",NULL":",'"+reg->getNInitialPosZ_str()+"'";
    sql += (reg->getNInitialPosX_str()=="")?",NULL":",'"+reg->getNInitialPosX_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXStrategicPosition(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfStrategicPositionDAOSQLiteEntity::updateReg(CPfStrategicPosition *reg)
{
    std::string sql("UPDATE PF_STRATEGIC_POSITION SET ");
    sql += (reg->getNLineupOrder_str()=="")?" N_LINEUP_ORDER=NULL":" N_LINEUP_ORDER='"+reg->getNLineupOrder_str()+"'";
    sql += (reg->getXFkFormation_str()=="")?",X_FK_FORMATION=NULL":",X_FK_FORMATION='"+reg->getXFkFormation_str()+"'";
    sql += (reg->getNTopLeftArea_str()=="")?",N_TOP_LEFT_AREA=NULL":",N_TOP_LEFT_AREA='"+reg->getNTopLeftArea_str()+"'";
    sql += (reg->getXFkRole_str()=="")?",X_FK_ROLE=NULL":",X_FK_ROLE='"+reg->getXFkRole_str()+"'";
    sql += (reg->getNOffensivePosX_str()=="")?",N_OFFENSIVE_POS_X=NULL":",N_OFFENSIVE_POS_X='"+reg->getNOffensivePosX_str()+"'";
    sql += (reg->getNBottomRightArea_str()=="")?",N_BOTTOM_RIGHT_AREA=NULL":",N_BOTTOM_RIGHT_AREA='"+reg->getNBottomRightArea_str()+"'";
    sql += (reg->getNOffensivePosZ_str()=="")?",N_OFFENSIVE_POS_Z=NULL":",N_OFFENSIVE_POS_Z='"+reg->getNOffensivePosZ_str()+"'";
    sql += (reg->getXStrategicPosition_str()=="")?",X_STRATEGIC_POSITION=NULL":",X_STRATEGIC_POSITION='"+reg->getXStrategicPosition_str()+"'";
    sql += (reg->getNDefensivePosZ_str()=="")?",N_DEFENSIVE_POS_Z=NULL":",N_DEFENSIVE_POS_Z='"+reg->getNDefensivePosZ_str()+"'";
    sql += (reg->getNDefensivePosX_str()=="")?",N_DEFENSIVE_POS_X=NULL":",N_DEFENSIVE_POS_X='"+reg->getNDefensivePosX_str()+"'";
    sql += (reg->getNInitialPosZ_str()=="")?",N_INITIAL_POS_Z=NULL":",N_INITIAL_POS_Z='"+reg->getNInitialPosZ_str()+"'";
    sql += (reg->getNInitialPosX_str()=="")?",N_INITIAL_POS_X=NULL":",N_INITIAL_POS_X='"+reg->getNInitialPosX_str()+"'";
    sql += " WHERE X_STRATEGIC_POSITION='"+reg->getXStrategicPosition_str()+"'";
    return exec(sql);
}

void CPfStrategicPositionDAOSQLiteEntity::freeVector(std::vector<CPfStrategicPosition*>* vector )
{
    std::vector<CPfStrategicPosition*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfStrategicPosition* CPfStrategicPositionDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfStrategicPosition *destiny = new CPfStrategicPosition();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfStrategicPosition*> * CPfStrategicPositionDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfStrategicPosition*> *container = new std::vector<CPfStrategicPosition*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfStrategicPositionDAOSQLiteEntity::exec(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    bool correct = true;
    int result = sqlite3_exec(m_database, sql.c_str(), NULL, NULL, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        correct = false;
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return correct;
}

int CPfStrategicPositionDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfStrategicPosition *destiny = (CPfStrategicPosition*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "N_LINEUP_ORDER")==0 ){
                destiny->setNLineupOrder_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_FORMATION")==0 ){
                destiny->setXFkFormation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_TOP_LEFT_AREA")==0 ){
                destiny->setNTopLeftArea_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_ROLE")==0 ){
                destiny->setXFkRole_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_OFFENSIVE_POS_X")==0 ){
                destiny->setNOffensivePosX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_BOTTOM_RIGHT_AREA")==0 ){
                destiny->setNBottomRightArea_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_OFFENSIVE_POS_Z")==0 ){
                destiny->setNOffensivePosZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_STRATEGIC_POSITION")==0 ){
                destiny->setXStrategicPosition_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_DEFENSIVE_POS_Z")==0 ){
                destiny->setNDefensivePosZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_DEFENSIVE_POS_X")==0 ){
                destiny->setNDefensivePosX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_INITIAL_POS_Z")==0 ){
                destiny->setNInitialPosZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_INITIAL_POS_X")==0 ){
                destiny->setNInitialPosX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfStrategicPositionDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfStrategicPosition*> *container = (std::vector<CPfStrategicPosition*> *)object;
        CPfStrategicPosition *destiny = new CPfStrategicPosition();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "N_LINEUP_ORDER")==0 ){
                destiny->setNLineupOrder_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_FORMATION")==0 ){
                destiny->setXFkFormation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_TOP_LEFT_AREA")==0 ){
                destiny->setNTopLeftArea_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_ROLE")==0 ){
                destiny->setXFkRole_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_OFFENSIVE_POS_X")==0 ){
                destiny->setNOffensivePosX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_BOTTOM_RIGHT_AREA")==0 ){
                destiny->setNBottomRightArea_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_OFFENSIVE_POS_Z")==0 ){
                destiny->setNOffensivePosZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_STRATEGIC_POSITION")==0 ){
                destiny->setXStrategicPosition_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_DEFENSIVE_POS_Z")==0 ){
                destiny->setNDefensivePosZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_DEFENSIVE_POS_X")==0 ){
                destiny->setNDefensivePosX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_INITIAL_POS_Z")==0 ){
                destiny->setNInitialPosZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_INITIAL_POS_X")==0 ){
                destiny->setNInitialPosX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

