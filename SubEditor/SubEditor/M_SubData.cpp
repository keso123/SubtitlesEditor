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
#include "M_SubData.h"

M_SubData::M_SubData(void){}
M_SubData::~M_SubData(void){}

int M_SubData::size(){
	return counter;
}
bool M_SubData::empty(){
	return counter == 0;
}
int M_SubData::getEncoding(){
	return encoding;
}
String^ M_SubData::getPath(){
	return path;
}
String^ M_SubData::getName(){
	return name;
}
void M_SubData::setEncoding(int enc){
	encoding = enc;
}
void M_SubData::setPath(String^ path){
	this->path = path;
}
void M_SubData::setName(String^ name){
	this->name = name;
}


void M_SubData::insert(M_SubData::nodeData^ data){
	moveEnd();
	if(currentNode != nullptr){
		node^ n = gcnew node;
		n->data = data;
		//firstNode->data->start = toMilliSeconds(data->sStart);
		//firstNode->data->end = toMilliSeconds(data->sEnd);
		currentNode->next = n;
		n->prev = currentNode;
		n->next = nullptr;
		if(currentNode == firstNode){
			currentNode = n;
			firstNode = n->prev;
		}
		currentNode = n;
		lastNode = currentNode;
		counter++;
	}else{
		firstNode = gcnew node;
		firstNode->data = data;
		//firstNode->data->start = toMilliSeconds(data->sStart);
		//firstNode->data->end = toMilliSeconds(data->sEnd);
		firstNode->next = nullptr;
		firstNode->prev = nullptr;
		currentNode = firstNode;
		lastNode = firstNode;
		counter++;
	}
}
void M_SubData::insertIn(int pos, M_SubData::nodeData^ data){
	if(currentNode != nullptr){
		node^ n = gcnew node;
		n->data = data;
		moveTo(pos);
		if(currentNode == firstNode){
			n->prev = nullptr;
			n->next = firstNode;
			currentNode = n;
			firstNode = n;
			increaseIndex();
		}else if(currentNode == lastNode){
			n->prev = currentNode->prev;
			n->next = currentNode;
			currentNode->prev->next = n;
			currentNode->prev = n;
			currentNode = n;
			lastNode->data->ind += 1;
		}else{
			n->prev = currentNode->prev;
			n->next = currentNode;
			currentNode->prev->next = n;
			currentNode->prev = n;
			currentNode = n;
			increaseIndex();
		}
		counter++;
	}else{
		firstNode = gcnew node;
		firstNode->data = data;
		firstNode->next = nullptr;
		firstNode->prev = nullptr;
		currentNode = firstNode;
		lastNode = firstNode;
		counter++;
	}
}

void M_SubData::erase(int pos){
	moveTo(pos);
	if(pos > 1){
		node^ prev = currentNode->prev;
		node^ next = currentNode->next;
		node^ aux = currentNode;
		prev->next = next;
		next->prev = prev;
		aux->next = nullptr;
		aux->prev = nullptr;
		currentNode = next;
		delete aux;
		aux = nullptr;
		counter--;
		decreseIndex();
	}else if(pos == 1 && counter > 1){
		node^ next = currentNode->next;
		node^ aux = currentNode;
		firstNode = next;
		currentNode = next;
		next->prev = nullptr;
		aux->next = nullptr;
		delete aux;
		aux = nullptr;
		counter--;
		decreseIndex();
	}else if(pos == counter){
	}
}

void M_SubData::edit(int pos){
}
void M_SubData::clear(){
	while(firstNode != nullptr && firstNode->next != nullptr){
		node^ n = firstNode;
		firstNode = n->next;
		firstNode->prev = nullptr;
		//n->next = nullptr;
		delete n->data;
		delete n;
		counter--;
	}
	if(firstNode != nullptr && firstNode->next == nullptr){
		delete firstNode;
		firstNode = nullptr;
		counter--;
	}
}

void M_SubData::increaseIndex(){
	node^ n = currentNode;
	while(n->next != nullptr){
		n->next->data->ind += 1;
		n = n->next;
	}
}
void M_SubData::decreseIndex(){
	node^ n = currentNode;
	currentNode->data->ind -= 1;
	while(n->next != nullptr){
		n->next->data->ind -= 1;
		n = n->next;
	}
}

void M_SubData::moveStart(){
	currentNode = firstNode;	
}
void M_SubData::moveEnd(){
	currentNode = lastNode;
}
void M_SubData:: movePrev(){
	if(currentNode == firstNode) return;
	node^ aux = currentNode;
	currentNode = aux->prev;
}
void M_SubData::moveNext(){
	if(currentNode == lastNode) return;
	node^ aux = currentNode;
	currentNode = aux->next;
}
void M_SubData::moveTo(int index){
	if(index > counter || index < 1) return;
	while(currentNode->data->ind < index) moveNext();
	while(currentNode->data->ind > index) movePrev();
}