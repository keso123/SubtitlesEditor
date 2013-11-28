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

#include "M_SubData.h"

interface class M_ObserverForm
{
public:
	//M_ObserverForm(void){}
	//virtual ~M_ObserverForm(void){}
	virtual void updateDataGrid()=0;
	virtual void updateSubData(M_SubData^ data)=0;
	virtual void updataDataGrid(int row, M_SubData::nodeData^ data)=0;
	virtual void errorNotEnoughRoomSub()=0;
	virtual void errorNotErase()=0;
	//between guis
	virtual void updateSubData(int shiftMode, int mode, int rowsAffected, int timesAffected, String^ time)=0;
	virtual void saveOK()=0;
	virtual void saveError()=0;
	virtual void openError()=0;
};

