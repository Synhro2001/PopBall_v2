#pragma once

#include "Ball.h"
#include <iostream>
#include "Ball.h"


namespace PopBallKrasovskis {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			MouseWheel += gcnew MouseEventHandler(this, &MainForm::Form_MouseWheel);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::PictureBox^ frame;
	private: System::Windows::Forms::Timer^ drawTimer;
	public:
	private: System::Windows::Forms::Timer^ moveTimer;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->frame = (gcnew System::Windows::Forms::PictureBox());
			this->drawTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->moveTimer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->frame))->BeginInit();
			this->SuspendLayout();
			// 
			// frame
			// 
			this->frame->Location = System::Drawing::Point(12, 12);
			this->frame->Name = L"frame";
			this->frame->Size = System::Drawing::Size(690, 417);
			this->frame->TabIndex = 0;
			this->frame->TabStop = false;
			this->frame->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::frame_Paint);
			this->frame->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::frame_MouseDoubleClick);
			this->frame->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::MainForm_MouseDown);
			this->frame->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::frame_MouseMove);
			this->frame->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::frame_MouseUp);
			// 
			// drawTimer
			// 
			this->drawTimer->Enabled = true;
			this->drawTimer->Interval = 10;
			this->drawTimer->Tick += gcnew System::EventHandler(this, &MainForm::drawTimer_Tick);
			// 
			// moveTimer
			// 
			this->moveTimer->Enabled = true;
			this->moveTimer->Interval = 10;
			this->moveTimer->Tick += gcnew System::EventHandler(this, &MainForm::moveTimer_Tick);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(714, 441);
			this->Controls->Add(this->frame);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->KeyPreview = true;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Pop Balls V1: Single Ball";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->frame))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: 
		int x1, y1, x2, y2, nt;
		bool timer_counter;
		float dx, dy;



	private: System::Void frame_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ grp = e->Graphics;
		Pen framePen(Color::Black, 3);
		grp->FillRectangle(% SolidBrush(Color::White), 0, 0, frame->Width, frame->Height);
		grp->DrawRectangle(% framePen, 0, 0, frame->Width, frame->Height);
		ball->draw(grp);

	}

	private: System::Void MainForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		
		if (e->Button == System::Windows::Forms::MouseButtons::Left) { // момент нажатие левой клавиши мыши
			ball->setPos(e->X, e->Y);
			 ball->setSpeed(0, 0); // останавливаем шарик в момент нажатие мышки
			 x1 = e->X; // передаем координаты 
			 y1 = e->Y;
			 nt = 0;
			 timer_counter = true;

		}
		
		else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			ball->followTo(e->X, e->Y);
		}

	}

	private: System::Void frame_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			ball->setPos(e->X, e->Y);
		}
		else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			ball->followTo(e->X, e->Y);
		}
	}



	private: System::Void frame_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		ball->setColor(Color::FromArgb(rand() % 256, rand() % 256, rand() % 256).ToArgb());


	}

	private: void Form_MouseWheel(Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {


		if (ModifierKeys == Keys::Control) {


			if (e->Delta < 0) {
				ball->setSize(ball->getSize() - 5);
			}
			else {
				ball->setSize(ball->getSize() + 5);
			}

		}



		// Есть ошибка если резко менять скорость программа зависает ( она багуется в одной координате )
		dx = ball->getdX();
		dy = ball->getdY();
		
		if (e->Delta > 0) {
			if (dx < 15) {
				dx = dx * 2; // умножаем на коэфицент > 1
			}
			if (dy < 15) {
				dy = dy * 2;
			}
			ball->setSpeed(dx, dy);
		}
		else  {
			if (abs(dx) > 1) { // берем число в модуль чтобы при изменение скорости шарика его анимация не меняля направление !!!
				dx = dx * 0.5; // умножаем на коэфицент < 1
			}
			if (abs(dy) > 1) {
				dy = dy * 0.5;
			}

			ball->setSpeed(dx, dy);
		}

	}

	private: System::Void moveTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		ball->move();
		if (timer_counter == true) {
			
			nt++;
		}
	
	}

	private: System::Void drawTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		frame->Invalidate();
	}


	private: System::Void frame_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			timer_counter = false;
			x2 = e->X; // передаем координаты после того как мы отпустили левый шелчек
			y2 = e->Y;
			
			dx = (x2 - x1) / nt;
			dy = (y2 - y1) / nt;
			ball->setSpeed(dx, dy);
			
		}

	}
};
}
