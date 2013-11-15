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
#ifndef SHAREDTYPES_H_
#define SHAREDTYPES_H_

#define DEBUG 1

enum SubtitlesType {
	SRT = 0,
	ASS = 1
};
enum PropertiesFileError {
	propertiesOK = 0,
	propertiesFileNotFound = 1
};
enum OpenFileError {
	OpenFileErrorOK = 0,
	fileNotFoundError = 1,
	fileExtensionError = 2,
	permissionsError = 3,
	invalidPathError = 4,
	accessDeniedError = 5
};
enum TextFileEncoding {
	UTF8 = 0,
	UTF16B = 1,//unicodeBigEndian
	UTF16L = 2,//unicode
	UTF32B = 3,
	UTF32L = 4,
	UTF7 = 5,
	UTF1 = 6,
	UTFeBCDIC = 7,
	SCSU = 8,
	BOCU1 = 9,
	GB18030 = 10,
	NoBOMencoding = 11
};
enum ShiftTimes {
	timeMode = 0,
	frameMode = 1,
	forward = 2,
	backward = 3,
	allrows = 4,
	selectionF = 5,
	selectionB = 6,
	timeStartEnd = 7,
	timeStart = 8,
	timeEnd = 9
};
enum Properties {
	E_PROYECT_NAME = 0,
	E_MENU_STRIP_FILE_HEADER = 1,
	E_MENU_STRIP_FILE_NEWSUB = 2,
	E_MENU_STRIP_FILE_OPENSUB = 3,
	E_MENU_STRIP_FILE_SAVESUB = 4,
	E_MENU_STRIP_FILE_SAVESUBAS = 5,
	E_MENU_STRIP_FILE_EXIT = 6
};

#endif
