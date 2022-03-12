#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

int main()
{
	srand((unsigned)time(NULL));
	Application::EnableVisualStyles();
	PopBallKrasovskis::MainForm form;
	ball = new Ball(form.frame->Width, form.frame->Height);
	Application::Run(% form);
	delete ball;
}