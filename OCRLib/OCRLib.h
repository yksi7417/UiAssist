#ifdef OCRLIB_EXPORTS
#define OCRLIB_API __declspec(dllexport) 
#else
#define OCRLIB_API __declspec(dllimport) 
#endif

namespace OCRLib
{
    class OCRLIB_API HelloWorld
    {
    public:
        static void sayIt();
    };
}
