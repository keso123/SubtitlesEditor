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
#include "M_Properties.h"


M_Properties::M_Properties(void)
{
	proyName = "SubEditor";
	//menu strip gui messages
	menuStripFileHeader = "File";
	menuStripFileNewSub = "New Subtitles";
	menuStripFileOpenSub = "Open Subtitles...";
	menuStripFileSaveSub = "Save Subtitles";
	menuStripFileSaveSubAs = "Save Subtitles as...";
	menuStripFileExit = "Exit";
}


M_Properties::~M_Properties(void)
{
}

PropertiesFileError M_Properties::loadProperties(String^ path){
	return PropertiesFileError::propertiesOK;
}
String^ M_Properties::getPropertie(Properties propertie){
	switch (propertie)
	{
	case E_PROYECT_NAME: return proyName;
	case E_MENU_STRIP_FILE_HEADER: return menuStripFileHeader;
	case E_MENU_STRIP_FILE_NEWSUB: return menuStripFileNewSub;
	case E_MENU_STRIP_FILE_OPENSUB: return menuStripFileOpenSub;
	case E_MENU_STRIP_FILE_SAVESUB: return menuStripFileSaveSub;
	case E_MENU_STRIP_FILE_SAVESUBAS: return menuStripFileSaveSubAs;
	case E_MENU_STRIP_FILE_EXIT: return menuStripFileExit;
	default:
		break;
	}
	return "";
}

M_Properties^ M_Properties::getProperties(){
	if(instanceFlag == false){
		instance = gcnew M_Properties;
		instanceFlag = true;
	}
	return instance;
}

void M_Properties::resetProperties(){
	delete instance;
	instanceFlag = false;
}
