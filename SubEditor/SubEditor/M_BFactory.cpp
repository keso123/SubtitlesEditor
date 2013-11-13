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
#include "M_BFactory.h"


M_BFactory::M_BFactory(void)
{
}


M_BFactory::~M_BFactory(void)
{
}

M_BFactory^ M_BFactory::getBFactory(){
	if(instanceFlag == false){
		instanceFlag = true;
		instance = gcnew M_BFactory;
	}
	return instance;
}

M_SubClass^ M_BFactory::getSubClass(){
	return gcnew M_SubClass;
}
