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
#include "M_SubDataASS.h"


M_SubDataASS::M_SubDataASS(void)
{
	this->counter = 0;
	this->currentNode = nullptr;
	this->firstNode = nullptr;
	this->lastNode = nullptr;
	this->path = nullptr;
	this->name = "Untitled";
	this->encoding = TextFileEncoding::UTF8;
}


M_SubDataASS::~M_SubDataASS(void)
{
	clear();
}

bool M_SubDataASS::checkTimeString(String^ s){return false;}
bool M_SubDataASS::compareTime(String^ s1, String^ s2){return false;}
String^ M_SubDataASS::increaseTime(String^ s, String^ inc){return "";}
String^ M_SubDataASS::decraseTime(String^ s, String^ dec){return "";}
bool M_SubDataASS::inOrder(String^ start, String^ end){return false;}
bool M_SubDataASS::inOrderNotEqual(String^ start, String^ end){return false;}