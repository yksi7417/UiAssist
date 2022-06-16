#include "pch.h"
#include "OCRLib.h"
#include <string>

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

