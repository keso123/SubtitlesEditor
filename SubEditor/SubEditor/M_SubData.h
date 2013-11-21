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

interface class M_SubData
{
public: ref struct nodeData{
			 int ind;
			 int start;
			 int end;
			 String^ sStart;
			 String^ sEnd;
			 String^ text;
		 };

public:
	//M_SubData(void);
	//virtual ~M_SubData(void);
	virtual int size()=0;
	virtual bool empty()=0;
	virtual int getEncoding()=0;
	virtual String^ getPath()=0;
	virtual String^ getName()=0;
	virtual void setEncoding(int enc)=0;
	virtual void setPath(String^ path)=0;
	virtual void setName(String^ name)=0;
	virtual void insert(nodeData^ data)=0;//OK
	virtual void insertIn(int pos, nodeData^ data)=0;//OK
	virtual void erase(int pos)=0;//NOT FINISHED
	virtual void edit(int pos)=0;//NOT FINISHED
	
	virtual void moveStart()=0;//OK
	virtual void moveEnd()=0;//OK
	virtual void movePrev()=0;//OK
	virtual void moveNext()=0;//OK
	virtual void moveTo(int index)=0;//OK
	/*nodeData^ getCurrentData(){
		return currentNode->data;
	}

	nodeData^ getFirst(){
		return firstNode->data;
	}
	nodeData^ getCurrent(){
		return currentNode->data;
	}
	nodeData^ getLast(){
		return lastNode->data;
	}
	nodeData^ get(int pos){
		moveTo(pos);
		return currentNode->data;
	}*/

	virtual bool checkTimeString(String^ s)=0;//OK
	virtual bool compareTime(String^ s1, String^ s2)=0;//OK
	virtual String^ increaseTime(String^ s, String^ inc)=0;//OK
	virtual String^ decraseTime(String^ s, String^ dec)=0;//OK
	virtual bool inOrder(String^ start, String^ end)=0;//OK
	virtual bool inOrderNotEqual(String^ start, String^ end)=0;//OK

//private:
	virtual void clear()=0;//OK
	virtual void increaseIndex()=0;//NOT TESTED
	virtual void decreseIndex()=0;
};

