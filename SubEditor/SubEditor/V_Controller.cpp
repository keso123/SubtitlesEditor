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
#include "V_Controller.h"

//V_Controller^ V_Controller::instance = nullptr;
//bool V_Controller::instanceFlag = false;

V_Controller::V_Controller(void)
{
}

V_Controller::~V_Controller(){
}

V_Controller^ V_Controller::getController(){
	if(instanceFlag == false){
		instance = gcnew V_Controller;
		instanceFlag = true;
	}
	return instance;
}

/*void V_Controller::setObserver(SubEditor::V_MainForm^ form){
	this->form = form;
}*/

void V_Controller::newSubtitles(M_ObserverForm^ form){
	M_BFactory^ factory = M_BFactory::getBFactory();
	M_SubClass^ subClass = factory->getSubClass();
	subClass->addObserver(form);
	subClass->newSubtitles();
	delete subClass;
}

void V_Controller::openSubtitles(M_ObserverForm^ form, System::IO::StreamReader^ file){
	M_BFactory^ factory = M_BFactory::getBFactory();
	M_SubClass^ subClass = factory->getSubClass();
	subClass->addObserver(form);
	subClass->openSubtitles(file);
	delete subClass;
}

OpenFileError V_Controller::checkFile(M_ObserverForm^ form,String^ path, int& encoding){
	M_BFactory^ factory = M_BFactory::getBFactory();
	M_SubClass^ subClass = factory->getSubClass();
	subClass->addObserver(form);

	OpenFileError result = subClass->checkFile(path,encoding);
	delete subClass;
	return result;
}

void V_Controller::editSubtitles(M_ObserverForm^ form, M_SubDataClass^ data){
	M_BFactory^ factory = M_BFactory::getBFactory();
	M_SubClass^ subClass = factory->getSubClass();
	subClass->addObserver(form);
	subClass->editSubtitle(data);
	delete subClass;

}

void V_Controller::editSubtitlesText(M_ObserverForm^ form, M_SubDataClass^ data, int pos, String^ start, String^ end, String^ text){
	M_BFactory^ factory = M_BFactory::getBFactory();
	M_SubClass^ subClass = factory->getSubClass();
	subClass->addObserver(form);

	subClass->editSubtitleText(data,pos,start,end,text);

	delete subClass;
}

void V_Controller::insertSubtitles(M_ObserverForm^ form, M_SubDataClass^ data, int pos){
	M_BFactory^ factory = M_BFactory::getBFactory();
	M_SubClass^ subClass = factory->getSubClass();
	subClass->addObserver(form);

	subClass->insertSubtitles(data,pos);

	delete subClass;
}

void V_Controller::eraseSubtitles(M_ObserverForm^ form, M_SubDataClass^ data, int pos){
	M_BFactory^ factory = M_BFactory::getBFactory();
	M_SubClass^ subClass = factory->getSubClass();
	subClass->addObserver(form);

	subClass->eraseSubtitles(data,pos);

	delete subClass;
}