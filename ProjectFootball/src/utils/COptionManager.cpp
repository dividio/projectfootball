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

#define CONFIG_FILE		"./data/ProjectFootball.ini"
#define	LINE_LENGTH		256


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>

#include "COptionManager.h"
#include "CLog.h"


char * trim( char *s )
{
    int  i;

    // First, from the beggining of the string iterate forward
    // to the first character that not validate isspace(). Copying
    // the rest of the string to the beggining.
    i = 0;
    while( isspace(s[i]) ){
      i++;
    }
    if( i!=0 ){
        strcpy(&(s[0]), &(s[i]) );
    }

    // Later, from the end of the string iterate backward to the first
    // character that not validate isspace(). Invalidating the rest of
    // the string
    i = strlen(s)-1;
    while( i>=0 && isspace(s[i]) ){
      i--;
    }
    s[i+1] = '\0';

    return s;
}


char * getSentence( char *sentence, const char *line )
{
    // First, copy the line to the sentence
    strcpy( sentence, line );
    // Later, detele comments from the sentence
    strtok( sentence, "#" );
    // trim the sentence
    trim( sentence );
    // Finally, if it's a comment line (start with '#'), then
    // return empty string
    if( sentence[0] == '#' ){
        sentence[0] = '\0';
    }

    return sentence;
}


void getAssignment( char *attribute, char *value, const char *sentence )
{
    // First, create temp buffer and copy sentence to it
    char *buffer = new char[strlen(sentence)+1];
    strcpy( buffer, sentence );

    // Copy the attribute
    strcpy( attribute, trim( strtok( buffer, "=" ) ) );
    // Copy the value
    strcpy( value, trim( strtok( NULL, "=" ) ) );

    // Free reserved buffer
    delete[] buffer;
}



COptionManager::COptionManager()
   : m_categoriesList()
{
    // Open the config file
    FILE *file = fopen( CONFIG_FILE, "r" );
    if( file==NULL ){
      CLog::getInstance()->error("Config file not found: %s", CONFIG_FILE);
        return;
    }

    char category[LINE_LENGTH];
    char option[LINE_LENGTH];
    char value[LINE_LENGTH];

    // Default category
    strcpy(category, "Others");

    char line[LINE_LENGTH];
    char sentence[LINE_LENGTH];

    while( fgets( line, LINE_LENGTH, file ) ){

        getSentence( sentence, line );

        // If it's not a empty sentence
        if( strlen(sentence) > 0 ){
          // If it's a category
            if( sentence[0] == '[' ){
              // Copy the sentence without the '[',']'
                sentence[strlen(sentence)-1] = '\0';
                if( strlen(sentence) > 0 ){
                    strcpy( category, &(sentence[1]) );
                }else{
                  CLog::getInstance()->warning("Malformed category label '%s' into config file '%s'", sentence, CONFIG_FILE);
                }
            }else{
              // else, then it's a assignment
              getAssignment(option, value, sentence);
              setStringOption(category, option, value);
           }
        }
    }

    // Close the config file
    fclose( file );

    CLog::getInstance()->info("Option manager initialized: <-- \"%s\"", CONFIG_FILE);
}


COptionManager::~COptionManager()
{
    // Para desincializar el gestor, se va recorriendo las distintas opciones
    // a traves de las distintas categorias escribiendolas en el fichero de
    // configuracion a la vez que se va liberando la memoria que se habia
    // reservado.

    // Open the config file
    FILE *file = fopen( CONFIG_FILE, "w" );
    if( file == NULL ){
      CLog::getInstance()->exception("Error at open the config file: %s", CONFIG_FILE);
    }

    fprintf( file, "# Autogenerated config file by ProjectFootball. Modify at your risk.\n\n\n" );


    std::map< const char *, std::map<const char *, const char *>* >::iterator itCategories;

    for( itCategories = m_categoriesList.begin(); itCategories != m_categoriesList.end(); itCategories++ ){

        const char *category = itCategories->first;
        std::map<const char *, const char *> *optionsList = itCategories->second;
        fprintf( file, "[%s]\n", category );

        std::map<const char *, const char *>::iterator itOptions;
        for( itOptions = optionsList->begin(); itOptions != optionsList->end(); itOptions++ ){

            const char *option = itOptions->first;
            const char *value  = itOptions->second;

            fprintf( file, "  %s = %s\n", option, value );

            // Free memory
            delete []option;
            delete []value;
        }

        fprintf( file, "\n" );

        // Free memory
        delete []category;
        optionsList->clear();
        delete optionsList;
    }

    m_categoriesList.clear();

    // Close config file
    fclose( file );

    CLog::getInstance()->info("Option manager deinitialized: --> \"%s\"", CONFIG_FILE);
}


COptionManager* COptionManager::getInstance()
{
  static COptionManager instance;
  return &instance;
}


const char * COptionManager::getStringOption( const char *category, const char *option, const char *defaultValue )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then create the category
        optionsList = createCategory( category );
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then create the option
        o = createOption( optionsList, option, defaultValue );
    }

    // Return the option value
    return optionsList->operator[](o);
}


int COptionManager::getIntOption( const char *category, const char *option, int defaultValue )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then create the category
        optionsList = createCategory( category );
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then create the option
        std::ostringstream stream;
        stream << defaultValue;
        o = createOption( optionsList, option, stream.str().c_str() );
    }

    // Return the option value
    return atoi(optionsList->operator[](o));
}


bool COptionManager::getBooleanOption( const char *category, const char *option, bool defaultValue )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then create the category
        optionsList = createCategory( category );
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then create the option
        if( defaultValue ){
            o = createOption( optionsList, option, "true" );
        }else{
            o = createOption( optionsList, option, "false" );
        }
    }

    // Return the option value
    return strcmp( optionsList->operator[](o), "true" ) == 0;
}


void COptionManager::setStringOption( const char *category, const char *option, const char *value )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then create the category
        optionsList = createCategory( category );
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then create the option
        createOption( optionsList, option, value );
    }else{
        // Else delete old value
        delete optionsList->operator[](o);
        // and set the new value
        char *v = new char[strlen(value)+1];
        strcpy( v, value );
        optionsList->operator[](o) = v;
    }
}


void COptionManager::setIntOption( const char *category, const char *option, int value )
{
    char buffer[50];
    sprintf( buffer, "%d", value );

    setStringOption( category, option, buffer );
}


void COptionManager::setBooleanOption( const char *category, const char *option, bool value )
{
    if( value ){
      setStringOption( category, option, "true" );
    }else{
      setStringOption( category, option, "false" );
    }
}


std::map<const char *, const char *> * COptionManager::searchCategory( const char *category )
{
    bool found = false;
    std::map< const char *, std::map<const char *, const char *>* >::iterator it;

    const char *c;

    for( it = m_categoriesList.begin(); it != m_categoriesList.end() && !found; it++ ){

        c = it->first;
        if( strcmp( c, category ) == 0 ){
            found = true;
        }
    }

    if( found ){
        return m_categoriesList[c];
    }else{
        return NULL;
    }
}


const char * COptionManager::searchOption( std::map<const char *, const char *> *map, const char *option )
{
    bool found = false;
    std::map<const char *, const char *>::iterator it;

    const char *o;

    for( it = map->begin(); it != map->end() && !found; it++ ){

        o = it->first;
        if( strcmp( o, option ) == 0 ){
            found = true;
        }
    }

    if( found ){
        return o;
    }else{
        return NULL;
    }
}


std::map<const char *, const char *> * COptionManager::createCategory( const char *category )
{
    // First, create the new options list
    std::map<const char *, const char *> *optionsList = new std::map<const char *, const char *>();
    // Copy the category name
    char *c = new char[strlen(category)+1];
    strcpy( c, category );
    // Associate the options list with the category inside of the categories list
    m_categoriesList[c] = optionsList;

    // Finally, return the options list of the category
    return optionsList;
}


const char * COptionManager::createOption( std::map<const char *, const char *> *map, const char *option, const char *value )
{
    // First, copu the option and the value
    char *o = new char[strlen(option)+1];
    char *v = new char[strlen(value)+1];

    strcpy( o, option );
    strcpy( v ,value );

    // Insert the option in the options list
    map->operator[](o) = v;

    // return the option create
    return o;
}
