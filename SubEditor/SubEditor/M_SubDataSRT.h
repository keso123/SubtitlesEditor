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

ref class M_SubDataSRT : public M_SubData
{
/*public: ref struct nodeData{
			 int ind;
			 int start;
			 int end;
			 String^ sStart;
			 String^ sEnd;
			 String^ text;
		 };*/
private: ref struct node{
			M_SubData::nodeData^ data;
			node^ next;
			node^ prev;
		 };
private:
	int counter;
	node^ currentNode;
	node^ firstNode;
	node^ lastNode;
	String^ path;
	int encoding;
	String^ name;

public:
	M_SubDataSRT(void);
	virtual ~M_SubDataSRT(void);

	//virtual int size()override;
	
	
	

	virtual bool checkTimeString(String^ s)override;//OK
	virtual bool compareTime(String^ s1, String^ s2)override;//OK
	virtual String^ increaseTime(String^ s, String^ inc)override;//OK
	virtual String^ decraseTime(String^ s, String^ dec)override;//OK
	virtual String^ getInterval(String^ start, String^ end){return "";}//NOT USED
	virtual bool inOrder(String^ start, String^ end)override;//OK
	virtual bool inOrderNotEqual(String^ start, String^ end)override;//OK

	int toMilliSeconds(String^ time){return 0;}//NOT USED
	String^ toTimeString(int milliSeconds){return "";}//NOT USED
};

