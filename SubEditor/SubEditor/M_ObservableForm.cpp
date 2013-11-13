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
#include "M_ObservableForm.h"


M_ObservableForm::M_ObservableForm(void)
{
}

M_ObservableForm::~M_ObservableForm(void){
}

void M_ObservableForm::addObserver(M_ObserverForm^ observer){
	this->observer = observer;
}

void M_ObservableForm::notifySubData(M_SubDataClass^ data){
	observer->updateSubData(data);
}

void M_ObservableForm::notifyDataGrid(){
	observer->updateDataGrid();
}

void M_ObservableForm::notifyDataGrid(int row, M_SubDataClass::nodeData^ data){
	observer->updataDataGrid(row,data);
}

void M_ObservableForm::notifyNotEnoughRoomSub(){
	observer->errorNotEnoughRoomSub();
}

void M_ObservableForm::notifyNotErase(){
	observer->errorNotErase();
}