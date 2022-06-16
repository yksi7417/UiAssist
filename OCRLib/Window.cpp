#include "pch.h"
#include <string.h>
#include <windows.h>
#include <dwmapi.h>
#include <tchar.h>

#include "OCRLib.h"

#define WINDOW_TEXT_SIZE 32767
#define SEARCH_PHRASE_SIZE 1024

class WindowSearch {
public:
	HWND IsMatch();
	void SetCandidate(HWND aWnd);

private:
	void UpdateCandidateAttributes();
	bool DetectWindow(HWND aWnd);
	BOOL CALLBACK EnumParentFind(HWND aWnd, LPARAM lParam);
	bool IsWindowCloaked(HWND aWnd);

private:
	HWND mCandidateParent;
	bool mFindLastMatch; 
	TCHAR mCandidateTitle[WINDOW_TEXT_SIZE];
	TCHAR mCriterionTitle[SEARCH_PHRASE_SIZE]; // For storing the title.
	size_t mCriterionTitleLength;             // Length of mCriterionTitle.
};

void WindowSearch::SetCandidate(HWND aWnd) 
{
	// For performance reasons, update the attributes only if the candidate window changed:
	if (mCandidateParent != aWnd)
	{
		mCandidateParent = aWnd;
		UpdateCandidateAttributes(); 
	}
}

void WindowSearch::UpdateCandidateAttributes()
{
	if (!mCandidateParent)
		return;
	if (!GetWindowText(mCandidateParent, mCandidateTitle, _countof(mCandidateTitle)))
		*mCandidateTitle = '\0'; 
}

HWND WindowSearch::IsMatch()
{
	if (_tcscmp(mCandidateTitle, mCriterionTitle))
		return NULL;
	return mCandidateParent;
}

bool WindowSearch::IsWindowCloaked(HWND aWnd)
{
	static auto* pfn = (decltype(&DwmGetWindowAttribute))
		GetProcAddress(LoadLibrary(_T("dwmapi.dll")), "DwmGetWindowAttribute");
	if (!pfn) // Windows XP or earlier.
		return false;
	int cloaked = 0;
	const int DWMWA_CLOAKED = 14; // Work around SDK troubles.
	auto result = pfn(aWnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
	return SUCCEEDED(result) && cloaked; // Result is "invalid parameter" on Windows 7.
}

bool WindowSearch::DetectWindow(HWND aWnd)
{
	return (IsWindowVisible(aWnd) && !IsWindowCloaked(aWnd));
}


BOOL CALLBACK WindowSearch::EnumParentFind(HWND aWnd)
{
	if (!DetectWindow(aWnd)) return TRUE;
	SetCandidate(aWnd);
	return IsMatch() ? mFindLastMatch : TRUE;
}


HWND WinExist(std::string& title, HWND aAlreadyVisited[], int aAlreadyVisitedCount)
{
	HWND target_window;

	WindowSearch ws;
	if (!ws.SetCriteria(aSettings, aTitle, aText, aExcludeTitle, aExcludeText)) // No match is possible with these criteria.
		return NULL;

	ws.mAlreadyVisited = aAlreadyVisited;
	ws.mAlreadyVisitedCount = aAlreadyVisitedCount;

	EnumWindows(EnumParentFind, (LPARAM)&ws);

	UPDATE_AND_RETURN_LAST_USED_WINDOW(ws.mFoundParent) // This also does a "return".
}

namespace OCRLib {

	struct Window::WindowPrivateMembers {
		std::string title; 
		WindowPrivateMembers(const char* title_) : title(title_) {
		}

	};

	Window::Window(const char* title_) 
		: d_ptr_(std::make_unique<WindowPrivateMembers>(title_)) {
	}

	Window::~Window() = default;

	bool Window::exists() {
		HWND target_window = GetForegroundWindow();

		return false;
	}

	bool Window::close() {
		return false;
	}

}

