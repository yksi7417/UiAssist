#ifdef OCRLIB_EXPORTS
#define OCRLIB_API __declspec(dllexport) 
#else
#define OCRLIB_API __declspec(dllimport) 
#endif

#pragma once
#include <memory>

namespace OCRLib
{
    class OCRLIB_API HelloWorld
    {
    public:
        static void sayIt();
    };

    class Window
    {
    public:
        OCRLIB_API Window(const char* title);
        bool OCRLIB_API exists();
        bool OCRLIB_API close();
        OCRLIB_API ~Window();

    private:
        struct WindowPrivateMembers;
        std::unique_ptr<WindowPrivateMembers> d_ptr_;

    private:
        // Explicitly Disable access for the followings
        Window();                               // Default Constructor
        Window(const Window&);                  // Copy constructor
        Window(Window&&) noexcept;              // Move constructor
        Window& operator=(const Window&);       // Copy assignment operator
        Window& operator=(Window&&) noexcept;   // Move assignment operator
    };
}
