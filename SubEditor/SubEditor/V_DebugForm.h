#pragma once

namespace SubEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de V_DebugForm
	/// </summary>
	public ref class V_DebugForm : public System::Windows::Forms::Form
	{
	private: static V_DebugForm^ instance;
	private: static bool instanceFlag = false;
	private:
		V_DebugForm(void)
		{
			InitializeComponent();
			setLocationTextBox();
			//
			//TODO: agregar código de constructor aquí
			//
		}
	
	public: static V_DebugForm^ getDebugger(){
				if(instanceFlag == false){
					instance = gcnew V_DebugForm;
					instanceFlag = true;
				}
				return instance;	
			}
	public: static void resetDebugger(){
				delete instance;
				instanceFlag = false;
			}
	public: void setWindowLocation(int x, int y){
				this->DesktopLocation.X = x;
				this->DesktopLocation.Y = y;
				this->DesktopLocation  = Point(x,y);
			}

	private: void setLocationTextBox(){
				 Point p = panel1->Location;
				 this->textBox1->Location = Point(p.X+2,2); //Point(200,200);
				 this->textBox1->Height = panel1->Height - 4;
				 this->textBox1->Width = panel1->Width - 4;
				 //this->textBox1->BorderStyle = BorderStyle::Fixed3D;
			 }
	public: void setText(String^ text){
				this->textBox1->Text = text;
			}
	public: void clearText(){
				this->textBox1->Text = "";
			}
	public: void insertLine(String^ text){
				this->textBox1->Text = this->textBox1->Text + "\r\n" + text;
			}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~V_DebugForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;

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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(315, 262);
			this->panel1->TabIndex = 0;
			this->panel1->SizeChanged += gcnew System::EventHandler(this, &V_DebugForm::panel1_SizeChanged);
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::WindowText;
			this->textBox1->ForeColor = System::Drawing::SystemColors::Window;
			this->textBox1->Location = System::Drawing::Point(25, 81);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox1->Size = System::Drawing::Size(235, 113);
			this->textBox1->TabIndex = 0;
			// 
			// V_DebugForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(315, 262);
			this->Controls->Add(this->panel1);
			this->Name = L"V_DebugForm";
			this->Text = L"Debug";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &V_DebugForm::V_DebugForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &V_DebugForm::V_DebugForm_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void panel1_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
				 setLocationTextBox();
			 }
	private: System::Void V_DebugForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 
			 }
private: System::Void V_DebugForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 this->resetDebugger();
		 }
};
}
