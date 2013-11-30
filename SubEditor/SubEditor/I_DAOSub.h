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

#include <stdlib.h>
#include <string.h>

//#include "M_SubDataClass.h"
#include "M_SubData.h"
#include "SharedTypes.h"

ref class I_DAOSub
{
private:
	bool parseInd(String^ line, M_SubData::nodeData^ data);
	bool parseStartEnd(String^ line, M_SubData::nodeData^ data);
	bool parseText(System::IO::StreamReader^ file, M_SubData::nodeData^ data);

	bool parseScriptInfo(System::IO::StreamReader^ file, M_SubData^ sub);
	bool parseStyles(System::IO::StreamReader^ file, M_SubData^ sub);
	bool parseEvents(System::IO::StreamReader^ file, M_SubData^ sub);

public:
	I_DAOSub(void);
	virtual ~I_DAOSub(void);

	bool loadSubtitles(System::IO::StreamReader^ file, M_SubData^ sub);
	bool saveSubtitles(System::IO::StreamWriter^ file, M_SubData^ sub);
	OpenFileError checkFile(String^ path, int& encoding, String^& name, int& type);

	bool loadASS(System::IO::StreamReader^ file, M_SubData^ sub);
};

