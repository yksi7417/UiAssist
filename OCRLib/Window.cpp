#include "pch.h"
#include "OCRLib.h"
#include <string>

namespace OCRLib {

	struct Window::WindowImplDetails {
		std::string title; 
		WindowImplDetails(const char* title_) : title(title_) {
		}

	};

	Window::Window(const char* title_) 
		: d_ptr_(std::make_unique<WindowImplDetails>(title_)) {
	}

	Window::~Window() = default;

	bool Window::exists() {
		return false;
	}

	bool Window::close() {
		return false;
	}

}

