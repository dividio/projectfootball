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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>

#include "optionsUtil.h"

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
