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

namespace SubEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de V_TimeShiftForm
	/// </summary>
	public ref class V_TimeShiftForm : public System::Windows::Forms::Form
	{
	public:
		V_TimeShiftForm(void)
		{
			InitializeComponent();
			this->StartPosition = FormStartPosition::CenterParent;
			initGUI();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~V_TimeShiftForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: bool time;
	private: bool frame;
	private: bool backward;
	private: bool forward;
	private: bool allRows;
	private: bool selectionF;
	private: bool selectionB;
	private: bool startEnd;
	private: bool start;
	private: bool end;
	private: String^ timeText;
	private: String^ frameText;
			 // Methods
	private: void initGUI(){
				 time = true;
				 frame = false;
				 backward = false;
				 forward = false;
				 allRows = true;
				 selectionF = false;
				 selectionB = false;
				 startEnd = true;
				 start = false;
				 end = false;
				 timeText = "00:00:00,000";
				 frameText = "";
				 this->checkBoxTime->Checked = time;
				 this->checkBoxFrames->Checked = frame;
				 this->checkBoxForward->Checked = forward;
				 this->checkBoxBackward->Checked = backward;
				 this->checkBoxAllRows->Checked = allRows;
				 this->checkBoxSelectionForward->Checked = selectionF;
				 this->checkBoxSelectionBackward->Checked = selectionB;
				 this->checkBoxStartEnd->Checked = startEnd;
				 this->checkBoxStart->Checked = start;
				 this->checkBoxEnd->Checked = end;
				 this->textBoxTime->Text = timeText;
				 this->textBoxFrame->Text = frameText;
			 }
			 // End Methods
	private: System::Windows::Forms::GroupBox^  groupBox1;
	protected: 
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::TextBox^  textBoxFrame;

	private: System::Windows::Forms::TextBox^  textBoxTime;

	private: System::Windows::Forms::CheckBox^  checkBoxBackward;

	private: System::Windows::Forms::CheckBox^  checkBoxForward;

	private: System::Windows::Forms::CheckBox^  checkBoxFrames;

	private: System::Windows::Forms::CheckBox^  checkBoxTime;
	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Button^  buttonCancel;


	private: System::Windows::Forms::CheckBox^  checkBoxSelectionBackward;

	private: System::Windows::Forms::CheckBox^  checkBoxSelectionForward;
	private: System::Windows::Forms::CheckBox^  checkBoxAllRows;
	private: System::Windows::Forms::CheckBox^  checkBoxEnd;

	private: System::Windows::Forms::CheckBox^  checkBoxStart;

	private: System::Windows::Forms::CheckBox^  checkBoxStartEnd;

	private:
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido del método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxFrame = (gcnew System::Windows::Forms::TextBox());
			this->textBoxTime = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxBackward = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxForward = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxFrames = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxTime = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxSelectionBackward = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxSelectionForward = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxAllRows = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxEnd = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxStart = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxStartEnd = (gcnew System::Windows::Forms::CheckBox());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBoxFrame);
			this->groupBox1->Controls->Add(this->textBoxTime);
			this->groupBox1->Controls->Add(this->checkBoxBackward);
			this->groupBox1->Controls->Add(this->checkBoxForward);
			this->groupBox1->Controls->Add(this->checkBoxFrames);
			this->groupBox1->Controls->Add(this->checkBoxTime);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(204, 91);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Shift by";
			// 
			// textBoxFrame
			// 
			this->textBoxFrame->Location = System::Drawing::Point(94, 44);
			this->textBoxFrame->Name = L"textBoxFrame";
			this->textBoxFrame->Size = System::Drawing::Size(100, 20);
			this->textBoxFrame->TabIndex = 5;
			// 
			// textBoxTime
			// 
			this->textBoxTime->Location = System::Drawing::Point(94, 20);
			this->textBoxTime->Name = L"textBoxTime";
			this->textBoxTime->Size = System::Drawing::Size(100, 20);
			this->textBoxTime->TabIndex = 4;
			// 
			// checkBoxBackward
			// 
			this->checkBoxBackward->AutoSize = true;
			this->checkBoxBackward->Location = System::Drawing::Point(109, 68);
			this->checkBoxBackward->Name = L"checkBoxBackward";
			this->checkBoxBackward->Size = System::Drawing::Size(74, 17);
			this->checkBoxBackward->TabIndex = 3;
			this->checkBoxBackward->Text = L"Backward";
			this->checkBoxBackward->UseVisualStyleBackColor = true;
			this->checkBoxBackward->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &V_TimeShiftForm::checkBoxBackward_MouseUp);
			// 
			// checkBoxForward
			// 
			this->checkBoxForward->AutoSize = true;
			this->checkBoxForward->Location = System::Drawing::Point(7, 68);
			this->checkBoxForward->Name = L"checkBoxForward";
			this->checkBoxForward->Size = System::Drawing::Size(64, 17);
			this->checkBoxForward->TabIndex = 2;
			this->checkBoxForward->Text = L"Forward";
			this->checkBoxForward->UseVisualStyleBackColor = true;
			this->checkBoxForward->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &V_TimeShiftForm::checkBoxForward_MouseUp);
			// 
			// checkBoxFrames
			// 
			this->checkBoxFrames->AutoSize = true;
			this->checkBoxFrames->Location = System::Drawing::Point(7, 44);
			this->checkBoxFrames->Name = L"checkBoxFrames";
			this->checkBoxFrames->Size = System::Drawing::Size(63, 17);
			this->checkBoxFrames->TabIndex = 1;
			this->checkBoxFrames->Text = L"Frames:";
			this->checkBoxFrames->UseVisualStyleBackColor = true;
			this->checkBoxFrames->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &V_TimeShiftForm::checkBoxFrames_MouseUp);
			// 
			// checkBoxTime
			// 
			this->checkBoxTime->AutoSize = true;
			this->checkBoxTime->Location = System::Drawing::Point(7, 20);
			this->checkBoxTime->Name = L"checkBoxTime";
			this->checkBoxTime->Size = System::Drawing::Size(52, 17);
			this->checkBoxTime->TabIndex = 0;
			this->checkBoxTime->Text = L"Time:";
			this->checkBoxTime->UseVisualStyleBackColor = true;
			this->checkBoxTime->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &V_TimeShiftForm::checkBoxTime_MouseUp);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->checkBoxSelectionBackward);
			this->groupBox2->Controls->Add(this->checkBoxSelectionForward);
			this->groupBox2->Controls->Add(this->checkBoxAllRows);
			this->groupBox2->Location = System::Drawing::Point(12, 109);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(203, 91);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Rows affected";
			// 
			// checkBoxSelectionBackward
			// 
			this->checkBoxSelectionBackward->AutoSize = true;
			this->checkBoxSelectionBackward->Location = System::Drawing::Point(6, 68);
			this->checkBoxSelectionBackward->Name = L"checkBoxSelectionBackward";
			this->checkBoxSelectionBackward->Size = System::Drawing::Size(120, 17);
			this->checkBoxSelectionBackward->TabIndex = 2;
			this->checkBoxSelectionBackward->Text = L"Selection backward";
			this->checkBoxSelectionBackward->UseVisualStyleBackColor = true;
			this->checkBoxSelectionBackward->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &V_TimeShiftForm::checkBoxSelectionBackward_MouseUp);
			// 
			// checkBoxSelectionForward
			// 
			this->checkBoxSelectionForward->AutoSize = true;
			this->checkBoxSelectionForward->Location = System::Drawing::Point(6, 44);
			this->checkBoxSelectionForward->Name = L"checkBoxSelectionForward";
			this->checkBoxSelectionForward->Size = System::Drawing::Size(108, 17);
			this->checkBoxSelectionForward->TabIndex = 1;
			this->checkBoxSelectionForward->Text = L"Selection forward";
			this->checkBoxSelectionForward->UseVisualStyleBackColor = true;
			this->checkBoxSelectionForward->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &V_TimeShiftForm::checkBoxSelectionForward_MouseUp);
			// 
			// checkBoxAllRows
			// 
			this->checkBoxAllRows->AutoSize = true;
			this->checkBoxAllRows->Location = System::Drawing::Point(7, 20);
			this->checkBoxAllRows->Name = L"checkBoxAllRows";
			this->checkBoxAllRows->Size = System::Drawing::Size(62, 17);
			this->checkBoxAllRows->TabIndex = 0;
			this->checkBoxAllRows->Text = L"All rows";
			this->checkBoxAllRows->UseVisualStyleBackColor = true;
			this->checkBoxAllRows->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &V_TimeShiftForm::checkBoxAllRows_MouseUp);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->checkBoxEnd);
			this->groupBox3->Controls->Add(this->checkBoxStart);
			this->groupBox3->Controls->Add(this->checkBoxStartEnd);
			this->groupBox3->Location = System::Drawing::Point(13, 206);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(203, 91);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Times affected";
			// 
			// checkBoxEnd
			// 
			this->checkBoxEnd->AutoSize = true;
			this->checkBoxEnd->Location = System::Drawing::Point(6, 68);
			this->checkBoxEnd->Name = L"checkBoxEnd";
			this->checkBoxEnd->Size = System::Drawing::Size(67, 17);
			this->checkBoxEnd->TabIndex = 2;
			this->checkBoxEnd->Text = L"End only";
			this->checkBoxEnd->UseVisualStyleBackColor = true;
			this->checkBoxEnd->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &V_TimeShiftForm::checkBoxEnd_MouseUp);
			// 
			// checkBoxStart
			// 
			this->checkBoxStart->AutoSize = true;
			this->checkBoxStart->Location = System::Drawing::Point(6, 44);
			this->checkBoxStart->Name = L"checkBoxStart";
			this->checkBoxStart->Size = System::Drawing::Size(70, 17);
			this->checkBoxStart->TabIndex = 1;
			this->checkBoxStart->Text = L"Start only";
			this->checkBoxStart->UseVisualStyleBackColor = true;
			this->checkBoxStart->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &V_TimeShiftForm::checkBoxStart_MouseUp);
			// 
			// checkBoxStartEnd
			// 
			this->checkBoxStartEnd->AutoSize = true;
			this->checkBoxStartEnd->Location = System::Drawing::Point(7, 20);
			this->checkBoxStartEnd->Name = L"checkBoxStartEnd";
			this->checkBoxStartEnd->Size = System::Drawing::Size(91, 17);
			this->checkBoxStartEnd->TabIndex = 0;
			this->checkBoxStartEnd->Text = L"Start and End";
			this->checkBoxStartEnd->UseVisualStyleBackColor = true;
			this->checkBoxStartEnd->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &V_TimeShiftForm::checkBoxStartEnd_MouseUp);
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(36, 303);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(75, 23);
			this->buttonOK->TabIndex = 3;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &V_TimeShiftForm::buttonOK_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->Location = System::Drawing::Point(117, 303);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 4;
			this->buttonCancel->Text = L"Cancel";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &V_TimeShiftForm::buttonCancel_Click);
			// 
			// V_TimeShiftForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(229, 337);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"V_TimeShiftForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Shift Times";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void checkBoxForward_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 forward = !forward;
			 backward = !forward;
			 this->checkBoxBackward->Checked = backward;
		 }
private: System::Void checkBoxBackward_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 backward = !backward;
			 forward = !backward;
			 this->checkBoxForward->Checked = forward;
		 }
private: System::Void checkBoxTime_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 time = !time;
			 frame = !time;
			 //this->checkBoxTime->Checked = time;
			 this->checkBoxFrames->Checked = frame;
		 }
private: System::Void checkBoxFrames_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 frame = !frame;
			 time = !frame;
			 this->checkBoxTime->Checked = time;
			 //this->checkBoxFrames->Checked = frame;
		 }
private: System::Void checkBoxAllRows_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 allRows = !allRows;
			 if(allRows){
				 selectionF = false;
				 selectionB = false;
			 }
			 this->checkBoxSelectionForward->Checked = selectionF;
			 this->checkBoxSelectionBackward->Checked = selectionB;
		 }
private: System::Void checkBoxSelectionForward_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 selectionF = !selectionF;
			 selectionB = !selectionF;
			 if(selectionF){
				 allRows = false;
			 }
			 this->checkBoxSelectionBackward->Checked = selectionB;
			 this->checkBoxAllRows->Checked = allRows;
		 }
private: System::Void checkBoxSelectionBackward_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 selectionB = !selectionB;
			 selectionF = !selectionB;
			 if(selectionB){
				 allRows = false;
			 }
			 this->checkBoxSelectionForward->Checked = selectionF;
			 this->checkBoxAllRows->Checked = allRows;
		 }
private: System::Void checkBoxStartEnd_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 startEnd = !startEnd;
			 if(startEnd){
				 start = false;
				 end = false;
			 }
			 this->checkBoxStart->Checked = start;
			 this->checkBoxEnd->Checked = end;
		 }
private: System::Void checkBoxStart_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 start = !start;
			 end = !start;
			 if(start){
				 startEnd = false;
			 }
			 this->checkBoxEnd->Checked = end;
			 this->checkBoxStartEnd->Checked = startEnd;
		 }
private: System::Void checkBoxEnd_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 end = !end;
			 start = !end;
			 if(end){
				 startEnd = false;
			 }
			 this->checkBoxStart->Checked = start;
			 this->checkBoxStartEnd->Checked = startEnd;
		 }
private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
