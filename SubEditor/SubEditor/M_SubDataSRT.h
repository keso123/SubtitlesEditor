#pragma once

using namespace System;

ref class M_SubDataSRT
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
	String^ name;

public:
	M_SubDataSRT(void);
	virtual ~M_SubDataSRT(void);

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

	virtual bool checkTimeString(String^ s)=0;//OK
	virtual bool compareTime(String^ s1, String^ s2)=0;//OK
	virtual String^ increaseTime(String^ s, String^ inc)=0;//OK
	virtual String^ decraseTime(String^ s, String^ dec)=0;//OK
	String^ getInterval(String^ start, String^ end){return "";}//NOT USED
	virtual bool inOrder(String^ start, String^ end)=0;//OK
	virtual bool inOrderNotEqual(String^ start, String^ end)=0;//OK

private:
	virtual void clear()=0;//OK
	virtual void increaseIndex()=0;//NOT TESTED
	virtual void decreseIndex()=0;
	int toMilliSeconds(String^ time){return 0;}//NOT USED
	String^ toTimeString(int milliSeconds){return "";}//NOT USED
};

