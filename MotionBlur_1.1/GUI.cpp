#include "pch.h"
#include <Windows.h>
#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace GUIns;


[STAThread]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	auto form = gcnew GUIns::GUI();
	Application::Run(form);

	return 0;
}