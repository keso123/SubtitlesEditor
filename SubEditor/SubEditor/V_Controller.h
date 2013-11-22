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

#include "M_BFactory.h"
#include "V_DebugForm.h"
//#include "V_MainForm.h"

//using namespace SubEditor;

ref class V_Controller
{
private: static V_Controller^ instance;
private: static bool instanceFlag = false;
//private: V_MainForm^ form;
private:
	V_Controller(void);

public: static V_Controller^ getController();
public: ~V_Controller();

		//void setObserver(SubEditor::V_MainForm^ form);
		void newSubtitles(M_ObserverForm^ form);
		void openSubtitles(M_ObserverForm^ form, System::IO::StreamReader^ file, int encoding, String^ path, String^ name);
		void saveSubtitles(M_ObserverForm^ form, System::IO::StreamWriter^ file,M_SubData^ data);
		OpenFileError checkFile(M_ObserverForm^ form, String^ path, int& encoding, String^& name);
		void editSubtitles(M_ObserverForm^ form, M_SubData^ data);
		void editSubtitlesText(M_ObserverForm^ form, M_SubData^ data, int pos, String^ start, String^ end, String^ text);
		void insertSubtitles(M_ObserverForm^ form, M_SubData^ data, int pos);
		void eraseSubtitles(M_ObserverForm^ form, M_SubData^ data, int pos);
		void shiftTime(M_ObserverForm^ form, M_SubData^ data, int shiftMode, int mode, int rowsAffected, int timesAffected, String^ time, int selectedRow);
};

