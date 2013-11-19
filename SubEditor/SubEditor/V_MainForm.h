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

#include "V_Controller.h"
#include "M_ObserverForm.h"
#include "M_Properties.h"
#include "V_DebugForm.h"
#include "V_TimeShiftForm.h"

namespace SubEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de V_MainForm
	/// </summary>
	public ref class V_MainForm : public System::Windows::Forms::Form , M_ObserverForm
	{
	public:
		V_MainForm(void)
		{
			debug = nullptr;
			subData = nullptr;
			keyShift = false;
			rowIndex = 0;
			isSave = false;
			InitializeComponent();

			initGUIProperties();

			setBasicGUI();

			setUpDataGrid();
			setLocationTextBox();
			setStylePanelTextBox();

			V_Controller^ c = V_Controller::getController();
			c->newSubtitles(this);
			if(DEBUG){
				debug = V_DebugForm::getDebugger();
				debug->setWindowLocation(this->DesktopLocation.X+this->Width,this->DesktopLocation.Y);
				debug->Show();
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DataGridNumberColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DataGridStartColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DataGridEndColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DataGridTextColumn;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::SplitContainer^  splitContainer3;
	private: System::Windows::Forms::SplitContainer^  splitContainer4;
	private: System::Windows::Forms::TextBox^  textBoxSubtitlesText;


	public: 
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::TextBox^  textBox2;


	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::TextBox^  textBoxStartTime;
	private: System::Windows::Forms::TextBox^  textBoxEndTime;
	private: System::Windows::Forms::TextBox^  textBoxTimeInterval;
	private: System::Windows::Forms::Button^  buttonEnterSubtitles;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;



	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripGrid;

	private: System::Windows::Forms::ToolStripMenuItem^  insertBeforeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  insertAfterToolStripMenuItem;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  subtitlesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  shiftTimesTimToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^  videoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  audioToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;



	private: bool keyShift;
	private: V_DebugForm^ debug;
	private: int rowIndex;
	private: M_SubDataClass^ subData;
	private: bool isSave;
	//
	// Interface M_ObserverForm code
	//
	public: virtual void updateDataGrid(){
				dataGridView1->Rows->Clear();
				array<Object^>^ rows;
				int cnt = 1;
				subData->moveStart();
				while(cnt <= subData->size()){
					M_SubDataClass::nodeData^ data = subData->getCurrentData();
					array<String^>^ row = gcnew array<String^>{data->ind.ToString(),
						data->sStart,data->sEnd,data->text};
					dataGridView1->Rows->Add( row );
					cnt++;
					subData->moveNext();
				}
				this->textBoxSubtitlesText->Text = (String^)this->dataGridView1->Rows[rowIndex]->Cells[3]->Value;
				this->textBoxStartTime->Text = (String^)this->dataGridView1->Rows[rowIndex]->Cells[1]->Value;
				this->textBoxEndTime->Text = (String^)this->dataGridView1->Rows[rowIndex]->Cells[2]->Value;
				this->textBoxTimeInterval->Text = subData->decraseTime(this->textBoxEndTime->Text,this->textBoxStartTime->Text);
				this->dataGridView1->Rows[0]->Selected = false;
				this->dataGridView1->Rows[rowIndex]->Selected = true;
				//dataGridView1->Rows[1]->Selected = true;
				/*array<String^>^row1 = gcnew array<String^>{
				"1","00:00:00:000","00:00:00:000","hola probando..."
				};
				array<Object^>^rows = {row1};
				  System::Collections::IEnumerator^ myEnum = rows->GetEnumerator();
				  while ( myEnum->MoveNext() )
				  {
					 array<String^>^rowArray = safe_cast<array<String^>^>(myEnum->Current);
					 dataGridView1->Rows->Add( rowArray );
				  }*/
			}
	public: virtual void updateSubData(M_SubDataClass^ data){
				if(subData != nullptr){
					delete subData;
					subData = nullptr;
				}
				subData = data;
			}
	public: virtual void updataDataGrid(int row, M_SubDataClass::nodeData^ data){
				DataGridViewRow^ r = dataGridView1->Rows[row];
				r->Cells[0]->Value = data->ind.ToString();
				r->Cells[1]->Value = data->sStart;
				r->Cells[2]->Value = data->sEnd;
				r->Cells[3]->Value = data->text;
				this->dataGridView1->Rows[row]->Selected = true;
			}
	public: virtual void errorNotEnoughRoomSub(){
				//MessageBox::Show("Not Enough Room");
				if(DEBUG){
					debug = V_DebugForm::getDebugger();
					debug->Show();
					debug->insertLine("errorNotEnoughRoomSub");
					debug->insertLine("Los tiempos del subtitulo no son validos");
				}
			}
	public: virtual void errorNotErase(){
				if(DEBUG){
					debug = V_DebugForm::getDebugger();
					debug->Show();
					debug->insertLine("No se ha borrado el subtitulo");
				}
			 }
	public: virtual void updateSubData(int shiftMode, int mode, int rowsAffected, int timesAffected, String^ time){
				if(DEBUG){
					debug = V_DebugForm::getDebugger();
					debug->Show();
					debug->insertLine("updateSubData");
				}
				V_Controller^ c = V_Controller::getController();
				c->shiftTime(this,subData,shiftMode,mode,rowsAffected,timesAffected,time,rowIndex);
			}
	public: virtual void saveOK(){
				if(DEBUG){
					debug = V_DebugForm::getDebugger();
					debug->Show();
					debug->insertLine("Guardado con exito");
				}
			}
	public: virtual void saveError(){
				if(DEBUG){
					debug = V_DebugForm::getDebugger();
					debug->Show();
					debug->insertLine("Error al guardar");
				}
			}
	//
	// private methods
	//
	private: void editSubtitle(String^ text){
				 String^ start = this->textBoxStartTime->Text;
				 String^ end = this->textBoxEndTime->Text;

				 /*int row;
				 try{
					row = Convert::ToInt16(numericUpDownSubtitlesIndex->Text);
				 }catch(System::FormatException^ e){
					return;
				 }catch(System::OverflowException^ e){
					return;
				 }
				 if(row != 0){
					rowIndex = row - 1;
				 }*/
				 V_Controller^ c = V_Controller::getController();
				 c->editSubtitlesText(this,subData,rowIndex + 1,start,end,text);
				 this->dataGridView1->Rows[rowIndex]->Selected = false;
				 rowIndex++;
				 this->dataGridView1->Rows[rowIndex]->Selected = true;
				 this->textBoxSubtitlesText->Text = subData->get(rowIndex + 1)->text;
				 this->textBoxStartTime->Text = subData->get(rowIndex + 1)->sStart;
				 this->textBoxEndTime->Text = subData->get(rowIndex + 1)->sEnd;
				 this->textBoxTimeInterval->Text = subData->decraseTime(this->textBoxEndTime->Text,this->textBoxStartTime->Text);
				 isSave = false;
			 }
	private: void insertSubtitle(int pos){
				 V_Controller^ c = V_Controller::getController();
				 c->insertSubtitles(this,subData,pos);
			 }
	private: void changeTimeTextBox(System::Windows::Forms::TextBox^ box, System::Windows::Forms::KeyPressEventArgs^  e){
				 if(e->KeyChar >= 48 && e->KeyChar <= 57){
					 //00:00:00,000
					 int pos = box->SelectionStart;
					 if(pos == 2 || pos == 5 || pos == 8){
						 pos = pos + 1;
					 }else if(pos == box->Text->Length){
						pos = pos - 1;
					 }
					 String^ text1 = box->Text->Substring(0,pos);
					 String^ text2 = box->Text->Substring(pos+1);
					 int n = e->KeyChar - 48;
					 String^ number = n.ToString();
					 box->Text = text1 + number + text2;
					 box->SelectionStart = pos +1;
					 box->SelectionLength = 0;
					 e->Handled = true;
					return;
				}
				if(e->KeyChar == 8){
					int pos = box->SelectionStart;
					if(pos == 3 || pos == 6 || pos == 9){
						box->SelectionStart = pos - 1;
						box->SelectionLength = 0;
						e->Handled = true;
						return;
					}else if(pos == 0){
						e->Handled = true;
						return;
					}
					String^ text1 = box->Text->Substring(0,pos - 1);
					String^ text2 = box->Text->Substring(pos);
					int n = 0;
					String^ number = n.ToString();
					box->Text = text1 + number + text2;
					box->SelectionStart = pos - 1;
					box->SelectionLength = 0;
					e->Handled = true;
					return;
				}
				e->Handled = true;
			 }
	private: System::Windows::Forms::DialogResult askSaveSubtitles(){
				 String^ name = subData->getName();
				 System::Windows::Forms::DialogResult result = MessageBox::Show("Do you want to save changes to "+name+"?","Unsaved changes",MessageBoxButtons::YesNoCancel,MessageBoxIcon::Question);
				 return result;
			 }
	private: bool saveSubtitles(){
				 String^ path;
				 if(subData->getPath() == nullptr){ 
					 if(this->saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
						 path = saveFileDialog1->FileName;
					 }else{
						 return false;//not save
					 }
				 }else{
					  path = subData->getPath();
				 }
				 V_Controller^ c = V_Controller::getController();
				 try{
					 System::IO::StreamWriter^ file;/*
					 if(subData->getEncoding() == TextFileEncoding::NoBOMencoding)
						 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::UTF7);
					 else{
						 switch (subData->getEncoding())
						 {
						 case TextFileEncoding::UTF8:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::UTF8);
							 break;
						 case TextFileEncoding::UTF16B:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::BigEndianUnicode);
 							 break;
						 case TextFileEncoding::UTF16L:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::Unicode);
 							 break;
						 case TextFileEncoding::UTF32B:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::UTF32);
							 break;
						 case TextFileEncoding::UTF7:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::UTF7);
							 break;
						 default:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::UTF8);
							 break;
						 }
					 }*/
					 file = gcnew System::IO::StreamWriter(path,false);
					 c->saveSubtitles(this,file,subData);
					 file->Close();
					 //Set all
					 isSave = true;
					 subData->setPath(path);
					 System::IO::FileInfo^ info = gcnew System::IO::FileInfo(path);
					 subData->setName(info->Name);
				 }catch(Exception^ e){
					 if(DEBUG){
					 debug = SubEditor::V_DebugForm::getDebugger();
					 debug->Show();
					 debug->insertLine("M_SubClass::saveSubtitles");
					 debug->insertLine("Error al guardar el archivo");
				 }
				 }finally{
				 }
				 return true;
			 }
	private: void setUpDataGrid(){
				 /*DataGridViewCellStyle^ style = dataGridView1->ColumnHeadersDefaultCellStyle;
				 style->BackColor = Color::Aqua;
				 style->ForeColor = Color::Black;*/

				 dataGridView1->RowsDefaultCellStyle->BackColor = Color::White;
				 dataGridView1->ColumnHeadersDefaultCellStyle->BackColor = Color::LightSeaGreen;
				 dataGridView1->EnableHeadersVisualStyles = false;
				 dataGridView1->ContextMenuStrip = this->contextMenuStripGrid;
			 }
	private: void setLocationTextBox(){
				 Point p = splitContainer4->Panel2->Location;
				 this->textBoxSubtitlesText->Location = Point(p.X+2,2); //Point(200,200);
				 this->textBoxSubtitlesText->Height = splitContainer4->Panel2->Height - 4;
				 this->textBoxSubtitlesText->Width = splitContainer4->Panel2->Width - 4;
				 //this->textBox1->BorderStyle = BorderStyle::Fixed3D;
			 }
	private: void setStylePanelTextBox(){
				 this->splitContainer4->Panel2->BackColor = Color::Black;
				 this->splitContainer4->Panel2->BorderStyle = BorderStyle::Fixed3D;
			 }
	private: void hideVideoPanel(){
				 splitContainer2->Panel2Collapsed = true;
				 splitContainer2->Panel2->Hide();
			 }
	private: void hideSoundPanel(){
				 splitContainer3->Panel1Collapsed = true;
				 splitContainer3->Panel1->Hide();
			 }
	private: void showVideoPanel(){
				 splitContainer2->Panel2Collapsed = false;
				 splitContainer2->Panel2->Show();
			 }
	private: void showSoundPanel(){
				 splitContainer3->Panel1Collapsed = false;
				 splitContainer3->Panel1->Show();
			 }
	private: void setBasicGUI(){
				 hideSoundPanel();
				 hideVideoPanel();
				 int w = this->Width;
				 int h = this->Height;
				 this->Width = w / 2;
				 this->splitContainer1->SplitterDistance = (h / 4);
				 this->splitContainer1->IsSplitterFixed = true;
				 this->splitContainer4->SplitterDistance += 10;
				 this->splitContainer4->IsSplitterFixed = true;
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			 }
	private: void initGUIProperties(){
				 M_Properties^ p = M_Properties::getProperties();
				 p->loadProperties("");
				 // menu strip gui properties
				 this->fileToolStripMenuItem->Text = p->getPropertie(Properties::E_MENU_STRIP_FILE_HEADER);
				 this->newSubtitlesToolStripMenuItem->Text = p->getPropertie(Properties::E_MENU_STRIP_FILE_NEWSUB);
				 this->openSubtitlesToolStripMenuItem->Text = p->getPropertie(Properties::E_MENU_STRIP_FILE_OPENSUB);
				 this->saveSubtitlesToolStripMenuItem->Text = p->getPropertie(Properties::E_MENU_STRIP_FILE_SAVESUB);
				 this->saveSubtitlesAsToolStripMenuItem->Text = p->getPropertie(Properties::E_MENU_STRIP_FILE_SAVESUBAS);
				 this->exitToolStripMenuItem->Text = p->getPropertie(Properties::E_MENU_STRIP_FILE_EXIT);
				 p->resetProperties();
				 //p = M_Properties::getProperties();
				 //p->getPropertie(Properties::E_PROYECT_NAME);
			 }
	// //////////////////////////////////////////////////////////////////////////////
	// //////////////////////////////////////////////////////////////////////////////
	// //////////////////////////////////////////////////////////////////////////////

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~V_MainForm()
		{
			if(debug != nullptr) debug->resetDebugger();
			if(subData != nullptr) delete subData;
			if (components)
			{
				delete components;
				//delete all the singletons
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newSubtitlesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openSubtitlesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveSubtitlesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveSubtitlesAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido del método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newSubtitlesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openSubtitlesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveSubtitlesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveSubtitlesAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->subtitlesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->shiftTimesTimToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer3 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer4 = (gcnew System::Windows::Forms::SplitContainer());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->textBoxStartTime = (gcnew System::Windows::Forms::TextBox());
			this->textBoxEndTime = (gcnew System::Windows::Forms::TextBox());
			this->textBoxTimeInterval = (gcnew System::Windows::Forms::TextBox());
			this->buttonEnterSubtitles = (gcnew System::Windows::Forms::Button());
			this->textBoxSubtitlesText = (gcnew System::Windows::Forms::TextBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->DataGridNumberColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DataGridStartColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DataGridEndColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DataGridTextColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->contextMenuStripGrid = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->insertBeforeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->insertAfterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->deleteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->videoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->audioToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer2))->BeginInit();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer3))->BeginInit();
			this->splitContainer3->Panel2->SuspendLayout();
			this->splitContainer3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer4))->BeginInit();
			this->splitContainer4->Panel1->SuspendLayout();
			this->splitContainer4->Panel2->SuspendLayout();
			this->splitContainer4->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->contextMenuStripGrid->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem, this->subtitlesToolStripMenuItem, this->videoToolStripMenuItem, this->audioToolStripMenuItem, this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(962, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->newSubtitlesToolStripMenuItem, 
				this->openSubtitlesToolStripMenuItem, this->saveSubtitlesToolStripMenuItem, this->saveSubtitlesAsToolStripMenuItem, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newSubtitlesToolStripMenuItem
			// 
			this->newSubtitlesToolStripMenuItem->Name = L"newSubtitlesToolStripMenuItem";
			this->newSubtitlesToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->newSubtitlesToolStripMenuItem->Text = L"New Subtitles";
			this->newSubtitlesToolStripMenuItem->Click += gcnew System::EventHandler(this, &V_MainForm::newSubtitlesToolStripMenuItem_Click);
			// 
			// openSubtitlesToolStripMenuItem
			// 
			this->openSubtitlesToolStripMenuItem->Name = L"openSubtitlesToolStripMenuItem";
			this->openSubtitlesToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->openSubtitlesToolStripMenuItem->Text = L"Open Subtitles...";
			this->openSubtitlesToolStripMenuItem->Click += gcnew System::EventHandler(this, &V_MainForm::openSubtitlesToolStripMenuItem_Click);
			// 
			// saveSubtitlesToolStripMenuItem
			// 
			this->saveSubtitlesToolStripMenuItem->Name = L"saveSubtitlesToolStripMenuItem";
			this->saveSubtitlesToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->saveSubtitlesToolStripMenuItem->Text = L"Save Subtitles";
			// 
			// saveSubtitlesAsToolStripMenuItem
			// 
			this->saveSubtitlesAsToolStripMenuItem->Name = L"saveSubtitlesAsToolStripMenuItem";
			this->saveSubtitlesAsToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->saveSubtitlesAsToolStripMenuItem->Text = L"Save Subtitles as...";
			this->saveSubtitlesAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &V_MainForm::saveSubtitlesAsToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->editToolStripMenuItem->Text = L"Edit";
			// 
			// subtitlesToolStripMenuItem
			// 
			this->subtitlesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->shiftTimesTimToolStripMenuItem});
			this->subtitlesToolStripMenuItem->Name = L"subtitlesToolStripMenuItem";
			this->subtitlesToolStripMenuItem->Size = System::Drawing::Size(64, 20);
			this->subtitlesToolStripMenuItem->Text = L"Subtitles";
			// 
			// shiftTimesTimToolStripMenuItem
			// 
			this->shiftTimesTimToolStripMenuItem->Name = L"shiftTimesTimToolStripMenuItem";
			this->shiftTimesTimToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->shiftTimesTimToolStripMenuItem->Text = L"Shift Times...";
			this->shiftTimesTimToolStripMenuItem->Click += gcnew System::EventHandler(this, &V_MainForm::shiftTimesTimToolStripMenuItem_Click);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 24);
			this->splitContainer1->Margin = System::Windows::Forms::Padding(10);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->splitContainer2);
			this->splitContainer1->Panel1->Padding = System::Windows::Forms::Padding(4);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->dataGridView1);
			this->splitContainer1->Panel2->Padding = System::Windows::Forms::Padding(4);
			this->splitContainer1->Size = System::Drawing::Size(962, 541);
			this->splitContainer1->SplitterDistance = 354;
			this->splitContainer1->TabIndex = 1;
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->Location = System::Drawing::Point(4, 4);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->splitContainer3);
			this->splitContainer2->Panel1->Margin = System::Windows::Forms::Padding(4);
			this->splitContainer2->Panel1->Padding = System::Windows::Forms::Padding(4);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Margin = System::Windows::Forms::Padding(4);
			this->splitContainer2->Panel2->Padding = System::Windows::Forms::Padding(4);
			this->splitContainer2->Size = System::Drawing::Size(954, 346);
			this->splitContainer2->SplitterDistance = 501;
			this->splitContainer2->TabIndex = 0;
			// 
			// splitContainer3
			// 
			this->splitContainer3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer3->Location = System::Drawing::Point(4, 4);
			this->splitContainer3->Margin = System::Windows::Forms::Padding(4);
			this->splitContainer3->Name = L"splitContainer3";
			this->splitContainer3->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer3.Panel1
			// 
			this->splitContainer3->Panel1->Margin = System::Windows::Forms::Padding(4);
			this->splitContainer3->Panel1->Padding = System::Windows::Forms::Padding(4);
			// 
			// splitContainer3.Panel2
			// 
			this->splitContainer3->Panel2->Controls->Add(this->splitContainer4);
			this->splitContainer3->Panel2->Margin = System::Windows::Forms::Padding(4);
			this->splitContainer3->Panel2->Padding = System::Windows::Forms::Padding(4);
			this->splitContainer3->Size = System::Drawing::Size(493, 338);
			this->splitContainer3->SplitterDistance = 184;
			this->splitContainer3->TabIndex = 0;
			// 
			// splitContainer4
			// 
			this->splitContainer4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer4->Location = System::Drawing::Point(4, 4);
			this->splitContainer4->Margin = System::Windows::Forms::Padding(4);
			this->splitContainer4->Name = L"splitContainer4";
			this->splitContainer4->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer4.Panel1
			// 
			this->splitContainer4->Panel1->Controls->Add(this->flowLayoutPanel1);
			this->splitContainer4->Panel1->Margin = System::Windows::Forms::Padding(4);
			this->splitContainer4->Panel1->Padding = System::Windows::Forms::Padding(4);
			// 
			// splitContainer4.Panel2
			// 
			this->splitContainer4->Panel2->Controls->Add(this->textBoxSubtitlesText);
			this->splitContainer4->Panel2->Margin = System::Windows::Forms::Padding(4);
			this->splitContainer4->Panel2->Padding = System::Windows::Forms::Padding(4);
			this->splitContainer4->Panel2->SizeChanged += gcnew System::EventHandler(this, &V_MainForm::splitContainer4_Panel2_SizeChanged);
			this->splitContainer4->Size = System::Drawing::Size(485, 142);
			this->splitContainer4->SplitterDistance = 64;
			this->splitContainer4->TabIndex = 0;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->checkBox1);
			this->flowLayoutPanel1->Controls->Add(this->comboBox1);
			this->flowLayoutPanel1->Controls->Add(this->comboBox2);
			this->flowLayoutPanel1->Controls->Add(this->textBox2);
			this->flowLayoutPanel1->Controls->Add(this->numericUpDown1);
			this->flowLayoutPanel1->Controls->Add(this->textBoxStartTime);
			this->flowLayoutPanel1->Controls->Add(this->textBoxEndTime);
			this->flowLayoutPanel1->Controls->Add(this->textBoxTimeInterval);
			this->flowLayoutPanel1->Controls->Add(this->buttonEnterSubtitles);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(4, 4);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(477, 56);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(3, 3);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(70, 17);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = L"Comment";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(79, 3);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 1;
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(206, 3);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 21);
			this->comboBox2->TabIndex = 7;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(333, 3);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 2;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(439, 3);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(31, 20);
			this->numericUpDown1->TabIndex = 9;
			// 
			// textBoxStartTime
			// 
			this->textBoxStartTime->Location = System::Drawing::Point(3, 30);
			this->textBoxStartTime->Name = L"textBoxStartTime";
			this->textBoxStartTime->Size = System::Drawing::Size(100, 20);
			this->textBoxStartTime->TabIndex = 4;
			this->textBoxStartTime->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &V_MainForm::textBoxStartTime_KeyPress);
			// 
			// textBoxEndTime
			// 
			this->textBoxEndTime->Location = System::Drawing::Point(109, 30);
			this->textBoxEndTime->Name = L"textBoxEndTime";
			this->textBoxEndTime->Size = System::Drawing::Size(100, 20);
			this->textBoxEndTime->TabIndex = 5;
			this->textBoxEndTime->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &V_MainForm::textBoxEndTime_KeyPress);
			// 
			// textBoxTimeInterval
			// 
			this->textBoxTimeInterval->Location = System::Drawing::Point(215, 30);
			this->textBoxTimeInterval->Name = L"textBoxTimeInterval";
			this->textBoxTimeInterval->Size = System::Drawing::Size(100, 20);
			this->textBoxTimeInterval->TabIndex = 6;
			this->textBoxTimeInterval->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &V_MainForm::textBoxTimeInterval_KeyPress);
			// 
			// buttonEnterSubtitles
			// 
			this->buttonEnterSubtitles->Location = System::Drawing::Point(321, 30);
			this->buttonEnterSubtitles->Name = L"buttonEnterSubtitles";
			this->buttonEnterSubtitles->Size = System::Drawing::Size(30, 23);
			this->buttonEnterSubtitles->TabIndex = 8;
			this->buttonEnterSubtitles->Text = L"OK";
			this->buttonEnterSubtitles->UseVisualStyleBackColor = true;
			this->buttonEnterSubtitles->Click += gcnew System::EventHandler(this, &V_MainForm::buttonEnterSubtitles_Click);
			// 
			// textBoxSubtitlesText
			// 
			this->textBoxSubtitlesText->Location = System::Drawing::Point(206, 23);
			this->textBoxSubtitlesText->Multiline = true;
			this->textBoxSubtitlesText->Name = L"textBoxSubtitlesText";
			this->textBoxSubtitlesText->Size = System::Drawing::Size(100, 20);
			this->textBoxSubtitlesText->TabIndex = 0;
			this->textBoxSubtitlesText->TextChanged += gcnew System::EventHandler(this, &V_MainForm::textBox1_TextChanged);
			this->textBoxSubtitlesText->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &V_MainForm::textBox1_KeyDown);
			this->textBoxSubtitlesText->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &V_MainForm::textBox1_KeyUp);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeColumns = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->DataGridNumberColumn, 
				this->DataGridStartColumn, this->DataGridEndColumn, this->DataGridTextColumn});
			this->dataGridView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dataGridView1->GridColor = System::Drawing::SystemColors::ActiveCaption;
			this->dataGridView1->Location = System::Drawing::Point(4, 4);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(954, 175);
			this->dataGridView1->TabIndex = 0;
			this->dataGridView1->CellMouseClick += gcnew System::Windows::Forms::DataGridViewCellMouseEventHandler(this, &V_MainForm::dataGridView1_CellMouseClick);
			this->dataGridView1->RowStateChanged += gcnew System::Windows::Forms::DataGridViewRowStateChangedEventHandler(this, &V_MainForm::dataGridView1_RowStateChanged);
			this->dataGridView1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &V_MainForm::dataGridView1_MouseDown);
			// 
			// DataGridNumberColumn
			// 
			this->DataGridNumberColumn->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->DataGridNumberColumn->HeaderText = L"#";
			this->DataGridNumberColumn->Name = L"DataGridNumberColumn";
			this->DataGridNumberColumn->ReadOnly = true;
			this->DataGridNumberColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Programmatic;
			this->DataGridNumberColumn->Width = 39;
			// 
			// DataGridStartColumn
			// 
			this->DataGridStartColumn->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->DataGridStartColumn->HeaderText = L"Start";
			this->DataGridStartColumn->Name = L"DataGridStartColumn";
			this->DataGridStartColumn->ReadOnly = true;
			this->DataGridStartColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Programmatic;
			this->DataGridStartColumn->Width = 54;
			// 
			// DataGridEndColumn
			// 
			this->DataGridEndColumn->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->DataGridEndColumn->HeaderText = L"End";
			this->DataGridEndColumn->Name = L"DataGridEndColumn";
			this->DataGridEndColumn->ReadOnly = true;
			this->DataGridEndColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Programmatic;
			this->DataGridEndColumn->Width = 51;
			// 
			// DataGridTextColumn
			// 
			this->DataGridTextColumn->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->DataGridTextColumn->HeaderText = L"Text";
			this->DataGridTextColumn->Name = L"DataGridTextColumn";
			this->DataGridTextColumn->ReadOnly = true;
			this->DataGridTextColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Programmatic;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// contextMenuStripGrid
			// 
			this->contextMenuStripGrid->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->insertBeforeToolStripMenuItem, 
				this->insertAfterToolStripMenuItem, this->toolStripMenuItem1, this->deleteToolStripMenuItem});
			this->contextMenuStripGrid->Name = L"contextMenuStripGrid";
			this->contextMenuStripGrid->Size = System::Drawing::Size(149, 76);
			// 
			// insertBeforeToolStripMenuItem
			// 
			this->insertBeforeToolStripMenuItem->Name = L"insertBeforeToolStripMenuItem";
			this->insertBeforeToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->insertBeforeToolStripMenuItem->Text = L"Insert (Before)";
			this->insertBeforeToolStripMenuItem->Click += gcnew System::EventHandler(this, &V_MainForm::insertBeforeToolStripMenuItem_Click);
			// 
			// insertAfterToolStripMenuItem
			// 
			this->insertAfterToolStripMenuItem->Name = L"insertAfterToolStripMenuItem";
			this->insertAfterToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->insertAfterToolStripMenuItem->Text = L"Insert (After)";
			this->insertAfterToolStripMenuItem->Click += gcnew System::EventHandler(this, &V_MainForm::insertAfterToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(145, 6);
			// 
			// deleteToolStripMenuItem
			// 
			this->deleteToolStripMenuItem->Name = L"deleteToolStripMenuItem";
			this->deleteToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->deleteToolStripMenuItem->Text = L"Delete";
			this->deleteToolStripMenuItem->Click += gcnew System::EventHandler(this, &V_MainForm::deleteToolStripMenuItem_Click);
			// 
			// videoToolStripMenuItem
			// 
			this->videoToolStripMenuItem->Name = L"videoToolStripMenuItem";
			this->videoToolStripMenuItem->Size = System::Drawing::Size(49, 20);
			this->videoToolStripMenuItem->Text = L"Video";
			// 
			// audioToolStripMenuItem
			// 
			this->audioToolStripMenuItem->Name = L"audioToolStripMenuItem";
			this->audioToolStripMenuItem->Size = System::Drawing::Size(51, 20);
			this->audioToolStripMenuItem->Text = L"Audio";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// V_MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(962, 565);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"V_MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SubEditor";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->splitContainer2->Panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer2))->EndInit();
			this->splitContainer2->ResumeLayout(false);
			this->splitContainer3->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer3))->EndInit();
			this->splitContainer3->ResumeLayout(false);
			this->splitContainer4->Panel1->ResumeLayout(false);
			this->splitContainer4->Panel2->ResumeLayout(false);
			this->splitContainer4->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer4))->EndInit();
			this->splitContainer4->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->contextMenuStripGrid->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//
		// New Subtitles clean all, and creates a new subtitles. If there is a subtitle already open ask if want to save it
		//
	private: System::Void newSubtitlesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(!isSave && subData->size() > 1){
					 System::Windows::Forms::DialogResult result = askSaveSubtitles();
					 if(result == System::Windows::Forms::DialogResult::Yes){
						 if(!saveSubtitles()) return;
						 rowIndex = 0;
						 V_Controller^ c = V_Controller::getController();
						 c->newSubtitles(this);
					 }else if(result == System::Windows::Forms::DialogResult::No){
						 rowIndex = 0;
						 V_Controller^ c = V_Controller::getController();
						 c->newSubtitles(this);
					 }else{
						 return;
					 }
				 }
			 }
private: System::Void openSubtitlesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
				V_Controller^ c = V_Controller::getController();

				String^ path = openFileDialog1->FileName;

				int encoding = TextFileEncoding::NoBOMencoding;
				String^ name = "Untitled";
				if(c->checkFile(this,path,encoding,name) == OpenFileError::OpenFileErrorOK){
					try{
						System::IO::StreamReader^ file;
						if(encoding == TextFileEncoding::NoBOMencoding)
							file = gcnew System::IO::StreamReader(path,System::Text::Encoding::UTF7);
						else
							file = gcnew System::IO::StreamReader(path);
						
						c->openSubtitles(this,file,encoding,path,name);
						file->Close();
					}catch(Exception^ e){
						MessageBox::Show("Error al abrir");
					}finally{

					}
				}else{
					if(DEBUG){
						debug = SubEditor::V_DebugForm::getDebugger();
						debug->Show();
						debug->insertLine("M_SubClass::openSubtitles");
						debug->insertLine("Error al abrir archivo, archivo no valido");
					}
				}
			 }
		 }
private: System::Void dataGridView1_RowStateChanged(System::Object^  sender, System::Windows::Forms::DataGridViewRowStateChangedEventArgs^  e) {
			 // for any other operation except, StateChanged, return
			 if(e->StateChanged != DataGridViewElementStates::Selected) return;

		 }
private: System::Void splitContainer4_Panel2_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
			 setLocationTextBox();
		 }
private: System::Void dataGridView1_CellMouseClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellMouseEventArgs^  e) {	 
			 rowIndex = e->RowIndex;
			 this->textBoxSubtitlesText->Text = subData->get(rowIndex + 1)->text;
			 this->textBoxStartTime->Text = subData->get(rowIndex + 1)->sStart;
			 this->textBoxEndTime->Text = subData->get(rowIndex + 1)->sEnd;
			 this->textBoxTimeInterval->Text = subData->decraseTime(this->textBoxEndTime->Text,this->textBoxStartTime->Text);
		 }
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 // Change the subtitles here?
		 }
private: System::Void textBox1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode == Keys::ShiftKey){
				 keyShift = false;
				 return;
			 }
			 // Return for any key except 'enter'
			 if(e->KeyCode != Keys::Enter) return;
			 if(keyShift == true) return;
			 
			 //byte* keys = new byte[255];
			 //GetKeyboardState(keys);
			 //if(keys[(int)Keys::Shift] == 129) return;
			 String^ text = this->textBoxSubtitlesText->Text->Substring(0,this->textBoxSubtitlesText->Text->Length - 1);
			 this->textBoxSubtitlesText->SelectionStart = text->Length;
			 this->textBoxSubtitlesText->SelectionLength = 0;
			 editSubtitle(text);
		 }
private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode == Keys::ShiftKey){
				 keyShift = true;
				 return;
			 }

		 }
private: System::Void buttonEnterSubtitles_Click(System::Object^  sender, System::EventArgs^  e) {
			 String^ text = this->textBoxSubtitlesText->Text;
			 editSubtitle(text);
		 }
private: System::Void dataGridView1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(e->Button == System::Windows::Forms::MouseButtons::Right){
				 DataGridView::HitTestInfo^ p = this->dataGridView1->HitTest(e->X,e->Y);
				 if(p->Type == DataGridViewHitTestType::ColumnHeader || p->Type == DataGridViewHitTestType::None){
					 this->dataGridView1->ContextMenuStrip = nullptr;
				 }else{
					 this->dataGridView1->Rows[rowIndex]->Selected = false;
					 rowIndex = p->RowIndex;
					 this->dataGridView1->Rows[rowIndex]->Selected = true;
					 this->textBoxSubtitlesText->Text = subData->get(rowIndex + 1)->text;
					 this->textBoxStartTime->Text = subData->get(rowIndex + 1)->sStart;
					 this->textBoxEndTime->Text = subData->get(rowIndex + 1)->sEnd;
					 this->textBoxTimeInterval->Text = subData->decraseTime(this->textBoxEndTime->Text,this->textBoxStartTime->Text);
					 this->dataGridView1->ContextMenuStrip = this->contextMenuStripGrid;
				 }
			 }
		 }
private: System::Void textBoxStartTime_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 changeTimeTextBox(this->textBoxStartTime,e);
			 this->textBoxTimeInterval->Text = subData->decraseTime(this->textBoxEndTime->Text,this->textBoxStartTime->Text);
		 }
private: System::Void textBoxEndTime_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 changeTimeTextBox(this->textBoxEndTime,e);
			 this->textBoxTimeInterval->Text = subData->decraseTime(this->textBoxEndTime->Text,this->textBoxStartTime->Text);
		 }
private: System::Void textBoxTimeInterval_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 changeTimeTextBox(this->textBoxTimeInterval,e);
			 this->textBoxEndTime->Text = subData->increaseTime(this->textBoxStartTime->Text,this->textBoxTimeInterval->Text);
		 }
private: System::Void insertBeforeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(rowIndex > 0){
				 insertSubtitle(rowIndex + 1);
			 }
		 }
private: System::Void insertAfterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(rowIndex < subData->size() - 1){
				 insertSubtitle(rowIndex + 2);
			 }
		 }
private: System::Void deleteToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 V_Controller^ c = V_Controller::getController();
			 c->eraseSubtitles(this,subData,rowIndex + 1);
		 }
private: System::Void shiftTimesTimToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 V_TimeShiftForm^ timeForm = gcnew V_TimeShiftForm();
			 timeForm->setObserver(this);
			 timeForm->ShowDialog();
		 }
private: System::Void saveSubtitlesAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(this->saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
				 V_Controller^ c = V_Controller::getController();

				 String^ path = saveFileDialog1->FileName;
				 try{
					 System::IO::StreamWriter^ file;
					 if(subData->getEncoding() == TextFileEncoding::NoBOMencoding)
						 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::UTF7);
					 else{
						 switch (subData->getEncoding())
						 {
						 case TextFileEncoding::UTF8:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::UTF8);
							 break;
						 case TextFileEncoding::UTF16B:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::BigEndianUnicode);
							 break;
						 case TextFileEncoding::UTF16L:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::Unicode);
							 break;
						 case TextFileEncoding::UTF32B:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::UTF32);
							 break;
						 case TextFileEncoding::UTF7:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::UTF7);
							 break;
						 default:
							 file = gcnew System::IO::StreamWriter(path,false,System::Text::Encoding::UTF8);
							 break;
						 }
					 }
					 c->saveSubtitles(this,file,subData);
					 isSave = true;
					 subData->setPath(path);
					 System::IO::FileInfo^ info = gcnew System::IO::FileInfo(path);
					 subData->setName(info->Name);
					 file->Close();
				 }catch(Exception^ e){
					 if(DEBUG){
						debug = SubEditor::V_DebugForm::getDebugger();
						debug->Show();
						debug->insertLine("M_SubClass::saveSubtitles");
						debug->insertLine("Error al guardar el archivo");
					}
				 }finally{
				 }
			 }
		 }
};
}
