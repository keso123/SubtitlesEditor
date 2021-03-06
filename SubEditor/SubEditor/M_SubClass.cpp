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
#include "M_SubClass.h"


M_SubClass::M_SubClass(void)
{
}

M_SubClass::~M_SubClass(){
}

void M_SubClass::newSubtitles(){
	M_SubData^ sub = gcnew M_SubDataSRT();
	M_SubData::nodeData^ data = gcnew M_SubData::nodeData;
	data->ind = 1;
	data->start = 0;
	data->end = 5000;
	data->sStart = "00:00:00,000";
	data->sEnd = "00:00:05,000";
	data->text = "";
	sub->insert(data);
	notifySubData(sub);
	notifyDataGrid();
}

void M_SubClass::openSubtitles(System::IO::StreamReader^ file, int encoding, String^ path, String^ name, int type){
	if(type == SubtitlesType::SRT){
		M_SubData^ sub = gcnew M_SubDataSRT();

		I_DAOFactory^ fac = I_DAOFactory::getDAOFactory();
		I_DAOSub^ dao = fac->getDAOSub();

		if(dao->loadSubtitles(file,sub)){
			delete dao;
			M_SubData::nodeData^ last = sub->getLast();
			M_SubData::nodeData^ node = gcnew M_SubData::nodeData;
			node->ind = last->ind + 1;
			node->sStart = last->sEnd;//sub->increaseTime(last->sEnd, "00:00:00,001");
			node->sEnd = sub->increaseTime(node->sStart, "00:00:01,000");
			node->text = "";
			sub->insert(node);
			sub->setEncoding(encoding);
			sub->setPath(path);
			sub->setName(name);
			notifySubData(sub);
			notifyDataGrid();
		}else{
			delete dao;
			notifyOpenError();
		}
	}else if(type == SubtitlesType::ASS){
		M_SubData^ sub = gcnew M_SubDataASS();

		I_DAOFactory^ fac = I_DAOFactory::getDAOFactory();
		I_DAOSub^ dao = fac->getDAOSub();
		if(dao->loadASS(file,sub)){
			delete dao;
			notifySubData(sub);
			notifyDataGrid();
		}else{
			delete dao;
		}
	}
}
void M_SubClass::saveSubtitles(System::IO::StreamWriter^ file,M_SubData^ data){
	M_SubData^ sub = gcnew M_SubDataSRT();

	I_DAOFactory^ fac = I_DAOFactory::getDAOFactory();
	I_DAOSub^ dao = fac->getDAOSub();
	if(dao->saveSubtitles(file,data)){
		notifySaveOK();
	}else{
		notifySaveError();
	}
	delete dao;
}

void M_SubClass::editSubtitle(M_SubData^ data){
	//data->edit

}

void M_SubClass::editSubtitleText(M_SubData^ data, int pos, String^ start, String^ end, String^ text){
	data->moveTo(pos - 1);
	M_SubData::nodeData^ prev = data->getCurrent();
	data->moveTo(pos + 1);
	M_SubData::nodeData^ next = data->getCurrent();
	M_SubData::nodeData^ d = data->get(pos);
	if(DEBUG){
		SubEditor::V_DebugForm^ debug = SubEditor::V_DebugForm::getDebugger();
		debug->Show();
		debug->insertLine("M_SubClass::editSubtitles");
		debug->insertLine("Indice del nodo prev: "+prev->ind.ToString());
		debug->insertLine("Indice del nodo next: "+next->ind.ToString());
		debug->insertLine("Indice del nodo actual: "+d->ind.ToString());
		debug->insertLine("Tiempo del nodo prev: "+prev->sEnd);
		debug->insertLine("Tiempo del nodo next: "+next->sStart);
		debug->insertLine("Tiempo del nodo actual: "+start+" , "+end);
	}
	if(pos == data->size() && pos != 1 && !data->inOrder(prev->sEnd,start)){
		notifyNotEnoughRoomSub();
		return;
	}
	if(pos == 1 && pos != data->size() && !data->inOrder(end,next->sStart)){
		notifyNotEnoughRoomSub();
		return;
	}
	if(pos > 1 && pos < data->size() && (!data->inOrder(prev->sEnd,start) || !data->inOrder(end,next->sStart))){
		notifyNotEnoughRoomSub();
		return;
	}
	if(!data->inOrderNotEqual(start,end)){//(data->compareTime(data->decraseTime(start,end),"00:00:00,000")){
		if(DEBUG){
			SubEditor::V_DebugForm^ debug = SubEditor::V_DebugForm::getDebugger();
			debug->Show();
			debug->insertLine("M_SubClass::editSubtitles");
			debug->insertLine("Start y End no estan en orden");
		}
		return;
	}
	d->sStart = start;
	d->sEnd = end;
	d->text = text;
	if(pos == data->size()){
		M_SubData::nodeData^ last = data->getLast();
		M_SubData::nodeData^ node = gcnew M_SubData::nodeData;
		node->ind = last->ind + 1;
		node->sStart = last->sEnd;//data->increaseTime(last->sEnd, "00:00:00,001");
		node->sEnd = data->increaseTime(node->sStart, "00:00:01,000");
		node->text = "";
		data->insert(node);
		notifyDataGrid();
	}else{
		notifyDataGrid(pos-1,d);
	}
}
void M_SubClass::insertSubtitles(M_SubData^ data, int pos){
	data->moveTo(pos - 1);
	M_SubData::nodeData^ prev = data->getCurrent();
	data->moveTo(pos);
	M_SubData::nodeData^ next = data->getCurrent();
	if(DEBUG){
		SubEditor::V_DebugForm^ debug = SubEditor::V_DebugForm::getDebugger();
		debug->Show();
		debug->insertLine("M_SubClass::insertSubtitles");
		debug->insertLine("Indice del nodo prev: "+prev->ind.ToString());
		debug->insertLine("Indice del nodo next: "+next->ind.ToString());
	}
	if(!data->inOrderNotEqual(prev->sEnd,next->sStart)){
		notifyNotEnoughRoomSub();
	}else{
		M_SubData::nodeData^ node = gcnew M_SubData::nodeData;
		node->sStart = prev->sEnd;
		node->sEnd = next->sStart;
		node->text = "";
		node->ind = pos;
		data->insertIn(pos,node);
		notifyDataGrid();
	}
}
void M_SubClass::eraseSubtitles(M_SubData^ data, int pos){
	if(pos == data->size()){
		if(DEBUG){
			SubEditor::V_DebugForm^ debug = SubEditor::V_DebugForm::getDebugger();
			debug->Show();
			debug->insertLine("M_SubClass::eraseSubtitles");
			debug->insertLine("El ultimo subtilo no se puede borrar");
		}
		notifyNotErase();
		return;
	}
	data->erase(pos);
	notifyDataGrid();
}

void M_SubClass::shiftForwardAll(M_SubData^ data, int timesAffected, String^ time){
	M_SubData::nodeData^ node;
	data->moveEnd();
	int i = data->size();
	while(i > 0){
		node = data->getCurrent();
		switch(timesAffected){
		case ShiftTimes::timeStartEnd: 
			node->sStart = data->increaseTime(node->sStart,time);
			node->sEnd = data->increaseTime(node->sEnd,time);
			break;
		case ShiftTimes::timeStart: 
			node->sStart = data->increaseTime(node->sStart,time);
			break;
		case ShiftTimes::timeEnd: 
			node->sEnd = data->increaseTime(node->sEnd,time);
			break;
		}
		data->movePrev();
		i--;
	}
	notifyDataGrid();
}
void M_SubClass::shiftForwardForward(M_SubData^ data, int timesAffected, int pos, String^ time){
	data->moveEnd();
	M_SubData::nodeData^ node;
	int i = data->size();
	while(i >= pos){
		node = data->getCurrent();
		switch(timesAffected){
		case ShiftTimes::timeStartEnd: 
			node->sStart = data->increaseTime(node->sStart,time);
			node->sEnd = data->increaseTime(node->sEnd,time);
			break;
		case ShiftTimes::timeStart: 
			node->sStart = data->increaseTime(node->sStart,time);
			break;
		case ShiftTimes::timeEnd: 
			node->sEnd = data->increaseTime(node->sEnd,time);
			break;
		}
		data->movePrev();
		i--;
	}
	notifyDataGrid();
}
void M_SubClass::shiftForwardBackward(M_SubData^ data, int timesAffected, int pos, String^ time){
	data->moveTo(pos);
	M_SubData::nodeData^ node;
	int i = pos;
	while(i > 0){
		node = data->getCurrent();
		switch(timesAffected){
		case ShiftTimes::timeStartEnd: 
			node->sStart = data->increaseTime(node->sStart,time);
			node->sEnd = data->increaseTime(node->sEnd,time);
			break;
		case ShiftTimes::timeStart: 
			node->sStart = data->increaseTime(node->sStart,time);
			break;
		case ShiftTimes::timeEnd: 
			node->sEnd = data->increaseTime(node->sEnd,time);
			break;
		}
		data->movePrev();
		i--;
	}
	notifyDataGrid();
}
void M_SubClass::shiftBackwardAll(M_SubData^ data, int timesAffected, String^ time){
	data->moveStart();
	M_SubData::nodeData^ node;
	int i = 1;
	while(i <= data->size()){
		node = data->getCurrent();
		switch(timesAffected){
		case ShiftTimes::timeStartEnd: 
			node->sStart = data->decraseTime(node->sStart,time);
			node->sEnd = data->decraseTime(node->sEnd,time);
			break;
		case ShiftTimes::timeStart: 
			node->sStart = data->decraseTime(node->sStart,time);
			break;
		case ShiftTimes::timeEnd: 
			node->sEnd = data->decraseTime(node->sEnd,time);
			break;
		}
		data->moveNext();
		i++;
	}
	notifyDataGrid();
}
void M_SubClass::shiftBackwardForward(M_SubData^ data, int timesAffected, int pos, String^ time){
	data->moveTo(pos);
	M_SubData::nodeData^ node;
	int i = pos;
	while(i <= data->size()){
		node = data->getCurrent();
		switch(timesAffected){
		case ShiftTimes::timeStartEnd: 
			node->sStart = data->decraseTime(node->sStart,time);
			node->sEnd = data->decraseTime(node->sEnd,time);
			break;
		case ShiftTimes::timeStart: 
			node->sStart = data->decraseTime(node->sStart,time);
			break;
		case ShiftTimes::timeEnd: 
			node->sEnd = data->decraseTime(node->sEnd,time);
			break;
		}
		data->moveNext();
		i++;
	}
	notifyDataGrid();
}
void M_SubClass::shiftBackwardBackward(M_SubData^ data, int timesAffected, int pos, String^ time){
	data->moveTo(pos);
	M_SubData::nodeData^ node;
	int i = pos;
	while(i > 0){
		node = data->getCurrent();
		switch(timesAffected){
		case ShiftTimes::timeStartEnd: 
			node->sStart = data->decraseTime(node->sStart,time);
			node->sEnd = data->decraseTime(node->sEnd,time);
			break;
		case ShiftTimes::timeStart: 
			node->sStart = data->decraseTime(node->sStart,time);
			break;
		case ShiftTimes::timeEnd: 
			node->sEnd = data->decraseTime(node->sEnd,time);
			break;
		}
		data->movePrev();
		i--;
	}
	notifyDataGrid();
}

OpenFileError M_SubClass::checkFile(String^ path, int& encoding, String^& name, int& type){
	I_DAOFactory^ fac = I_DAOFactory::getDAOFactory();
	I_DAOSub^ dao = fac->getDAOSub();
	
	OpenFileError result = dao->checkFile(path,encoding,name,type);
	delete dao;
	return result;
}