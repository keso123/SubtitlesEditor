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
#include "I_DAOSub.h"

I_DAOSub::I_DAOSub(void)
{
}

I_DAOSub::~I_DAOSub(void){
}

bool I_DAOSub::parseInd(String^ line, M_SubDataClass::nodeData^ data){
	try{
		int ind = Convert::ToInt16(line);
		data->ind = ind;
	}catch(System::FormatException^ e){
		return true;
	}catch(System::OverflowException^ e){
		return true;
	}
	return false;
}
bool I_DAOSub::parseStartEnd(String^ line, M_SubDataClass::nodeData^ data){
	int ind = line->IndexOf(" --> ");
	String^ sStart = line->Substring(0,ind);
	ind += 5;
	String^ sEnd = line->Substring(ind);
	data->sStart = sStart;
	data->sEnd= sEnd;
	data->start = 0;
	data->end = 0;
	return false;
}
bool I_DAOSub::parseText(System::IO::StreamReader^ file, M_SubDataClass::nodeData^ data){
	String^ text = "";
	String^ line = file->ReadLine();
	//text += line;
	while(String::Compare("",line) != 0){
		text += line+"\r\n";
		line = file->ReadLine();
	}
	data->text = text;
	return false;
}

bool I_DAOSub::loadSubtitles(System::IO::StreamReader^ file, M_SubDataClass^ sub){
	M_SubDataClass::nodeData^ data;

	bool error = false;
	while(file->EndOfStream == false && !error){
		String^ line = file->ReadLine();
		data = gcnew M_SubDataClass::nodeData;
		error = parseInd(line,data);
		if(!error){
			line = file->ReadLine();
			error = parseStartEnd(line,data);
			if(!error){
				error = parseText(file,data);
				sub->insert(data);
			}
		}
	}
	return true;
}
bool I_DAOSub::saveSubtitles(System::IO::StreamWriter^ file, M_SubDataClass^ sub){
	return true;
}

OpenFileError I_DAOSub::checkFile(String^ path, int& encoding){
	/*
	bool result = true;
	int ind = 0;
	String^ str = ".srt";
	while(ind < file->Extension->Length || result){
		char aux = file->Extension[ind];
		char aux2 = str[ind];
		if(str[ind] == file->Extension[ind]){
			System::Windows::Forms::MessageBox::Show("Iguales");
		}else{
			System::Windows::Forms::MessageBox::Show("NO iguales");
			result = false;
		}
		ind++;
	}
	return result;
	*/
	try{
		System::IO::FileInfo^ info = gcnew System::IO::FileInfo(path);
		
		//check extension
		if(String::Compare(info->Extension,".srt") == 0){
			
			//check enconding
			System::IO::FileStream^ fs = gcnew System::IO::FileStream(path, System::IO::FileMode::Open);
			System::IO::BinaryReader^ br = gcnew System::IO::BinaryReader(fs);

			Byte b1 = br->ReadByte();
			Byte b2 = br->ReadByte();
			Byte b3 = br->ReadByte();
			Byte b4 = br->ReadByte();
			encoding = TextFileEncoding::NoBOMencoding;

			if(b1 == 0x31 && b2 == 0x0D && b3 == 0x0A)/*1\r\n*/
				encoding = TextFileEncoding::NoBOMencoding;
			else{
				if(b1 == 0xEF && b2 == 0xBB && b3 == 0xBF)
					encoding = TextFileEncoding::UTF8;
				if(b1 == 0xFE && b2 == 0xFF) 
					encoding = TextFileEncoding::UTF16B;
				if(b1 == 0xFF && b2 == 0xFE) 
					encoding = TextFileEncoding::UTF16L;
				if(b1 == 0x00 && b2 == 0x00 && b3 == 0xFE && b4 == 0xFF) 
					encoding = TextFileEncoding::UTF32B;
				if(b1 == 0xFF && b2 == 0xFE && b3 == 0x00 && b4 == 0x00) 
					encoding = TextFileEncoding::UTF32L;
				if(b1 == 0x2B && b2 == 0x2F && b3 == 0x76 && 
					(b4 == 0x38 || b4 == 0x39 || b4 == 0x2B || b4 == 0x2F || b4 == 0x2D))
					encoding = TextFileEncoding::UTF7;
				if(b1 == 0xF7 && b2 == 0x64 && b3 == 0x4C) 
					encoding = TextFileEncoding::UTF1;
				if(b1 == 0xDD && b2 == 0x73 && b3 == 0x66 && b4 == 0x73)
					encoding = TextFileEncoding::UTFeBCDIC;
				if(b1 == 0x0E && b2 == 0xFE && b3 == 0xFF)
					encoding = TextFileEncoding::SCSU;
				if(b1 == 0xFB && b2 == 0xEE && b3 == 0x28)
					encoding = TextFileEncoding::BOCU1;
				if(b1 == 0x84 && b2 == 0x31 && b3 == 0x95 && b4 == 0x33)
					encoding = TextFileEncoding::GB18030;
			}
			fs->Close();

			return OpenFileError::OpenFileErrorOK;
		}else{
			return OpenFileError::fileExtensionError;
		}

	}catch(System::Security::SecurityException^ e){
		return OpenFileError::permissionsError;
	}catch(System::ArgumentException^ e){
		return OpenFileError::invalidPathError;
	}catch(System::UnauthorizedAccessException^ e){
		return OpenFileError::accessDeniedError;
	}catch(System::IO::PathTooLongException^ e){
		return OpenFileError::invalidPathError;
	}catch(System::NotSupportedException^ e){
		return OpenFileError::invalidPathError;
	}catch(System::IO::FileNotFoundException^ e){
		return OpenFileError::fileNotFoundError;
	}//more exceptions for the constructors filestream and binaryreader
}
