
/*
=====  INFORMACJE  ======
TEMAT PROJEKTU : Motion Blur - liniowe rozmycie obrazu.
KRÓTKI OPIS : Funkcja nak³adaj¹ca na obraz ARGB filtr Motion Blur - rozmycia pozoruj¹cego ruch liniowy.
Algorytm pracuje na mape bajtów uprzednio przygotowan¹ przez czêœæ GUI.
DATA WYKONANIA : Semestr Zimowy 2024 / 2025
AUTOR: Krzysztof Kluczka
*/

/*
=====  GUI  ======
GUI w WinForms odpoawiadaj¹ce za ob³sugê programu, w tym ³adowanie i zapis obrazu.
*/




#pragma once

#include <string>
#include "MotionBlur.h"

int LinearBlur(unsigned char* imageData, int width, int height, int channels, int blurLevel, int angle, bool use_ASM);
double getAsmTimeMs();
double getCppTimeMs();


namespace GUIns {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;


	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ processImageButton;
	private: System::Windows::Forms::TrackBar^ blurLevelTrackBar;
	protected:


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ blurLevelTextBox;

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::TextBox^ angleTextBox;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TrackBar^ angleTrackBar;


	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Button^ loadFileButton;

	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TextBox^ FilePathTextBox;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ saveFileButton;

	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;




	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		/// 
		System::ComponentModel::Container^ components;
		array<System::Byte>^ managedPngData;
		Bitmap^ originalImage;
	private: System::Windows::Forms::Label^ outputLabel;

	private: System::Windows::Forms::Label^ asmTimeLabel;
	private: System::Windows::Forms::Label^ cppTimeLabel;


		   Bitmap^ tempImage;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->processImageButton = (gcnew System::Windows::Forms::Button());
			   this->blurLevelTrackBar = (gcnew System::Windows::Forms::TrackBar());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->blurLevelTextBox = (gcnew System::Windows::Forms::TextBox());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->angleTextBox = (gcnew System::Windows::Forms::TextBox());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->angleTrackBar = (gcnew System::Windows::Forms::TrackBar());
			   this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			   this->loadFileButton = (gcnew System::Windows::Forms::Button());
			   this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			   this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->FilePathTextBox = (gcnew System::Windows::Forms::TextBox());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			   this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			   this->cppTimeLabel = (gcnew System::Windows::Forms::Label());
			   this->asmTimeLabel = (gcnew System::Windows::Forms::Label());
			   this->outputLabel = (gcnew System::Windows::Forms::Label());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->saveFileButton = (gcnew System::Windows::Forms::Button());
			   this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->blurLevelTrackBar))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->angleTrackBar))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->groupBox1->SuspendLayout();
			   this->groupBox2->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // processImageButton
			   // 
			   this->processImageButton->Enabled = false;
			   this->processImageButton->Location = System::Drawing::Point(242, 335);
			   this->processImageButton->Name = L"processImageButton";
			   this->processImageButton->Size = System::Drawing::Size(99, 44);
			   this->processImageButton->TabIndex = 0;
			   this->processImageButton->Text = L"Process image";
			   this->processImageButton->UseVisualStyleBackColor = true;
			   this->processImageButton->Click += gcnew System::EventHandler(this, &GUI::processImageButton_Click);
			   // 
			   // blurLevelTrackBar
			   // 
			   this->blurLevelTrackBar->Location = System::Drawing::Point(100, 37);
			   this->blurLevelTrackBar->Maximum = 100;
			   this->blurLevelTrackBar->Name = L"blurLevelTrackBar";
			   this->blurLevelTrackBar->Size = System::Drawing::Size(148, 45);
			   this->blurLevelTrackBar->TabIndex = 3;
			   this->blurLevelTrackBar->TickFrequency = 10;
			   this->blurLevelTrackBar->Scroll += gcnew System::EventHandler(this, &GUI::blurLevelTrackBar_Scroll);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(35, 45);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(57, 13);
			   this->label1->TabIndex = 4;
			   this->label1->Text = L"Blur Level:";
			   // 
			   // blurLevelTextBox
			   // 
			   this->blurLevelTextBox->Location = System::Drawing::Point(254, 37);
			   this->blurLevelTextBox->Name = L"blurLevelTextBox";
			   this->blurLevelTextBox->Size = System::Drawing::Size(64, 20);
			   this->blurLevelTextBox->TabIndex = 5;
			   this->blurLevelTextBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::blurLevelTextBox_KeyDown);
			   this->blurLevelTextBox->Leave += gcnew System::EventHandler(this, &GUI::blurLevelTextBox_Leave);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   this->openFileDialog1->Filter = L"Pliki PNG (*.png)|*.png|Wszystkie pliki (*.*)|*.*";
			   // 
			   // angleTextBox
			   // 
			   this->angleTextBox->Location = System::Drawing::Point(254, 83);
			   this->angleTextBox->Name = L"angleTextBox";
			   this->angleTextBox->Size = System::Drawing::Size(64, 20);
			   this->angleTextBox->TabIndex = 8;
			   this->angleTextBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::angleTextBox_KeyDown);
			   this->angleTextBox->Leave += gcnew System::EventHandler(this, &GUI::angleTextBox_Leave);
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(35, 91);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(37, 13);
			   this->label2->TabIndex = 7;
			   this->label2->Text = L"Angle:";
			   // 
			   // angleTrackBar
			   // 
			   this->angleTrackBar->LargeChange = 45;
			   this->angleTrackBar->Location = System::Drawing::Point(100, 83);
			   this->angleTrackBar->Maximum = 360;
			   this->angleTrackBar->Name = L"angleTrackBar";
			   this->angleTrackBar->Size = System::Drawing::Size(148, 45);
			   this->angleTrackBar->SmallChange = 45;
			   this->angleTrackBar->TabIndex = 6;
			   this->angleTrackBar->TickFrequency = 45;
			   this->angleTrackBar->Scroll += gcnew System::EventHandler(this, &GUI::angleTrackBar_Scroll);
			   // 
			   // pictureBox2
			   // 
			   this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->pictureBox2->Location = System::Drawing::Point(368, 49);
			   this->pictureBox2->Name = L"pictureBox2";
			   this->pictureBox2->Size = System::Drawing::Size(328, 167);
			   this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->pictureBox2->TabIndex = 10;
			   this->pictureBox2->TabStop = false;
			   // 
			   // loadFileButton
			   // 
			   this->loadFileButton->Location = System::Drawing::Point(242, 114);
			   this->loadFileButton->Name = L"loadFileButton";
			   this->loadFileButton->Size = System::Drawing::Size(84, 40);
			   this->loadFileButton->TabIndex = 11;
			   this->loadFileButton->Text = L"Load file";
			   this->loadFileButton->UseVisualStyleBackColor = true;
			   this->loadFileButton->Click += gcnew System::EventHandler(this, &GUI::loadFileButton_Click);
			   // 
			   // radioButton1
			   // 
			   this->radioButton1->AutoSize = true;
			   this->radioButton1->Checked = true;
			   this->radioButton1->Location = System::Drawing::Point(62, 134);
			   this->radioButton1->Name = L"radioButton1";
			   this->radioButton1->Size = System::Drawing::Size(71, 17);
			   this->radioButton1->TabIndex = 12;
			   this->radioButton1->TabStop = true;
			   this->radioButton1->Text = L"ASM DLL";
			   this->radioButton1->UseVisualStyleBackColor = true;
			   // 
			   // radioButton2
			   // 
			   this->radioButton2->AutoSize = true;
			   this->radioButton2->Location = System::Drawing::Point(181, 134);
			   this->radioButton2->Name = L"radioButton2";
			   this->radioButton2->Size = System::Drawing::Size(67, 17);
			   this->radioButton2->TabIndex = 13;
			   this->radioButton2->Text = L"C++ DLL";
			   this->radioButton2->UseVisualStyleBackColor = true;
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label3->Location = System::Drawing::Point(86, 30);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(189, 50);
			   this->label3->TabIndex = 14;
			   this->label3->Text = L"MOTION BLUR \nEFFECT APLLIER";
			   this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->pictureBox1->Location = System::Drawing::Point(368, 250);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(328, 167);
			   this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->pictureBox1->TabIndex = 15;
			   this->pictureBox1->TabStop = false;
			   // 
			   // FilePathTextBox
			   // 
			   this->FilePathTextBox->Location = System::Drawing::Point(34, 130);
			   this->FilePathTextBox->Name = L"FilePathTextBox";
			   this->FilePathTextBox->ReadOnly = true;
			   this->FilePathTextBox->Size = System::Drawing::Size(189, 20);
			   this->FilePathTextBox->TabIndex = 16;
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(31, 114);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(50, 13);
			   this->label4->TabIndex = 17;
			   this->label4->Text = L"File path:";
			   // 
			   // groupBox1
			   // 
			   this->groupBox1->Controls->Add(this->blurLevelTrackBar);
			   this->groupBox1->Controls->Add(this->label1);
			   this->groupBox1->Controls->Add(this->blurLevelTextBox);
			   this->groupBox1->Controls->Add(this->angleTrackBar);
			   this->groupBox1->Controls->Add(this->label2);
			   this->groupBox1->Controls->Add(this->radioButton2);
			   this->groupBox1->Controls->Add(this->angleTextBox);
			   this->groupBox1->Controls->Add(this->radioButton1);
			   this->groupBox1->Location = System::Drawing::Point(9, 160);
			   this->groupBox1->Name = L"groupBox1";
			   this->groupBox1->Size = System::Drawing::Size(347, 162);
			   this->groupBox1->TabIndex = 18;
			   this->groupBox1->TabStop = false;
			   this->groupBox1->Text = L"Options";
			   // 
			   // groupBox2
			   // 
			   this->groupBox2->Controls->Add(this->cppTimeLabel);
			   this->groupBox2->Controls->Add(this->asmTimeLabel);
			   this->groupBox2->Controls->Add(this->outputLabel);
			   this->groupBox2->Location = System::Drawing::Point(13, 331);
			   this->groupBox2->Name = L"groupBox2";
			   this->groupBox2->Size = System::Drawing::Size(200, 100);
			   this->groupBox2->TabIndex = 19;
			   this->groupBox2->TabStop = false;
			   this->groupBox2->Text = L"Output Dialog";
			   // 
			   // cppTimeLabel
			   // 
			   this->cppTimeLabel->AutoSize = true;
			   this->cppTimeLabel->Location = System::Drawing::Point(3, 83);
			   this->cppTimeLabel->Name = L"cppTimeLabel";
			   this->cppTimeLabel->Size = System::Drawing::Size(53, 13);
			   this->cppTimeLabel->TabIndex = 2;
			   this->cppTimeLabel->Text = L"CPP time:";
			   // 
			   // asmTimeLabel
			   // 
			   this->asmTimeLabel->AutoSize = true;
			   this->asmTimeLabel->Location = System::Drawing::Point(3, 66);
			   this->asmTimeLabel->Name = L"asmTimeLabel";
			   this->asmTimeLabel->Size = System::Drawing::Size(55, 13);
			   this->asmTimeLabel->TabIndex = 1;
			   this->asmTimeLabel->Text = L"ASM time:";
			   // 
			   // outputLabel
			   // 
			   this->outputLabel->AutoSize = true;
			   this->outputLabel->Location = System::Drawing::Point(3, 18);
			   this->outputLabel->Margin = System::Windows::Forms::Padding(0, 0, 3, 0);
			   this->outputLabel->Name = L"outputLabel";
			   this->outputLabel->Size = System::Drawing::Size(186, 13);
			   this->outputLabel->TabIndex = 0;
			   this->outputLabel->Text = L"Welcome to MotionBlur Effect Applier!";
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Location = System::Drawing::Point(368, 30);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(80, 13);
			   this->label5->TabIndex = 20;
			   this->label5->Text = L"Original picture:";
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Location = System::Drawing::Point(368, 231);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(74, 13);
			   this->label6->TabIndex = 21;
			   this->label6->Text = L"Output picture";
			   // 
			   // label7
			   // 
			   this->label7->AutoSize = true;
			   this->label7->Location = System::Drawing::Point(44, 80);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(282, 13);
			   this->label7->TabIndex = 22;
			   this->label7->Text = L"Assembly Language Project 2024/25 by Krzysztof Kluczka";
			   // 
			   // saveFileButton
			   // 
			   this->saveFileButton->Enabled = false;
			   this->saveFileButton->Location = System::Drawing::Point(242, 385);
			   this->saveFileButton->Name = L"saveFileButton";
			   this->saveFileButton->Size = System::Drawing::Size(99, 44);
			   this->saveFileButton->TabIndex = 23;
			   this->saveFileButton->Text = L"Save File";
			   this->saveFileButton->UseVisualStyleBackColor = true;
			   this->saveFileButton->Click += gcnew System::EventHandler(this, &GUI::saveFileButton_Click);
			   // 
			   // saveFileDialog1
			   // 
			   this->saveFileDialog1->Filter = L"\"PNG Image|*.png|JPEG Image|*.jpg;*.jpeg|Bitmap Image|*.bmp\"";
			   this->saveFileDialog1->Title = L"Save image as...";
			   // 
			   // GUI
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(755, 443);
			   this->Controls->Add(this->saveFileButton);
			   this->Controls->Add(this->label7);
			   this->Controls->Add(this->label6);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->groupBox2);
			   this->Controls->Add(this->groupBox1);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->FilePathTextBox);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->loadFileButton);
			   this->Controls->Add(this->pictureBox2);
			   this->Controls->Add(this->processImageButton);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			   this->MaximizeBox = false;
			   this->Name = L"GUI";
			   this->Text = L"MotionBlur";
			   this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->blurLevelTrackBar))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->angleTrackBar))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->groupBox1->ResumeLayout(false);
			   this->groupBox1->PerformLayout();
			   this->groupBox2->ResumeLayout(false);
			   this->groupBox2->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }

		   void SaveImage(Image^ image)
		   {

			   if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			   {
				   String^ fileName = saveFileDialog1->FileName;
				   // Pobierz rozszerzenie pliku i ustaw odpowiedni format obrazu
				   String^ ext = System::IO::Path::GetExtension(fileName)->ToLower();
				   System::Drawing::Imaging::ImageFormat^ format = System::Drawing::Imaging::ImageFormat::Png; // domyœlnie PNG

				   if (ext == ".jpg" || ext == ".jpeg")
				   {
					   format = System::Drawing::Imaging::ImageFormat::Jpeg;
				   }
				   else if (ext == ".bmp")
				   {
					   format = System::Drawing::Imaging::ImageFormat::Bmp;
				   }

				   // Zapisz obraz do wybranego pliku
				   image->Save(fileName, format);
				   printMessageOnOutput("File saved!");
			   }
		   }
		   void printMessageOnOutput(System::String^ message) {
			   this->outputLabel->Text = message;
		   }


#pragma endregion
	private: System::Void GUI_Load(System::Object^ sender, System::EventArgs^ e) {
		this->blurLevelTextBox->Text = "" + blurLevelTrackBar->Value + " px";
		this->angleTextBox->Text = "" + angleTrackBar->Value + "°";
	}

	private: System::Void blurLevelTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		this->blurLevelTextBox->Text = "" + blurLevelTrackBar->Value + " px";
	}

	private: System::Void blurLevelTextBox_Leave(System::Object^ sender, System::EventArgs^ e) {

		try {
			int value = Convert::ToInt32(this->blurLevelTextBox->Text);

			// Sprawdzenie, czy wartoœæ mieœci siê w zakresie TrackBar
			if (value >= this->blurLevelTrackBar->Minimum && value <= this->blurLevelTrackBar->Maximum) {
				this->blurLevelTrackBar->Value = value;
			}
			else {
				// Jeœli wartoœæ jest poza zakresem, przywróæ poprzedni¹ wartoœæ TrackBara
				this->blurLevelTextBox->Text = this->blurLevelTrackBar->Value.ToString() + " px";
			}
		}
		catch (Exception^ ex) {
			// Jeœli nie uda³o siê przekonwertowaæ tekstu, np. wpisano litery, ignorujemy zmianê
			this->blurLevelTextBox->Text = this->blurLevelTrackBar->Value.ToString() + " px";
		}
		if (!this->blurLevelTextBox->Text->EndsWith(" px"))
			this->blurLevelTextBox->Text = this->blurLevelTextBox->Text + " px";
	}

	private: System::Void angleTextBox_Leave(System::Object^ sender, System::EventArgs^ e) {

		try {
			int value = Convert::ToInt32(this->angleTextBox->Text);

			// Sprawdzenie, czy wartoœæ mieœci siê w zakresie TrackBar
			if (value >= this->angleTrackBar->Minimum && value <= this->angleTrackBar->Maximum) {
				this->angleTrackBar->Value = value;
			}
			else {
				// Jeœli wartoœæ jest poza zakresem, przywróæ poprzedni¹ wartoœæ TrackBara
				this->angleTextBox->Text = this->angleTrackBar->Value.ToString() + "°";
			}
		}
		catch (Exception^ ex) {
			// Jeœli nie uda³o siê przekonwertowaæ tekstu, np. wpisano litery, ignorujemy zmianê
			this->angleTextBox->Text = this->angleTrackBar->Value.ToString() + "°";
		}
		if (!this->angleTextBox->Text->EndsWith("°"))
			this->angleTextBox->Text = this->angleTextBox->Text + "°";
	}

	private: System::Void angleTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		this->angleTextBox->Text = "" + angleTrackBar->Value + "°";
	}

	private: System::Void loadFileButton_Click(System::Object^ sender, System::EventArgs^ e) {

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ filePath = openFileDialog1->FileName;
			this->FilePathTextBox->Text = filePath;
			// Za³aduj obraz do obiektu Bitmap
			originalImage = gcnew Bitmap(filePath);

			// Opcjonalnie: przypisz obraz do kontrolki PictureBox, ¿eby go wyœwietliæ
			pictureBox2->Image = originalImage;
			this->processImageButton->Enabled = true;
			printMessageOnOutput("File loaded!");
		}
	}

	private: System::Void processImageButton_Click(System::Object^ sender, System::EventArgs^ e) {


		tempImage = dynamic_cast<Bitmap^>(originalImage->Clone(
			System::Drawing::Rectangle(0, 0, originalImage->Width, originalImage->Height),
			System::Drawing::Imaging::PixelFormat::Format32bppArgb));

		// Ustal prostok¹t obejmuj¹cy ca³y obraz
		System::Drawing::Rectangle rect(0, 0, tempImage->Width, tempImage->Height);

		// Zablokuj bitmapê, uzyskuj¹c dostêp do danych
		System::Drawing::Imaging::BitmapData^ bmpData =
			tempImage->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, tempImage->PixelFormat);

		// Pobierz wskaŸnik do danych pikseli
		unsigned char* imageData = reinterpret_cast<unsigned char*>(bmpData->Scan0.ToPointer());
		// Ustal parametry efektu (przyk³adowe wartoœci)
		int blurLevel = this->blurLevelTrackBar->Value;
		int angle = this->angleTrackBar->Value;
		bool useAsm = this->radioButton1->Checked;
		double timeAsm, timeCpp;


		// Wywo³aj funkcjê z DLL
		if (LinearBlur(imageData, tempImage->Width, tempImage->Height, 4, blurLevel, angle, useAsm) == 0) {
			if (useAsm) {
				timeAsm = getAsmTimeMs();
				this->asmTimeLabel->Text = "ASM time: " + timeAsm + " ms";
				printMessageOnOutput("Using Asm DLL... Process succesful!");
			}
			else {
				timeCpp = getCppTimeMs();
				this->cppTimeLabel->Text = "CPP time: " + timeCpp + " ms";
				printMessageOnOutput("Using Cpp DLL... Process succesful!");

			}
			// Odblokuj bitmapê
			tempImage->UnlockBits(bmpData);
			pictureBox1->Image = tempImage;
			pictureBox1->Refresh();
			this->saveFileButton->Enabled = true;
		}
		else {
			printMessageOnOutput("DLL Error!!!");

		}

	}
	private: System::Void saveFileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->SaveImage(tempImage);
	}

	private: System::Void blurLevelTextBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			blurLevelTextBox_Leave(sender, e); // Wywo³ujemy tê sam¹ logikê co w Leave
		}
	}
	private: System::Void angleTextBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			angleTextBox_Leave(sender, e); // Wywo³ujemy tê sam¹ logikê co w Leave
		}
	};

	};
}
