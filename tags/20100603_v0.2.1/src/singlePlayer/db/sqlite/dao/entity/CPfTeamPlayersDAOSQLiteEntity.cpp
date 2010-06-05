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

#include "CPfTeamPlayersDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfTeamPlayersDAOSQLiteEntity::CPfTeamPlayersDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfTeamPlayersDAOSQLiteEntity::~CPfTeamPlayersDAOSQLiteEntity()
{
}

void CPfTeamPlayersDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfTeamPlayersDAOSQLiteEntity::deleteReg(CPfTeamPlayers *reg)
{
    std::string sql("DELETE FROM PF_TEAM_PLAYERS WHERE X_TEAM_PLAYER=");
    sql += "'"+reg->getXTeamPlayer_str()+"'";
    return exec(sql);
}

bool CPfTeamPlayersDAOSQLiteEntity::insertReg(CPfTeamPlayers *reg)
{
    std::string sql("INSERT INTO PF_TEAM_PLAYERS (N_WEIGHT,N_LINEUP_ORDER,N_SQUAD_NUMBER,N_HEIGHT,N_SPEED,N_KICK_POWER,S_SHORT_NAME,N_FORTITUDE,S_NAME,S_PHOTO,D_BIRTHDAY,X_FK_COUNTRY,N_MORAL) VALUES (");
    sql += (reg->getNWeight_str()=="")?"NULL":"'"+reg->getNWeight_str()+"'";
    sql += (reg->getNLineupOrder_str()=="")?",NULL":",'"+reg->getNLineupOrder_str()+"'";
    sql += (reg->getNSquadNumber_str()=="")?",NULL":",'"+reg->getNSquadNumber_str()+"'";
    sql += (reg->getNHeight_str()=="")?",NULL":",'"+reg->getNHeight_str()+"'";
    sql += (reg->getNSpeed_str()=="")?",NULL":",'"+reg->getNSpeed_str()+"'";
    sql += (reg->getNKickPower_str()=="")?",NULL":",'"+reg->getNKickPower_str()+"'";
    sql += (reg->getSShortName_str()=="")?",NULL":",'"+reg->getSShortName_str()+"'";
    sql += (reg->getNFortitude_str()=="")?",NULL":",'"+reg->getNFortitude_str()+"'";
    sql += (reg->getSName_str()=="")?",NULL":",'"+reg->getSName_str()+"'";
    sql += (reg->getSPhoto_str()=="")?",NULL":",'"+reg->getSPhoto_str()+"'";
    sql += (reg->getDBirthday_str()=="")?",NULL":",'"+reg->getDBirthday_str()+"'";
    sql += (reg->getXFkCountry_str()=="")?",NULL":",'"+reg->getXFkCountry_str()+"'";
    sql += (reg->getNMoral_str()=="")?",NULL":",'"+reg->getNMoral_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXTeamPlayer(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfTeamPlayersDAOSQLiteEntity::updateReg(CPfTeamPlayers *reg)
{
    std::string sql("UPDATE PF_TEAM_PLAYERS SET ");
    sql += (reg->getNWeight_str()=="")?" N_WEIGHT=NULL":" N_WEIGHT='"+reg->getNWeight_str()+"'";
    sql += (reg->getNLineupOrder_str()=="")?",N_LINEUP_ORDER=NULL":",N_LINEUP_ORDER='"+reg->getNLineupOrder_str()+"'";
    sql += (reg->getNSquadNumber_str()=="")?",N_SQUAD_NUMBER=NULL":",N_SQUAD_NUMBER='"+reg->getNSquadNumber_str()+"'";
    sql += (reg->getNHeight_str()=="")?",N_HEIGHT=NULL":",N_HEIGHT='"+reg->getNHeight_str()+"'";
    sql += (reg->getNSpeed_str()=="")?",N_SPEED=NULL":",N_SPEED='"+reg->getNSpeed_str()+"'";
    sql += (reg->getNKickPower_str()=="")?",N_KICK_POWER=NULL":",N_KICK_POWER='"+reg->getNKickPower_str()+"'";
    sql += (reg->getXTeamPlayer_str()=="")?",X_TEAM_PLAYER=NULL":",X_TEAM_PLAYER='"+reg->getXTeamPlayer_str()+"'";
    sql += (reg->getSShortName_str()=="")?",S_SHORT_NAME=NULL":",S_SHORT_NAME='"+reg->getSShortName_str()+"'";
    sql += (reg->getNFortitude_str()=="")?",N_FORTITUDE=NULL":",N_FORTITUDE='"+reg->getNFortitude_str()+"'";
    sql += (reg->getSName_str()=="")?",S_NAME=NULL":",S_NAME='"+reg->getSName_str()+"'";
    sql += (reg->getSPhoto_str()=="")?",S_PHOTO=NULL":",S_PHOTO='"+reg->getSPhoto_str()+"'";
    sql += (reg->getDBirthday_str()=="")?",D_BIRTHDAY=NULL":",D_BIRTHDAY='"+reg->getDBirthday_str()+"'";
    sql += (reg->getXFkCountry_str()=="")?",X_FK_COUNTRY=NULL":",X_FK_COUNTRY='"+reg->getXFkCountry_str()+"'";
    sql += (reg->getNMoral_str()=="")?",N_MORAL=NULL":",N_MORAL='"+reg->getNMoral_str()+"'";
    sql += " WHERE X_TEAM_PLAYER='"+reg->getXTeamPlayer_str()+"'";
    return exec(sql);
}

void CPfTeamPlayersDAOSQLiteEntity::freeVector(std::vector<CPfTeamPlayers*>* vector )
{
    std::vector<CPfTeamPlayers*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfTeamPlayers* CPfTeamPlayersDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfTeamPlayers *destiny = new CPfTeamPlayers();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfTeamPlayers*> * CPfTeamPlayersDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfTeamPlayers*> *container = new std::vector<CPfTeamPlayers*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfTeamPlayersDAOSQLiteEntity::exec(const std::string &sql)
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

int CPfTeamPlayersDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfTeamPlayers *destiny = (CPfTeamPlayers*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "N_WEIGHT")==0 ){
                destiny->setNWeight_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_LINEUP_ORDER")==0 ){
                destiny->setNLineupOrder_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_SQUAD_NUMBER")==0 ){
                destiny->setNSquadNumber_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_HEIGHT")==0 ){
                destiny->setNHeight_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_SPEED")==0 ){
                destiny->setNSpeed_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_KICK_POWER")==0 ){
                destiny->setNKickPower_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_TEAM_PLAYER")==0 ){
                destiny->setXTeamPlayer_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_SHORT_NAME")==0 ){
                destiny->setSShortName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_FORTITUDE")==0 ){
                destiny->setNFortitude_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_NAME")==0 ){
                destiny->setSName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_PHOTO")==0 ){
                destiny->setSPhoto_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "D_BIRTHDAY")==0 ){
                destiny->setDBirthday_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COUNTRY")==0 ){
                destiny->setXFkCountry_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_MORAL")==0 ){
                destiny->setNMoral_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfTeamPlayersDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfTeamPlayers*> *container = (std::vector<CPfTeamPlayers*> *)object;
        CPfTeamPlayers *destiny = new CPfTeamPlayers();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "N_WEIGHT")==0 ){
                destiny->setNWeight_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_LINEUP_ORDER")==0 ){
                destiny->setNLineupOrder_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_SQUAD_NUMBER")==0 ){
                destiny->setNSquadNumber_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_HEIGHT")==0 ){
                destiny->setNHeight_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_SPEED")==0 ){
                destiny->setNSpeed_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_KICK_POWER")==0 ){
                destiny->setNKickPower_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_TEAM_PLAYER")==0 ){
                destiny->setXTeamPlayer_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_SHORT_NAME")==0 ){
                destiny->setSShortName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_FORTITUDE")==0 ){
                destiny->setNFortitude_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_NAME")==0 ){
                destiny->setSName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_PHOTO")==0 ){
                destiny->setSPhoto_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "D_BIRTHDAY")==0 ){
                destiny->setDBirthday_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COUNTRY")==0 ){
                destiny->setXFkCountry_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_MORAL")==0 ){
                destiny->setNMoral_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

