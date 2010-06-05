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

#include <stdlib.h>
#include <string.h>

#include "CPfStrategicPositionsDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfStrategicPositionsDAOSQLiteEntity::CPfStrategicPositionsDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfStrategicPositionsDAOSQLiteEntity::~CPfStrategicPositionsDAOSQLiteEntity()
{
}

void CPfStrategicPositionsDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfStrategicPositionsDAOSQLiteEntity::deleteReg(CPfStrategicPositions *reg)
{
    std::string sql("DELETE FROM PF_STRATEGIC_POSITIONS WHERE X_STRATEGIC_POSITION=");
    sql += "'"+reg->getXStrategicPosition_str()+"'";
    return exec(sql);
}

bool CPfStrategicPositionsDAOSQLiteEntity::insertReg(CPfStrategicPositions *reg)
{
    std::string sql("INSERT INTO PF_STRATEGIC_POSITIONS (N_ATTRACTION_X,N_LINEUP_ORDER,N_BOTTOM_RIGHT_AREA_X,X_FK_FORMATION,N_TOP_LEFT_AREA_Z,X_FK_ROLE,N_TOP_LEFT_AREA_X,N_OFFENSIVE_POS_X,N_OFFENSIVE_POS_Z,N_ATTRACTION_Z,N_DEFENSIVE_POS_Z,N_DEFENSIVE_POS_X,N_INITIAL_POS_Z,N_INITIAL_POS_X,N_BOTTOM_RIGHT_AREA_Z) VALUES (");
    sql += (reg->getNAttractionX_str()=="")?"NULL":"'"+reg->getNAttractionX_str()+"'";
    sql += (reg->getNLineupOrder_str()=="")?",NULL":",'"+reg->getNLineupOrder_str()+"'";
    sql += (reg->getNBottomRightAreaX_str()=="")?",NULL":",'"+reg->getNBottomRightAreaX_str()+"'";
    sql += (reg->getXFkFormation_str()=="")?",NULL":",'"+reg->getXFkFormation_str()+"'";
    sql += (reg->getNTopLeftAreaZ_str()=="")?",NULL":",'"+reg->getNTopLeftAreaZ_str()+"'";
    sql += (reg->getXFkRole_str()=="")?",NULL":",'"+reg->getXFkRole_str()+"'";
    sql += (reg->getNTopLeftAreaX_str()=="")?",NULL":",'"+reg->getNTopLeftAreaX_str()+"'";
    sql += (reg->getNOffensivePosX_str()=="")?",NULL":",'"+reg->getNOffensivePosX_str()+"'";
    sql += (reg->getNOffensivePosZ_str()=="")?",NULL":",'"+reg->getNOffensivePosZ_str()+"'";
    sql += (reg->getNAttractionZ_str()=="")?",NULL":",'"+reg->getNAttractionZ_str()+"'";
    sql += (reg->getNDefensivePosZ_str()=="")?",NULL":",'"+reg->getNDefensivePosZ_str()+"'";
    sql += (reg->getNDefensivePosX_str()=="")?",NULL":",'"+reg->getNDefensivePosX_str()+"'";
    sql += (reg->getNInitialPosZ_str()=="")?",NULL":",'"+reg->getNInitialPosZ_str()+"'";
    sql += (reg->getNInitialPosX_str()=="")?",NULL":",'"+reg->getNInitialPosX_str()+"'";
    sql += (reg->getNBottomRightAreaZ_str()=="")?",NULL":",'"+reg->getNBottomRightAreaZ_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXStrategicPosition(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfStrategicPositionsDAOSQLiteEntity::updateReg(CPfStrategicPositions *reg)
{
    std::string sql("UPDATE PF_STRATEGIC_POSITIONS SET ");
    sql += (reg->getNAttractionX_str()=="")?" N_ATTRACTION_X=NULL":" N_ATTRACTION_X='"+reg->getNAttractionX_str()+"'";
    sql += (reg->getNLineupOrder_str()=="")?",N_LINEUP_ORDER=NULL":",N_LINEUP_ORDER='"+reg->getNLineupOrder_str()+"'";
    sql += (reg->getNBottomRightAreaX_str()=="")?",N_BOTTOM_RIGHT_AREA_X=NULL":",N_BOTTOM_RIGHT_AREA_X='"+reg->getNBottomRightAreaX_str()+"'";
    sql += (reg->getXFkFormation_str()=="")?",X_FK_FORMATION=NULL":",X_FK_FORMATION='"+reg->getXFkFormation_str()+"'";
    sql += (reg->getNTopLeftAreaZ_str()=="")?",N_TOP_LEFT_AREA_Z=NULL":",N_TOP_LEFT_AREA_Z='"+reg->getNTopLeftAreaZ_str()+"'";
    sql += (reg->getXFkRole_str()=="")?",X_FK_ROLE=NULL":",X_FK_ROLE='"+reg->getXFkRole_str()+"'";
    sql += (reg->getNTopLeftAreaX_str()=="")?",N_TOP_LEFT_AREA_X=NULL":",N_TOP_LEFT_AREA_X='"+reg->getNTopLeftAreaX_str()+"'";
    sql += (reg->getNOffensivePosX_str()=="")?",N_OFFENSIVE_POS_X=NULL":",N_OFFENSIVE_POS_X='"+reg->getNOffensivePosX_str()+"'";
    sql += (reg->getNOffensivePosZ_str()=="")?",N_OFFENSIVE_POS_Z=NULL":",N_OFFENSIVE_POS_Z='"+reg->getNOffensivePosZ_str()+"'";
    sql += (reg->getNAttractionZ_str()=="")?",N_ATTRACTION_Z=NULL":",N_ATTRACTION_Z='"+reg->getNAttractionZ_str()+"'";
    sql += (reg->getXStrategicPosition_str()=="")?",X_STRATEGIC_POSITION=NULL":",X_STRATEGIC_POSITION='"+reg->getXStrategicPosition_str()+"'";
    sql += (reg->getNDefensivePosZ_str()=="")?",N_DEFENSIVE_POS_Z=NULL":",N_DEFENSIVE_POS_Z='"+reg->getNDefensivePosZ_str()+"'";
    sql += (reg->getNDefensivePosX_str()=="")?",N_DEFENSIVE_POS_X=NULL":",N_DEFENSIVE_POS_X='"+reg->getNDefensivePosX_str()+"'";
    sql += (reg->getNInitialPosZ_str()=="")?",N_INITIAL_POS_Z=NULL":",N_INITIAL_POS_Z='"+reg->getNInitialPosZ_str()+"'";
    sql += (reg->getNInitialPosX_str()=="")?",N_INITIAL_POS_X=NULL":",N_INITIAL_POS_X='"+reg->getNInitialPosX_str()+"'";
    sql += (reg->getNBottomRightAreaZ_str()=="")?",N_BOTTOM_RIGHT_AREA_Z=NULL":",N_BOTTOM_RIGHT_AREA_Z='"+reg->getNBottomRightAreaZ_str()+"'";
    sql += " WHERE X_STRATEGIC_POSITION='"+reg->getXStrategicPosition_str()+"'";
    return exec(sql);
}

void CPfStrategicPositionsDAOSQLiteEntity::freeVector(std::vector<CPfStrategicPositions*>* vector )
{
    std::vector<CPfStrategicPositions*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfStrategicPositions* CPfStrategicPositionsDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfStrategicPositions *destiny = new CPfStrategicPositions();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfStrategicPositions*> * CPfStrategicPositionsDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfStrategicPositions*> *container = new std::vector<CPfStrategicPositions*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfStrategicPositionsDAOSQLiteEntity::exec(const std::string &sql)
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

int CPfStrategicPositionsDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfStrategicPositions *destiny = (CPfStrategicPositions*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "N_ATTRACTION_X")==0 ){
                destiny->setNAttractionX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_LINEUP_ORDER")==0 ){
                destiny->setNLineupOrder_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_BOTTOM_RIGHT_AREA_X")==0 ){
                destiny->setNBottomRightAreaX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_FORMATION")==0 ){
                destiny->setXFkFormation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_TOP_LEFT_AREA_Z")==0 ){
                destiny->setNTopLeftAreaZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_ROLE")==0 ){
                destiny->setXFkRole_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_TOP_LEFT_AREA_X")==0 ){
                destiny->setNTopLeftAreaX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_OFFENSIVE_POS_X")==0 ){
                destiny->setNOffensivePosX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_OFFENSIVE_POS_Z")==0 ){
                destiny->setNOffensivePosZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_ATTRACTION_Z")==0 ){
                destiny->setNAttractionZ_str((vColumn[i]==NULL)?"":vColumn[i]);
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
            }else if( strcmp(sColumn[i], "N_BOTTOM_RIGHT_AREA_Z")==0 ){
                destiny->setNBottomRightAreaZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfStrategicPositionsDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfStrategicPositions*> *container = (std::vector<CPfStrategicPositions*> *)object;
        CPfStrategicPositions *destiny = new CPfStrategicPositions();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "N_ATTRACTION_X")==0 ){
                destiny->setNAttractionX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_LINEUP_ORDER")==0 ){
                destiny->setNLineupOrder_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_BOTTOM_RIGHT_AREA_X")==0 ){
                destiny->setNBottomRightAreaX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_FORMATION")==0 ){
                destiny->setXFkFormation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_TOP_LEFT_AREA_Z")==0 ){
                destiny->setNTopLeftAreaZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_ROLE")==0 ){
                destiny->setXFkRole_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_TOP_LEFT_AREA_X")==0 ){
                destiny->setNTopLeftAreaX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_OFFENSIVE_POS_X")==0 ){
                destiny->setNOffensivePosX_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_OFFENSIVE_POS_Z")==0 ){
                destiny->setNOffensivePosZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_ATTRACTION_Z")==0 ){
                destiny->setNAttractionZ_str((vColumn[i]==NULL)?"":vColumn[i]);
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
            }else if( strcmp(sColumn[i], "N_BOTTOM_RIGHT_AREA_Z")==0 ){
                destiny->setNBottomRightAreaZ_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

