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

#include "SharedTypes.h"

using namespace System;

ref class M_Properties
{
	// ////////////////////////////////////////////////////
	// Properties
	// ////////////////////////////////////////////////////
private: static String^ PROYECT_NAME = "proy.name";
private: String^ proyName;
		 //
		 // menu strip gui messages
		 //
private: static String^ MENU_STRIP_FILE_HEADER = "menu.strip.file.header";
private: String^ menuStripFileHeader;
private: static String^ MENU_STRIP_FILE_NEWSUB = "menu.strip.file.newsub";
private: String^ menuStripFileNewSub;
private: static String^ MENU_STRIP_FILE_OPENSUB = "menu.strip.file.opensub";
private: String^ menuStripFileOpenSub;
private: static String^ MENU_STRIP_FILE_SAVESUB = "menu.strip.file.savesub";
private: String^ menuStripFileSaveSub;
private: static String^ MENU_STRIP_FILE_SAVESUBAS = "menu.strip.file.savesubas";
private: String^ menuStripFileSaveSubAs;
private: static String^ MENU_STRIP_FILE_EXIT = "menu.strip.file.exit";
private: String^ menuStripFileExit;
	// ////////////////////////////////////////////////////
	// Methods
	// ////////////////////////////////////////////////////
private: static M_Properties^ instance;
private: static bool instanceFlag = false;
private: M_Properties(void);
public: static M_Properties^ getProperties();
public: static void resetProperties();
public: virtual ~M_Properties(void);

		PropertiesFileError loadProperties(String^ path);
		String^ getPropertie(Properties propertie);
		// saveProperties
		// changePropertie
};

