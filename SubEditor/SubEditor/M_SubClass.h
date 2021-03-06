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

#include "M_ObservableForm.h"
//#include "M_SubDataClass.h"
#include "M_SubData.h"
#include "M_SubDataSRT.h"
#include "M_SubDataASS.h"
#include "I_DAOFactory.h"
#include "V_DebugForm.h"

using namespace System;

ref class M_SubClass : public M_ObservableForm
{
//private: M_SubDataClass subtitles;

public:
	M_SubClass(void);
	virtual ~M_SubClass();

	void newSubtitles();
	void openSubtitles(System::IO::StreamReader^ file, int encoding, String^ path, String^ name, int type);
	void saveSubtitles(System::IO::StreamWriter^ file,M_SubData^ data);
	void editSubtitle(M_SubData^ data);
	void editSubtitleText(M_SubData^ data, int pos, String^ start, String^ end, String^ text);
	void insertSubtitles(M_SubData^ data, int pos);
	void eraseSubtitles(M_SubData^ data, int pos);

	void shiftForwardAll(M_SubData^ data, int timesAffected, String^ time);
	void shiftForwardForward(M_SubData^ data, int timesAffected, int pos, String^ time);
	void shiftForwardBackward(M_SubData^ data, int timesAffected, int pos, String^ time);
	void shiftBackwardAll(M_SubData^ data, int timesAffected, String^ time);
	void shiftBackwardForward(M_SubData^ data, int timesAffected, int pos, String^ time);
	void shiftBackwardBackward(M_SubData^ data, int timesAffected, int pos, String^ time);

	OpenFileError checkFile(String^ path, int& encoding, String^& name, int& type);
};

