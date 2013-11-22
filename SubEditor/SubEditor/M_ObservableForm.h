/*
        Copyright 2013 Luis Valero Martin

        This file is part of SubEditor.

        SubEditor is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        any later version.

        SubEditor is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with SubEditor.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "M_ObserverForm.h"
#include "M_SubData.h"

ref class M_ObservableForm
{
private: M_ObserverForm^ observer;
public:
	M_ObservableForm(void);
	virtual ~M_ObservableForm(void);
	
	void addObserver(M_ObserverForm^ observer);
	void notifySubData(M_SubData^ data);
	void notifyDataGrid();
	void notifyDataGrid(int row, M_SubData::nodeData^ data);
	void notifyNotEnoughRoomSub();
	void notifyNotErase();
	void notifySaveOK();
	void notifySaveError();
};

