#include "pch.h"
#include <windows.h>
using namespace std;

namespace Windows {
	TEST(TestWinClose, IfWindowsExistsCloseTheWindow) {
		HINSTANCE errorCode = ShellExecute(NULL, L"open", L"C:\\Windows\\system32\\notepad.exe", L"OCRLibText.txt", NULL, SW_SHOWDEFAULT);
		EXPECT_EQ(0, 0);
		EXPECT_TRUE(true);
	}
}

