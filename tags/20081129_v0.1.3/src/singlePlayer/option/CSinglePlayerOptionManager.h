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

#ifndef CSINGLEPLAYEROPTIONMANAGER_H_
#define CSINGLEPLAYEROPTIONMANAGER_H_

#include <map>
#include "../db/dao/IPfGameOptionsDAO.h"

class CSinglePlayerOptionManager
{
public:
	/**
	 * Constructor/Destructor
	 */
	CSinglePlayerOptionManager(IPfGameOptionsDAO *gameOptionsDAO);
	~CSinglePlayerOptionManager();


    /**
     * Load the options from the config file
     */
    void loadOptions();


    /**
     * Save the options in the config file
     */
    void saveOptions();


private:
    /**
     *  Clean the options stored in the manager options and frees the memory
     */
    void cleanOptions();


    /**
     * Set the default values of options
     */
    void setDefaultValues();


    /**
     * This function return the string associate to an option of a category
     *
     * @param category Category of the searched option
     * @param option Option searched
     *
     * @return String asociate to the option if it's found, or the defaultValue else
     *
     * @throw If the option don't exists, then this function throw a exception
     */
    const char * getStringOption( const char *category, const char *option );


    /**
     * This function return the int value associate to an option of a category
     *
     * @param category Category of the searched option
     * @param option Option searched
     * @param defaultValue If the option is not found, then this value is returned by the function
     *
     * @return int value asociate to the option if it's found, or the defaultValue else
     *
     * @throw If the option don't exists, then this function throw a exception
     */
    int getIntOption( const char *category, const char *option );


    /**
     * This function return the boolean value associate to an option of a category
     *
     * @param category Category of the searched option
     * @param option Option searched
     * @param defaultValue If the option is not found, then this value is returned by the function
     *
     * @return boolean value asociate to the option if it's found, or the defaultValue else
     *
     * @throw If the option don't exists, then this function throw a exception
     */
    bool getBooleanOption( const char *category, const char *option );


    /**
     * This function set the value asociate to an option of a category.
     * If the option not exists, then it's created
     *
     * @param category Category of the searched option
     * @param option Option to set with the associate value
     * @param value String value of the option
     */
    void setStringOption( const char *category, const char *option, const char *value );


    /**
     * This function set the value asociate to an option of a category.
     * If the option not exists, then it's created
     *
     * @param category Category of the searched option
     * @param option Option to set with the associate value
     * @param value Int value of the option
     */
    void setIntOption( const char *category, const char *option, int value );


    /**
     * This function set the value asociate to an option of a category.
     * If the option not exists, then it's created
     *
     * @param category Category of the searched option
     * @param option Option to set with the associate value
     * @param value Boolean value of the option
     */
    void setBooleanOption( const char *category, const char *option, bool value );


    /**
     * This function return the date structure associate with the category indicated.
     *
     * @param category Category searched
     *
     * @return Return the pointer to the data structured searched or NULL else
     */
    std::map<const char *, const char *> * searchCategory( const char *category );


    /**
     * This function search the option inside of the data structure associate to
     * the category of the option.
     *
     * @param map Data structure associate to the category of the option
     * @param option Option searched
     *
     * @return Return the pointer to the option searched or NULL else
     */
    const char * searchOption( std::map<const char *, const char *> *map, const char *option );


    /**
     * This function create a category
     *
     * @param category Category to be created. This category must not exists or
     * the behaviour is undefined.
     *
     * @return Return the pointer to the data structure created
     */
    std::map<const char *, const char *> * createCategory( const char *category );


    /**
     * This function create a option inside of a category
     *
     * @param map Data structure associate with the category
     * @param option Option to be created. This option must not exists or
     * the behavior is undefined.
     * @param value Value to be associate with the option
     *
     * @return Return the pointer to the option created
     */
    const char * createOption( std::map<const char *, const char *> *map, const char *option, const char *value );


private:

    IPfGameOptionsDAO                                               *m_gameOptionsDAO;
    std::map< const char *, std::map<const char *, const char *>* > m_categoriesList;
};

#endif /*CSINGLEPLAYEROPTIONMANAGER_H_*/
