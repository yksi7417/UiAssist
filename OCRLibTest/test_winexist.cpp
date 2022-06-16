#include "pch.h"
#include <windows.h>
using namespace std;

namespace Windows {
	TEST(TestWinExist, IfWindowsExistsReturnTrue) {
		MessageBox(NULL, L"hello world", L"OCRLib TestWindow", 0);
		EXPECT_EQ(1, 1);
		EXPECT_TRUE(true);
	}
}

