/*
 * Copyright (C) 2012 - Ikaro Games   www.ikarogames.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *
 */

#ifndef CEDITORUTILS_H
#define CEDITORUTILS_H

#include "../singlePlayer/db/sqlite/dao/factory/CDAOFactorySQLite.h"
#include <boost/lambda/lambda.hpp>
#include <CEGUI/CEGUI.h>

struct for_each_if_data {
	CEGUI::PushButton *button;
	CEGUI::Listbox *list;
};

class CEditorUtils {
	public:
		CEditorUtils();
		~CEditorUtils();
		template <typename Iterator, typename Callback>
		void for_each(struct for_each_if_data *data, Iterator begin, Iterator end,
					  Callback callback)
		{
			data->list->resetList();
			std::string label;
			unsigned int id;
			for (Iterator it = begin; it != end; it++) {
				label.clear();
 				callback(it, &label, &id);
				data->list->addItem(new CEGUI::ListboxTextItem((CEGUI::utf8 *)label.c_str(), id));
			}
			if (end != begin)
				data->button->setEnabled(true);
		};
		void setDaoFactory(CDAOFactorySQLite *daoFactory);

	private:
		CDAOFactorySQLite *m_daoFactory;
};

#endif // CEDITORUTILS_H
