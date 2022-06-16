#include "pch.h"
#include <windows.h>
#include "..\OCRLib\OCRLib.h"

using namespace std;

namespace TestWindow {
	TEST(TestWinClose, IfWindowsExistsCloseTheWindow) {
		HINSTANCE errorCode = ShellExecute(NULL, L"open", L"C:\\Windows\\system32\\notepad.exe", L"OCRLibText.txt", NULL, SW_SHOWDEFAULT);
		OCRLib::Window window("OCRLibText.txt - Notepad");
		EXPECT_EQ(0, 0);
		EXPECT_TRUE(window.exists());
	}
}

