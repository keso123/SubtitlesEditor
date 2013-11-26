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

#include "M_SubData.h"

using namespace System;

ref class M_SubDataASS : public M_SubData
{
public:
	M_SubDataASS(void);
	virtual ~M_SubDataASS(void);

	virtual bool checkTimeString(String^ s)override;//OK
	virtual bool compareTime(String^ s1, String^ s2)override;//OK
	virtual String^ increaseTime(String^ s, String^ inc)override;//OK
	virtual String^ decraseTime(String^ s, String^ dec)override;//OK
	virtual bool inOrder(String^ start, String^ end)override;//OK
	virtual bool inOrderNotEqual(String^ start, String^ end)override;
};

