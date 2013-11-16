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

using namespace System;

ref class M_SubDataClass
{
public: ref struct nodeData{
			 int ind;
			 int start;
			 int end;
			 String^ sStart;
			 String^ sEnd;
			 String^ text;
		 };
private: ref struct node{
			nodeData^ data;
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

public:
	M_SubDataClass(void);
	~M_SubDataClass();

	int size();
	bool empty();
	int getEncoding();
	String^ getPath();
	void insert(nodeData^ data);//OK
	void insertIn(int pos, nodeData^ data);//OK
	void erase(int pos);//NOT FINISHED
	void edit(int pos);//NOT FINISHED
	
	void moveStart();//OK
	void moveEnd();//OK
	void movePrev();//OK
	void moveNext();//OK
	void moveTo(int index);//OK
	nodeData^ getCurrentData(){
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
	}

	bool checkTimeString(String^ s);//OK
	bool compareTime(String^ s1, String^ s2);//OK
	String^ increaseTime(String^ s, String^ inc);//OK
	String^ decraseTime(String^ s, String^ dec);//OK
	String^ getInterval(String^ start, String^ end){return "";}//NOT USED
	bool inOrder(String^ start, String^ end);//OK
	bool inOrderNotEqual(String^ start, String^ end);//OK

private:
	void clear();//OK
	void increaseIndex();//NOT TESTED
	void decreseIndex();
	int toMilliSeconds(String^ time){return 0;}//NOT USED
	String^ toTimeString(int milliSeconds){return "";}//NOT USED
};

