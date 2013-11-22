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
#include "M_SubDataSRT.h"


M_SubDataSRT::M_SubDataSRT(void)
{
	this->counter = 0;
	this->currentNode = nullptr;
	this->firstNode = nullptr;
	this->lastNode = nullptr;
	this->path = nullptr;
	this->name = "Untitled";
	this->encoding = TextFileEncoding::UTF8;
}


M_SubDataSRT::~M_SubDataSRT(void)
{
	clear();
}


bool M_SubDataSRT::checkTimeString(String^ s){
	try{
		int ind1 = s->IndexOf(",");
		int ind2 = s->LastIndexOf(":");
		int ind3 = s->IndexOf(":");
		if(ind1 == -1 || ind2 == -1 || ind3 == -1) return false;
		Convert::ToInt16(s->Substring(ind1+1));
		Convert::ToInt16(s->Substring(ind2+1,2));
		Convert::ToInt16(s->Substring(ind3+1,2));
		Convert::ToInt16(s->Substring(0,2));
		return true;
	}catch(System::FormatException^ e){
		return false;
	}catch(System::OverflowException^ e){
		return false;
	}
}

bool M_SubDataSRT::compareTime(String^ s1, String^ s2){
	return checkTimeString(s1) && checkTimeString(s2) && String::Compare(s1,s2) == 0;
}
String^ M_SubDataSRT::increaseTime(String^ s, String^ inc){
	if(checkTimeString(s) && checkTimeString(inc)){
		int ind1 = s->IndexOf(",");
		int ind2 = s->LastIndexOf(":");
		int ind3 = s->IndexOf(":");

		int milliseconds = Convert::ToInt16(s->Substring(ind1+1));
		int seconds = Convert::ToInt16(s->Substring(ind2+1,2));
		int minutes = Convert::ToInt16(s->Substring(ind3+1,2));
		int hours = Convert::ToInt16(s->Substring(0,2));

		int ms = Convert::ToInt16(inc->Substring(ind1+1));
		int s = Convert::ToInt16(inc->Substring(ind2+1,2));
		int m = Convert::ToInt16(inc->Substring(ind3+1,2));
		int h = Convert::ToInt16(inc->Substring(0,2));

		milliseconds += ms;
		seconds += s;
		minutes += m;
		hours += h;
		if(milliseconds > 999){
			int aux = milliseconds;
			aux = milliseconds % 1000;
			milliseconds -= aux;
			seconds += milliseconds / 1000;
			milliseconds = aux;
		}
		if(seconds > 59){
			int aux = seconds;
			aux = seconds % 60;
			seconds -= aux;
			minutes += seconds / 60;
			seconds = aux;
		}
		if(minutes > 59){
			int aux = minutes;
			aux = minutes % 60;
			minutes -= aux;
			hours += minutes / 60;
			minutes = aux;
		}
		if(hours > 99){
			return nullptr;
		}

		String^ sHours,^ sMinutes,^ sSeconds,^ sMilliseconds;
		if(milliseconds < 10)
			sMilliseconds = "00"+milliseconds.ToString();
		else if(milliseconds < 100)
			sMilliseconds = "0"+milliseconds.ToString();
		else
			sMilliseconds = milliseconds.ToString();

		if(seconds < 10)
			sSeconds = "0"+seconds.ToString();
		else
			sSeconds = seconds.ToString();

		if(minutes < 10)
			sMinutes = "0"+minutes.ToString();
		else 
			sMinutes = minutes.ToString();

		if(hours < 10)
			sHours = "0"+hours.ToString();
		else
			sHours = hours.ToString();

		return sHours+":"+sMinutes+":"+sSeconds+","+sMilliseconds;

	}else{
		return nullptr;
	}
}
String^ M_SubDataSRT::decraseTime(String^ s, String^ dec){
	if(inOrder(dec,s)){
		int ind1 = s->IndexOf(",");
		int ind2 = s->LastIndexOf(":");
		int ind3 = s->IndexOf(":");

		int milliseconds = Convert::ToInt16(s->Substring(ind1+1));
		int seconds = Convert::ToInt16(s->Substring(ind2+1,2));
		int minutes = Convert::ToInt16(s->Substring(ind3+1,2));
		int hours = Convert::ToInt16(s->Substring(0,2));

		int ms = Convert::ToInt16(dec->Substring(ind1+1));
		int s = Convert::ToInt16(dec->Substring(ind2+1,2));
		int m = Convert::ToInt16(dec->Substring(ind3+1,2));
		int h = Convert::ToInt16(dec->Substring(0,2));

		//milliseconds -= ms;
		//seconds -= s;
		//minutes -= m;
		if(milliseconds >= ms){
			milliseconds -= ms;
		}else{
			milliseconds += (1000 - ms);
			seconds--;
		}
		if(seconds >= s){
			seconds -= s;
		}else{
			seconds += (60 - s);
			minutes--;
		}
		if(minutes >= m){
			minutes -= m;
		}else{
			minutes += (60 - m);
			hours--;
		}
		hours -= h;
		if(hours > 99){
			return nullptr;
		}

		String^ sHours,^ sMinutes,^ sSeconds,^ sMilliseconds;
		if(milliseconds < 10)
			sMilliseconds = "00"+milliseconds.ToString();
		else if(milliseconds < 100)
			sMilliseconds = "0"+milliseconds.ToString();
		else
			sMilliseconds = milliseconds.ToString();

		if(seconds < 10)
			sSeconds = "0"+seconds.ToString();
		else
			sSeconds = seconds.ToString();

		if(minutes < 10)
			sMinutes = "0"+minutes.ToString();
		else 
			sMinutes = minutes.ToString();

		if(hours < 10)
			sHours = "0"+hours.ToString();
		else
			sHours = hours.ToString();

		return sHours+":"+sMinutes+":"+sSeconds+","+sMilliseconds;
	}else{
		return nullptr;
	}
}
bool M_SubDataSRT::inOrder(String^ start, String^ end){
	if(checkTimeString(start) && checkTimeString(end)){
		int ind1 = start->IndexOf(",");
		int ind2 = start->LastIndexOf(":");
		int ind3 = start->IndexOf(":");

		int milliseconds = Convert::ToInt16(start->Substring(ind1+1));
		int seconds = Convert::ToInt16(start->Substring(ind2+1,2));
		int minutes = Convert::ToInt16(start->Substring(ind3+1,2));
		int hours = Convert::ToInt16(start->Substring(0,2));

		int ms = Convert::ToInt16(end->Substring(ind1+1));
		int s = Convert::ToInt16(end->Substring(ind2+1,2));
		int m = Convert::ToInt16(end->Substring(ind3+1,2));
		int h = Convert::ToInt16(end->Substring(0,2));

		if(h > hours) return true;
		else if(h == hours && m > minutes) return true;
		else if(h == hours && m == minutes && s > seconds) return true;
		else if(h == hours && m == minutes && s == seconds && ms > milliseconds) return true;
		else if(h == hours && m == minutes && s == seconds && ms == milliseconds) return true;
		else return false;

	}else{
		return false;
	}
}
bool M_SubDataSRT::inOrderNotEqual(String^ start, String^ end){
	if(checkTimeString(start) && checkTimeString(end)){
		int ind1 = start->IndexOf(",");
		int ind2 = start->LastIndexOf(":");
		int ind3 = start->IndexOf(":");

		int milliseconds = Convert::ToInt16(start->Substring(ind1+1));
		int seconds = Convert::ToInt16(start->Substring(ind2+1,2));
		int minutes = Convert::ToInt16(start->Substring(ind3+1,2));
		int hours = Convert::ToInt16(start->Substring(0,2));

		int ms = Convert::ToInt16(end->Substring(ind1+1));
		int s = Convert::ToInt16(end->Substring(ind2+1,2));
		int m = Convert::ToInt16(end->Substring(ind3+1,2));
		int h = Convert::ToInt16(end->Substring(0,2));

		if(h > hours) return true;
		else if(h == hours && m > minutes) return true;
		else if(h == hours && m == minutes && s > seconds) return true;
		else if(h == hours && m == minutes && s == seconds && ms > milliseconds) return true;
		else if(h == hours && m == minutes && s == seconds && ms == milliseconds) return false;
		else return false;

	}else{
		return false;
	}
}