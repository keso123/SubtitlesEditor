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
#include "I_DAOFactory.h"


I_DAOFactory::I_DAOFactory(void)
{
}

I_DAOFactory::~I_DAOFactory(void){
}

I_DAOFactory^ I_DAOFactory::getDAOFactory(){
	if(instanceFlag == false){
		instanceFlag = true;
		instance = gcnew I_DAOFactory;
	}
	return instance;
}

I_DAOSub^ I_DAOFactory::getDAOSub(){
	return gcnew I_DAOSub;
}